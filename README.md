# RA8P1 Edge AI Assistive System

A physical real-time Edge AI assistive system deployed on the **Renesas EK-RA8P1** microcontroller, powered by **μT-Kernel 3.0 (TRON RTOS)**, **YOLOX-Tiny INT8**, and the **Arm Ethos-U55 NPU**, integrated with external sensor telemetry and hardware-accelerated 2D graphics.

Submitted for the **TRON Programming Contest 2026**.

---

## 🌟 System Overview & Key Features

* **Real-Time Vision AI:** Executes YOLOX-Tiny INT8 on the 500 MHz Arm Ethos-U55-256 MicroNPU (100% offload, 0 CPU fallback, 272/272 operators).
* **Hard Real-Time Multitasking:** Built upon μT-Kernel 3.0 BSP 2.0 with deterministic event-flag synchronization and prioritized task scheduling.
* **Zero-Wait NPU Execution:** Replaces driver polling loops with μT-Kernel 3.0 semaphores (`tk_wai_sem` / `tk_sig_sem`), placing the Cortex-M85 into low-power sleep during inference (0% CPU utilization).
* **30 FPS Video Pipeline:** Parallel VIN/CEU DMA captures 30 FPS video directly into SDRAM; DAVE2D hardware engine performs zero-CPU bitmap blitting and transparent GUI overlay rendering.
* **Environmental Sensor Gateway:** Dedicated ESP32 gateway ingests Sensirion SCD40 CO₂, temperature, and humidity data over UART without impacting camera or AI frame rates.
* **Interactive Touch GUI:** FT5316 capacitive touchscreen interface allowing real-time switching between AI object detection view and live environmental telemetry dashboards.

---

## 📂 Repository Structure

```text
RA8P1-Edge-AI-Assistive-System/
├── e2studio_project/         # Official Renesas e² studio workspace & project
│   ├── README.md             # Guide: Importing, building, debugging, & RTT setup
│   └── TRON_V_01/            # Complete e² studio project (μT-Kernel 3.0 + AI Pipeline)
├── sensor_gateway/           # ESP32 + Sensirion SCD40 telemetry node firmware
│   ├── README.md             # Sensor wiring, pinouts, and UART protocol specification
│   └── sensor_gateway.ino    # Arduino sketch for CO2/Temp/Humidity broadcasting
├── docs/                     # Specialized contest documentation and technical reports
│   ├── uT-Kernel_3.0_Architectural_Significance_Report.md    # Online report
│   ├── uT-Kernel_3.0_Architectural_Significance_Report.pdf   # Publication PDF
│   └── uT-Kernel_3.0_Architectural_Significance_Report.docx  # Word document
├── LICENSE                   # Open-source license
└── README.md                 # System overview and entry portal
```

---

## 🚀 Quick Start Guide

### 1. e² studio Project Setup
Refer to [`e2studio_project/README.md`](./e2studio_project/README.md) for full instructions:
1. Open **e² studio** and choose **File ➔ Import ➔ General ➔ Existing Projects into Workspace**.
2. Select [`e2studio_project/TRON_V_01`](./e2studio_project/TRON_V_01).
3. Build the `Debug` configuration (`Ctrl + B`).
4. Flash and debug via on-board J-Link using `TRON_V_01 Debug_Flat`.
5. Connect **SEGGER J-Link RTT Viewer** to target `R7FA8P1BH` at RTT address:
   ```
   0x22086d98
   ```

### 2. Sensor Gateway Setup
Refer to [`sensor_gateway/README.md`](./sensor_gateway/README.md) for hardware schematics and setup:
1. Connect Sensirion SCD40 to ESP32 via I2C (SDA ➔ GPIO 22, SCL ➔ GPIO 21).
2. Connect ESP32 UART to EK-RA8P1 Header J4 (Pin 8 RXD0, Pin 4 TXD0, Pin 19 GND).
3. Flash [`sensor_gateway/sensor_gateway.ino`](./sensor_gateway/sensor_gateway.ino) using the Arduino IDE.

---

## 📑 μT-Kernel 3.0 Architectural Significance & Justification Report

For in-depth analysis of how **μT-Kernel 3.0** is utilized, including the complete API catalog (`tk_*`), task priority matrices, zero-wait NPU semaphore driver binding, memory maps, and cache coherence strategies:

* 📄 **[Online Technical Significance Report (Markdown)](./docs/uT-Kernel_3.0_Architectural_Significance_Report.md)**
* 📑 **[Download Official PDF Report (.pdf)](./docs/uT-Kernel_3.0_Architectural_Significance_Report.pdf)**
* 📝 **[Download Official Word Report (.docx)](./docs/uT-Kernel_3.0_Architectural_Significance_Report.docx)**
