# ESP32 Bluetooth MP3 Player

This is a pocket-sized Bluetooth MP3 player that stands on its own. It is built around a custom **ESP32-WROOM-32E** PCB and a custom two-piece **3D-printed resin enclosure**. The player reads `.mp3` tracks from a MicroSD card. It decodes stereo audio in time. Then it sends the sound wirelessly through Bluetooth A2DP to headphones (**JBL Tune 770NC**). You control playback and volume with buttons. Anyways I haven't built it as of yet. Here are a the images of the PCB and the schematic with a 3D view from KiCad-
<img width="937" height="838" alt="image" src="https://github.com/user-attachments/assets/22b06971-eb70-452e-8b03-1a285e6df7a0" />  <img width="1136" height="763" alt="image" src="https://github.com/user-attachments/assets/2e49cb6d-9ce2-42e0-8f71-246e6fac5dd1" />
<img width="882" height="535" alt="image" src="https://github.com/user-attachments/assets/f8bcaef7-cf27-4b9b-b4a2-4b8815a2aa7d" />



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

| 3D Enclosure Assembly | JLCPCB Cart (PCB + 3D Case) |
| :---: | :---: |
| ![3D Enclosure Assembly](https://github.com/user-attachments/assets/b41ca35a-13a5-423c-9555-657957e9cc38) | ![JLCPCB Cart](https://github.com/user-attachments/assets/5a30b03f-2c66-41c9-b65d-c77a2e400386) |

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

## Bill of Materials (BOM)

| Qty | Reference | Component | Package / Spec | Supplier | Est. Cost |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **5** | `PCB` | Custom 2-Layer PCB (`72 × 55 mm`) | `1.6 mm` FR-4, Green | JLCPCB | \$4.00 |
| **1** | `CASE` | 3D Printed Upper & Lower Case | `9600` White Resin (SLA) | JLCPCB 3DP | \$2.38 |
| — | `SHIPPING` | JLCPCB Combined Shipping (after coupon) | International Shipping | JLCPCB | -\$0.46 *(Net \$5.92 total)* |
| **1** | `U1` | `ESP32-WROOM-32E` | SMD Module | Robu.in / Evelta | ₹260 (~\$3.05) |
| **1** | `U2` | `TP4056` LiPo Charger IC | `ESOP-8` | Robu.in / ElectronicsComp | ₹15 (~\$0.18) |
| **1** | `U3` | `AP2112K-3.3` 3.3V LDO Regulator | `SOT-23-5` | Evelta / LCSC | ₹20 (~\$0.24) |
| **1** | `J2` | USB-C 16-Pin Receptacle (`USB4105`) | SMD Horizontal | Robu.in / Evelta | ₹35 (~\$0.41) |
| **1** | `J1` | MicroSD Push-Pull Socket (`DM3D-SF`) | SMD | Evelta / LCSC | ₹45 (~\$0.53) |
| **7** | `SW1`, `Play1`, `Pause1`, `Next1`, `Previous1`, `volUp1`, `volDown1` | Tactile Push Button Switch | `6 × 6 mm` Through-Hole | Robu.in / ElectronicsComp | ₹20 (~\$0.24) |
| **1** | `SW2` | SPDT Slide Switch (`PCM12`) | 3-Pin SMD | Robu.in / Evelta | ₹15 (~\$0.18) |
| **4** | `C1, C2, C3, C4` | `10µF` Ceramic Capacitor | `0805` SMD | Robu.in / Evelta | ₹10 (~\$0.12) |
| **2** | `R1, R2` | `10kΩ` Resistor (`EN` & `BOOT`) | `0805` SMD | Robu.in / Evelta | ₹5 (~\$0.06) |
| **2** | `R3, R4` | `5.1kΩ` Resistor (`USB-C CC1/CC2`) | `0805` SMD | Robu.in / Evelta | ₹5 (~\$0.06) |
| **1** | `R5` | `1.2kΩ` Resistor (`TP4056 PROG`) | `0805` SMD | Robu.in / Evelta | ₹5 (~\$0.06) |
| **2** | `J3, J4` | `1×4` UART Header & `1×2` Battery Header | `2.54 mm` Pitch | Robu.in / ElectronicsComp | ₹10 (~\$0.12) |
| **1** | `BAT1` | `3.7V` LiPo Rechargeable Battery | `600mAh` Pouch Cell | Robu.in / ElectronicsComp | ₹250 (~\$2.95) |

**Estimated Grand Total:** **~\$14.12 USD (~₹1,200 INR)** including custom PCBs, resin 3D-printed enclosure, shipping, and all electronic components.

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
