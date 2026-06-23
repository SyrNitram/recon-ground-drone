# Recon Ground Drone

*Language: [Français](README.fr.md) · **English***

A small 3D-printed RC ground drone, inspired by the recon ground drone from
*Rainbow Six Siege*. It's a personal project I've been sitting on since 2022, and I
finally decided to release the files so others can use it, tinker with it, and
(hopefully) take it further than I did.

To drive it: an ESP32-CAM, a web page with a virtual joystick, and the camera feed
straight in the browser. The earliest versions ran on other setups (see the history
just below), which I've kept in the repo for the record.

> Fan project, **unofficial**. "Rainbow Six" and the drone design belong to Ubisoft.
> I'm not affiliated with anyone, this is non-commercial, and the 3D models are my
> own creations inspired by the game.

## Demo

<p align="center">
  <img src="images/render-vs-print-1.jpg" alt="The printed drone in front of its SolidWorks render" width="660">
  <br><em>The printed drone next to its original SolidWorks render.</em>
</p>

<p align="center">
  <img src="images/demo-drive.gif" alt="Driving the drone around the room" width="420">
  <br><em>Yes, it actually drives. Full clip: <a href="media/demo-drive.mp4"><code>media/demo-drive.mp4</code></a></em>
</p>

## A bit of history

Originally, this drone was a birthday gift for a friend. His version ran on Arduino,
with an analog FPV feed and a Flysky PWM receiver: so radio control, with FPV
goggles/screen. That version isn't in this repo, but it's the real starting point of
the project.

Then, for my own use, I wanted something more comfortable: to control everything from
a single device, without lugging an FPV mask or screen around on top of my phone.
That's how a WiFi version, drivable from the phone, came about (the Arduino + ESP8266
base you'll find in `firmware/arduino-esp8266-legacy`).

Then I discovered the ESP32-CAM, which has the camera built in. I figured the latency
would be higher — and it is — but having everything in one small module was worth a
shot. This ESP32-CAM line is what makes up the current versions of the project.

## Current state: honestly, it's not finished

What works today is the **ESP32-CAM v2** firmware with video over WiFi. But there are
still two real flaws I never solved:

- **It tips over when braking.** Brake hard and the drone lurches forward from its own
  inertia and noses down. It's a center-of-gravity / mass-distribution problem. That's
  exactly what I wanted to fix with the V2.0 CAD… which I never finished.
- **WiFi range is laughable.** It works, the video only has a touch of latency, but as
  soon as you move away a bit it drops out. That's the limit of the ESP32-CAM's WiFi.
  I originally wanted a proper FPV radio link; I never got there.

So if you're looking for where to contribute: **balance and range** are where it
hurts. Forks and PRs are welcome.

## What I'd love to see

Honestly, one of the reasons I'm publishing is curiosity — **I'd love to see what
people can do with it.** To this day I haven't seen any equivalent project as complete
around the R6 recon drone, even though technically… it's not that hard.

So: take it, fork it, or build your own from scratch, however you like. But if you do,
**share the result with me** (an issue, a PR, or a message). I'd really love to see —
and test — your evolutions, versions and improvements.

## Features

What's already in place in the firmware (ESP32-CAM versions, unless noted otherwise):

- **Differential drive** of both motors from a virtual joystick: the joystick position
  is converted into speed + angle, then split between the left and right motors
  (in-place rotation included).
- **Acceleration ramp and minimum PWM**: an acceleration limit smooths out the jolts,
  and a minimum PWM threshold overcomes the motors' start-up inertia (tunable via
  `ACC_MAX` and `PWM_MIN`).
- **Live video feed** from the ESP32-CAM (OV2640 sensor), shown in the web page.
- **Game-faithful LED animation**: a sweeping / "running light" effect on the light
  rings, like the R6 recon drone (sequential lighting outer → middle → inner, then
  back). On ESP32: 3 groups (`LED_OUT` / `LED_MID` / `LED_IN`); on the Arduino
  version: 6 LEDs in a symmetrical sweep.
- **Motorized LED deployment (like in the game)**: the lights **deploy** via a **servo
  motor**, the way the recon drone "opens up" its lights. This one works. The servo is
  handled in the code (`Servo` / `servo_ctrl`).
- **Access Point (AP) or Station (STA) mode**, selectable via `#define AP_MODE`.
- **Onboard flash control** of the ESP32-CAM.
- On the **Arduino (legacy) version**, additionally: ZQSD directional commands, an
  automatic **safety stop** if no command is received for 5 s, and battery-voltage
  measurement.

<p align="center">
  <img src="images/leds.gif" alt="In-game-style LED running light" width="420">
  <br><em>The game-faithful LED “running light” effect. Full clip: <a href="media/leds.mp4"><code>media/leds.mp4</code></a></em>
</p>

## Version history

I kept the various stages rather than overwriting everything — it can be useful.

**Mechanics (CAD) —** the 3D files are available as a download in the
[latest release](https://github.com/SyrNitram/recon-ground-drone/releases/latest) (`cad.zip`).

- **V1.0** — the first complete version. Designed between May and October 2022, it's
  the one it all started with.
- **V1.9** — an intermediate version, lots of small tweaks on top of V1.0.
- **V2.0** — the redesign meant to fix the tipping. I worked on it until 5 March 2023
  then stopped. **It's unfinished**, treat it as a starting point.

**Firmware —**

- `firmware/esp32cam-v2` — the current, working version (ESP32-CAM, WiFi video, web
  joystick). Start here.
- `firmware/esp32cam-v1-proto` — the earlier ESP32-CAM prototype, kept for reference.
- `firmware/arduino-esp8266-legacy` — the very first base, on Arduino + ESP8266 over
  AT commands (2022). It's history, I no longer maintain it.

**Web interface —**

- `webui/R6DC-V1` — the main control interface (joystick + video stream).
- `webui/joystick-tests` — my virtual-joystick experiments in HTML, all over the
  place. It's rough, but it shows the approach.

## The 3D files (CAD)

> 📦 **Download the 3D files:** they're attached to the
> [latest release](https://github.com/SyrNitram/recon-ground-drone/releases/latest)
> as `cad.zip` (too heavy to sit in the main file list).

A few honest warnings before printing:

- **It was designed in the pre-Bambu Lab era.** My machine back then had pretty
  mediocre precision and flow. As a result, **the part tolerances were tuned for MY
  machine** — and even then, sometimes just barely. That's also why there are so many
  **test files**: they were for dialing in those tolerances.
- **To be revisited with current printers.** On a recent machine (Bambu Lab and the
  like), the tolerances almost certainly need redoing.
- **SolidWorks format.** The models are in SolidWorks (`.SLDPRT` / `.SLDASM`). If you
  can, the ideal would be to adopt a **simple convention**: keep the native files, but
  also export neutral formats (`STEP` for editing, `STL` or `3MF` ready to print), with
  one folder per version. That makes everything reusable even without SolidWorks.
- **The latest 3D version (V2.0) isn't finished.** If you pick it up, **look at the
  full virtual assembly first** in the CAD software to check that everything lines up
  *before* starting a print — it'll save you wasting filament on parts that don't fit
  together yet.

## What's in the repo

```
firmware/      the board code (see versions above)
test-sketches/ isolated test sketches (camera, motors)
webui/         the web control interfaces
(CAD)          3D models — download from Releases → cad.zip (SolidWorks)
hardware/      the BOM and a few reference docs
images/        photos and GIFs used in this README
media/         demo videos (driving, LEDs, assembly)
```

## Hardware

The full list is in `hardware/BOM.xlsx`. Roughly: an ESP32-CAM, a motor driver, DC
motors, a battery, and the printed parts. Budget around €120 of components.

## Wiring & schematic

I don't (yet) have a clean schematic — **if someone wants to draw one, it's very
welcome.** In the meantime, here's the pinout **extracted straight from the code**,
for the parts wired to the programmable boards. The reference is the ESP32-CAM v2 (the
version that works).

### ESP32-CAM v2 (current version)

Notable point: the **motor direction** outputs and the **LEDs** go through an **I²C
PCF8574 I/O expander** (address `0x20`), to save the ESP32-CAM's GPIOs. Only the
**speed PWM** outputs are wired directly to the ESP32.

I²C bus to the PCF8574:

| Signal | ESP32-CAM GPIO |
|--------|----------------|
| SDA | GPIO13 |
| SCL | GPIO15 |
| Frequency | 100 kHz |

Outputs via the PCF8574 (pins P0–P7):

| PCF8574 pin | Role |
|-------------|------|
| P0 | Motor — IN1 (direction) |
| P1 | Motor — IN2 (direction) |
| P2 | Motor — IN3 (direction) |
| P3 | Motor — IN4 (direction) |
| P5 | Outer LED ring |
| P6 | Middle LED ring |
| P7 | Inner LED ring |

Motor speed PWM (directly on the ESP32, via LEDC, 40 kHz / 10-bit):

| Signal | GPIO | LEDC channel |
|--------|------|--------------|
| Left motor (EN) | GPIO14 | 10 |
| Right motor (EN) | GPIO12 | 11 |

ESP32-CAM onboard:

| Function | GPIO |
|----------|------|
| Flash LED | GPIO4 |
| Onboard red LED | GPIO33 |
| OV2640 camera | standard AI-Thinker pinout (XCLK 0, SIOD 26, SIOC 27, VSYNC 25, HREF 23, PCLK 22, D0–D7 = 5/18/19/21/36/39/34/35, PWDN 32) |

Network: a **WebSocket server on port 82** (commands + stream) and an **HTTP server on
port 80** (web page). STA mode by default (`AP_MODE 0`).

> ⚠️ On the power side, the motors go through an **L298N**-type driver: the IN pins
> come from the PCF8574, the ENA/ENB pins receive the PWM from the ESP32. Plan for a
> separate motor supply and a common ground.

### Arduino + ESP8266 (legacy, historical)

Indicative pinout as defined in the files (the `main` variant). ⚠️ This was
experimental: some pins overlap from one variant/experiment to another (e.g. the
software serial link and some LEDs share D8/D9), so double-check before wiring.

| Signal | Arduino pin |
|--------|-------------|
| Motors — ENA / ENB (PWM) | D5 / D6 |
| Motors — IN1 / IN2 / IN3 / IN4 | A1 / A2 / A3 / A4 |
| LEDs 1–6 (running light, defined in `led_ctrl`) | D9 / D10 / D8 / D12 / D11 / D7 |
| Software serial link (SoftwareSerial) | D8 (RX) / D9 (TX) |
| WiFi | ESP8266 module driven over AT commands |

Control is done through a web page (port 80) served via the ESP8266 module.

## Running the ESP32-CAM firmware

1. Arduino IDE + the ESP32 board support (board: AI Thinker ESP32-CAM).
2. Install the libraries listed in `THIRD_PARTY.md` (ArduinoWebsockets,
   ESPAsyncWebServer, AsyncTCP, esp32-camera).
3. Open `firmware/esp32cam-v2/R6_Drone_V0_2/R6_Drone_V0_2.ino`.
4. Put your WiFi credentials in place of the placeholders:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
   (I removed mine from the code, obviously — never commit yours.)
5. Upload, open the serial monitor to grab the IP, and go to that IP in a browser. The
   joystick controls direction/speed, the camera shows on screen (WebSocket on port
   82, page served on port 80).

The Arduino + ESP8266 version is in `firmware/arduino-esp8266-legacy/` if you're
interested; same idea for WiFi (placeholders in `wifi_com.h`).

## Gallery

<p align="center">
  <img src="images/render-vs-print-2.jpg" alt="Render vs print, side view" width="49%">
  <img src="images/build-electronics.jpg" alt="The drone opened up, electronics visible" width="49%">
</p>

More footage: assembly / internals in <a href="media/assembly.mp4"><code>media/assembly.mp4</code></a>.

## Credits

I'm far from having written everything myself. I leaned on quite a few projects and
tutorials (robotzero.one for the ESP32-CAM server, un0038998 for motor control,
neonious, electroniqueamateur, jQuery, the Espressif and me-no-dev libraries…). The
full breakdown, file by file, with licenses, is in **THIRD_PARTY.md**. Thanks to all
of these people.

## License

My code is under **MIT** (see `LICENSE`). One important note: the ESP32-CAM firmware
uses `ArduinoWebsockets`, which is **GPL-3.0**. As a result, a firmware binary you
compile and then redistribute is itself covered by GPL-3.0, even though my source code
stays MIT. This is explained in `LICENSE` and `THIRD_PARTY.md`.

## A note on honesty

The project, the design, the code, the balance struggles: that's all me, over several
months. But let's be clear: if I'm publishing today, it's only thanks to an AI. It's
the one lever that tipped me over — without it, I'd never have taken the time to
reorganize the folders, clean up and write all this documentation, and the project
would have stayed private, like it has since 2022. That's exactly why there's such a
gap between building the drone and putting it online.

## Links

- GitHub repo: https://github.com/SyrNitram/recon-ground-drone

---

Project by **Martin RYS** ([@SyrNitram](https://github.com/SyrNitram)). Taking it
further, improving it? I'd genuinely love to know — open an issue or a PR. 🛰️
