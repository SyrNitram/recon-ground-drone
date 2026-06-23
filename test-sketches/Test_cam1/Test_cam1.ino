// Recon Ground Drone - adapted file
// Original code (c) 2022-2023 Martin RYS, released under the MIT License.
// Adapted from: electroniqueamateur 'ESP32-CAM web server minimaliste',
//   itself derived from the Espressif CameraWebServer example (Apache-2.0).
//   https://electroniqueamateur.blogspot.com/2020/01/esp32-cam-un-web-server-minimaliste.html

/*
  Affichage dans une page web de l'image vidéo
  d'une ESP32-CAM.
  Version légère, sans reconnaissance faciale,
  réglage de paramètres, page web sophistiquée, etc.
  Pour plus d'infos:
  https://electroniqueamateur.blogspot.com/2020/01/esp32-cam-un-web-server-minimaliste.html
*/

#include "esp_camera.h"
#include <WiFi.h>
#include "esp_http_server.h"

// paramètres de votre réseau WiFi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

httpd_handle_t stream_httpd = NULL;
httpd_handle_t camera_httpd = NULL;

int numero_port; // numéro du port du stream server

// ********************************************************
// stream_handler: routine qui gère le streaming vidéo

static esp_err_t stream_handler(httpd_req_t *req) {
  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t * _jpg_buf = NULL;
  char * part_buf[64];

  static int64_t last_frame = 0;
  if (!last_frame) {
    last_frame = esp_timer_get_time();
  }

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if (res != ESP_OK) {
    return res;
  }
  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

  while (true) {
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Echec de la capture de camera");
      res = ESP_FAIL;
    } else {
      if (fb->width > 400) {
        if (fb->format != PIXFORMAT_JPEG) {
          bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
          esp_camera_fb_return(fb);
          fb = NULL;
          if (!jpeg_converted) {
            Serial.println("Echec de la compression JPEG");
            res = ESP_FAIL;
          }
        } else {
          _jpg_buf_len = fb->len;
          _jpg_buf = fb->buf;
        }
      }
    }
    if (res == ESP_OK) {
      size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
      res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if (res == ESP_OK) {
      res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
    }
    if (res == ESP_OK) {
      res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
    }
    if (fb) {
      esp_camera_fb_return(fb);
      fb = NULL;
      _jpg_buf = NULL;
    } else if (_jpg_buf) {
      free(_jpg_buf);
      _jpg_buf = NULL;
    }
    if (res != ESP_OK) {
      break;
    }
  }
  last_frame = 0;
  return res;
}

// ********************************************************
// web_handler: construction de la page web

static esp_err_t web_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  httpd_resp_set_hdr(req, "Content-Encoding", "identity");
  sensor_t * s = esp_camera_sensor_get();

  char pageWeb[300] = "";
  strcat(pageWeb, "<!doctype html><html><head><title id='title'>ESP32-CAM</title></head><body style='background-color:#000000;'>");
  strcat(pageWeb, "<img style='object-fit:contain;width:95vw;height:50vh;margin:auto;display:block;' id='stream' src='http://");
  //strcat(pageWeb, "<img style='width:95vw;max-height:50vh;margin:auto; display:block;' id='stream' src='http://");
  // l'adresse du stream server (exemple: 192.168.0.145:81):
  char adresse[20] = "";
  sprintf (adresse, "%d.%d.%d.%d:%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3], numero_port);
  strcat(pageWeb, adresse);
  strcat(pageWeb, "/stream'></body></html>");
  int taillePage = strlen(pageWeb);

  return httpd_resp_send(req, (const char *)pageWeb, taillePage);
}

// ********************************************************
// startCameraServer: démarrage du web server et du stream server

void startCameraServer() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = web_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t stream_uri = {
    .uri       = "/stream",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };

  Serial.printf("Demarrage du web server sur le port: '%d'\n", config.server_port);
  if (httpd_start(&camera_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(camera_httpd, &index_uri);
  }

  config.server_port += 1;
  config.ctrl_port += 1;
  Serial.printf("Demarrage du stream server sur le port: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &stream_uri);
  }

  numero_port = config.server_port;
}

// ********************************************************
// initialisation de la caméra, connexion au réseau WiFi.

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("====");

  // définition des broches pour le modèle AI Thinker - ESP32-CAM
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;  //YUV422|GRAYSCALE|RGB565|JPEG
  config.frame_size = FRAMESIZE_VGA;  // QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
  config.jpeg_quality = 15;  // 0-63 ; plus bas = meilleure qualité
  config.fb_count = 2; // nombre de frame buffers

  /*
     QVGA     320x240
     CIF      352x288
     VGA      640x480
     SVGA     800x600
     XGA      1024x768
     SXGA     1280x1024
     UXGA     1600x1200
  */

  // initialisation de la caméra
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Echec de l'initialisation de la camera, erreur 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();

  Serial.println("");
  Serial.print("Connexion au reseau WiFi: ");
  Serial.println(ssid);
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }

  Serial.println("WiFi connecte");
  Serial.println("");

  delay(100);

  startCameraServer();

  Serial.print("La camera est prete.  Utilisez 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' pour vous connecter.");

}

// ********************************************************
// loop ne fait rien!

void loop() {
  delay(10000);
}
