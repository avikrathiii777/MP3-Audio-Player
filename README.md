# ESP32 Bluetooth MP3 Player

This is a pocket-sized Bluetooth MP3 player that stands on its own. It is built around a custom **ESP32-WROOM-32E** PCB and a custom two-piece **3D-printed resin enclosure**. The player reads `.mp3` tracks from a MicroSD card. It decodes stereo audio in time. Then it sends the sound wirelessly through Bluetooth A2DP to headphones (**JBL Tune 770NC**). You control playback and volume with buttons.

---

## Features & Hardware Architecture

* **Microcontroller & Bluetooth Audio:** The `ESP32-WROOM-32E` streams audio over Bluetooth Classic (`A2DP Source`).

* **Storage:** A push-pull MicroSD card slot (`Hirose DM3D-SF`) is wired over hardware `VSPI`.

* **Power & USB-C Charging:**

* The `USB-C` receptacle (`, 16-pin) uses `5.1kΩ` `CC1`/`CC2` resistors so it works with standard 5V USB-C chargers.

* A `TP4056` linear Li-Ion charger IC is set for `1A` charging (``PROG` resistor).

* An `AP2112K-3.3` `600mA` low-dropout voltage regulator gives 3.3V` power from a `3.7V` LiPo battery.

* A physical `SPDT` slide switch (`SW2`) cuts the power at the hardware level.

* **Physical Controls:** There are 6 push buttons (`Play`, `Pause`, `Next`, `Previous`, `Volume Up`, `Volume Down`). There is also a BOOT` button (`SW1`) and a 4-pin UART programming header (`J3`).

* **Custom 2-Piece Enclosure:** I designed it in FreeCAD with cutouts for USB-C, MicroSD, the slide switch and all 6 buttons. The ESP32 PCB antenna stays clear under resin.

---

## Hardware & CAD Previews

3D PCB Render | JLCPCB Cart (PCB + 3D Case) |

| :---: | :---: |

| <img width="1292" height="763" alt="image" src="https://github.com/user-attachments/assets/b41ca35a-13a5-423c-9555-657957e9cc38" /> | <img width="1912" height="909" alt="image" src="https://github.com/user-attachments/assets/5a30b03f-2c66-41c9-b65d-c77a2e400386" />

---

## GPIO Pinout

| Function | ESP32 GPIO | Notes |

| :--- | :--- | :---

| **MicroSD `CS`** | `GPIO 5` | VSPI Chip Select |

| **MicroSD `SCK`** | `GPIO 18` | VSPI Clock |

| **MicroSD `MISO`** | `GPIO 19` | VSPI Data Out |

| **MicroSD `MOSI`** | `GPIO 23` | VSPI Data In

| **Play** | `GPIO 13` | Active-Low (`INPUT_PULLUP`) |

| **Pause** | `GPIO 14` | Active-Low (`INPUT_PULLUP`) |

| **Next Track** | `GPIO 16` | Active-Low (`INPUT_PULLUP`) |

| **Previous Track** | `GPIO 17` | Active-Low (`INPUT_PULLUP`) |

| **Volume Up** | `GPIO 25` | Active-Low (`INPUT_PULLUP`) |

| **Volume Down** | `GPIO 27` | Active-Low (`INPUT_PULLUP`) |

---

## Firmware Setup & Compilation

1. **Board Package:** Install **`by Espressif Systems (`v3.0.7`)** in the Arduino IDE.

2. **Required Libraries** (install via *Sketch > Include Library > Add.ZIP Library...*):

* [`ESP32-A2DP`](https://github.com)

* [`arduino-audio-tools` (`v1.0.1`)](https://github.com)

* [`arduino-libhelix`](https://github.com)

3. **Arduino IDE Settings:**

* **Board:** `ESP32 Dev Module`

* **Partition Scheme:** `Huge APP (3MB No OTA/1MB SPIFFS)`

4. **Usage:** Put `.mp3` files in the root directory of a FAT32-formatted MicroSD card. Change `BT_DEVICE_NAME` in `Firmware/firmware.ino` if you use headphones. Then flash the board through the 4-pin UART header (`3V3`, `GND`, `TX`, `RX`).

---

## Third-Party Libraries & Licensing

This project leans on open-source ESP32 audio and Bluetooth libraries:

* **[ESP32-A2DP](https://github.com)** by Phil Schatzmann is licensed under the **Apache License 2.0**.

* **[arduino-audio-tools](https://github.com)** by Phil Schatzmann is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.

* **[arduino-libhelix](https://github.com)** by Phil Schatzmann (a wrapper around RealNetworks Helix MP3 decoder) is licensed under the **RealNetworks Public Source License (RPSL) / GPL- terms**.

* **[Arduino-ESP32 Core](https://github.com)** by Espressif Systems is licensed under the **GNU Lesser General Public License v2.1 (LGPL-2.1)**.
