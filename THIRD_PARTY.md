# Third-Party Credits & Licenses

The **Recon Ground Drone** project reuses and adapts code from several open-source
projects, tutorials and blog posts. Below is every external source we are aware of,
with its license. Huge thanks to all the original authors. 🙏

If you believe a credit is missing or incorrect, please open an issue.

---

## 1. Bundled / vendored code (shipped in this repo)

| File | Source | Author | License |
|------|--------|--------|---------|
| `webui/R6DC-V1/HTML/jquery.min.js` (v2.1.3) | [jQuery](https://jquery.com/) | jQuery Foundation | MIT |

## 2. Adapted source code

| File(s) | Adapted from | Upstream license |
|---------|--------------|------------------|
| `firmware/esp32cam-v2/.../Server.cpp`, `firmware/esp32cam-v1-proto/.../Server.cpp` | [robotzero.one ESP32-CAM RC Car](https://robotzero.one/esp32-cam-rc-car/) — [repo](https://github.com/robotzero1/esp32cam-rc-car) | No explicit license (blog sample code); adapted with attribution — see note ‡. GPL-3.0 caveat applies via ArduinoWebsockets — see note † |
| `firmware/esp32cam-*/.../Motor_ctrl.cpp`, `test-sketches/Test_cam2` | [un0038998 / CameraCarWithPanTiltControl](https://github.com/un0038998/CameraCarWithPanTiltControl) | MIT |
| PWM helpers in `Motor_ctrl.cpp` | [electroniqueamateur — PWM](https://electroniqueamateur.blogspot.com/2019/08/modulation-par-largeur-dimpulsion-pwm.html) + [benpeoples gist](https://gist.github.com/benpeoples/3aa57bffc0f26ede6623ca520f26628c) | No license: blog tutorial + a factual PWM-frequency reference table (facts, not copyrightable) — see note ‡ |
| `test-sketches/Test_cam1/Test_cam1.ino` | [electroniqueamateur — ESP32-CAM web server minimaliste](https://electroniqueamateur.blogspot.com/2020/01/esp32-cam-un-web-server-minimaliste.html), derived from the Espressif `CameraWebServer` example | Apache-2.0 |
| `test-sketches/Test_Motor1/Test_Motor1.ino` | Common ESP32-CAM "MyWiFiCar" RC-car tutorial (un0038998 lineage) | MIT |
| `webui/joystick-tests/Page1.html` | robotzero.one + send-rate limiter from [neonious/lowjs_esp32_examples](https://github.com/neonious/lowjs_esp32_examples) (`cellphone_controlled_rc_car`) | MIT (neonious) |
| `webui/joystick-tests/Test HTML/Joystick_test.html` | [Instructables — Making a Joystick With HTML (pure JavaScript)](https://www.instructables.com/Making-a-Joystick-With-HTML-pure-JavaScript/) | CC BY-NC-SA 4.0 (Instructables author-selected license). This file keeps its NonCommercial/ShareAlike terms — **not** MIT — see note ‡ |
| `webui/R6DC-V1/HTML/ESP8266-1.html`, `R6DC.html` | Classic ESP8266 web LED-control pattern + jQuery | Generic tutorial idiom, no specific upstream license (jQuery itself is MIT) — see note ‡ |

## 3. Library dependencies (NOT bundled — installed via Arduino IDE / PlatformIO)

| Library | Author | License |
|---------|--------|---------|
| [ArduinoWebsockets](https://github.com/gilmaimon/ArduinoWebsockets) | gilmaimon | **GPL-3.0** ⚠️ |
| [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) | me-no-dev | LGPL-3.0 |
| [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) | me-no-dev | LGPL-3.0 |
| [esp32-camera](https://github.com/espressif/esp32-camera) (`esp_camera.h`) | Espressif | Apache-2.0 |
| Arduino core for ESP32 / ESP8266 | Espressif / ESP8266 community | LGPL-2.1 |
| ESP32Servo / Servo | community | LGPL-2.1 |

---

## † Important license note (GPL-3.0)

The ESP32-CAM firmware depends on **ArduinoWebsockets**, which is **GPL-3.0**
(strong copyleft). Because GPL-3.0 is "viral" for linked code, any firmware
**binary** you compile and then **distribute** is itself covered by GPL-3.0 —
even though the code written specifically for this project is offered under MIT.

- Source written for this project → **MIT** (see `LICENSE`).
- A redistributed ESP32-CAM binary, or a fork that keeps ArduinoWebsockets → **GPL-3.0**.

To obtain a fully permissive firmware, swap ArduinoWebsockets for an LGPL
alternative such as [Links2004/arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets).

---

## ‡ Note on tutorial / blog / Instructables sources

Some adapted snippets come from blog posts, forum answers or Instructables that do
**not** ship a formal software license:

- **Blog / forum / tutorial code** (robotzero.one, electroniqueamateur, the generic
  ESP8266 LED-control pattern): no formal license is provided. The relevant parts
  were re-implemented and adapted for this project, and are credited above. If any
  author wants their attribution changed or their code removed, please open an issue
  and it will be handled promptly.
- **Reference data** (the benpeoples gist) is a factual table of maximum PWM
  frequencies. Facts aren't copyrightable, so it is used freely with credit.
- **Instructables joystick** (`Joystick_test.html`): Instructables content is
  published under an author-selected Creative Commons license (commonly
  **CC BY-NC-SA 4.0**). That single test file therefore keeps its original
  **CC BY-NC-SA** terms (attribution, non-commercial, share-alike) and is **not**
  covered by this project's MIT license. This whole project is a non-commercial fan
  project, so those terms are respected.
