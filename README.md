# 🔵 Triana Bluetooth Sensor Device

![Schematic](docs/images/device_disassembled.png)

A compact hardware device for wirelessly reading body temperature and heart rate using Bluetooth Low Energy (BLE). Built with a custom PCB and 3D-printed casing for **Triana**.

---

## 🖥️ Schematic

> *Circuit connection overview.*

![Schematic](docs/images/schematic.png)

---

## 🔌 PCB Design

> *Top view of the custom PCB layout.*

![PCB Design](docs/images/pcb.png)

---

## 🧱 3D Casing

> *Render or photo of the 3D-printed enclosure.*

![3D Casing](docs/images/casing.png)

---

## ✅ Final Result

> *Photo of the fully assembled hardware.*

![Final Result](docs/images/device_on.png)

---

## 📲 Features

* BLE connection using ESP32
* Reads:

  * Body temperature
  * Heart rate
* Simple command interface via BLE

---

## 🚀 How It Works

1. Power on the device.
2. Connect to the Triana app in `/front_counter/config`
3. Send a command like:

   * `start mlx` → get temperature
   * `start pulse` → get heart rate
4. Data is sent back via BLE.

## 📎 Links

* 🌐 [Triana Web App](https://triana.sportsnow.app)
* 🐙 [GitHub Triana Web Repository](https://github.com/BeeCodingAI/triana-web)
