# e² studio Project Guide: μT-Kernel 3.0 Vision AI on Renesas RA8P1

This directory contains the official Renesas **e² studio** project (`TRON_V_01`) for the **RA8P1 Edge AI Assistive System** submitted to the TRON Programming Contest.

---

## 📋 System Requirements & Prerequisites

Before importing the project, ensure you have the following software installed:

* **IDE:** [Renesas e² studio](https://www.renesas.com/software-tool/e-studio) (Version 2024-01 or later recommended).
* **FSP (Flexible Software Package):** Renesas FSP for RA Series (v5.3.0 or higher with RA8P1 board support package).
* **Compiler:** GNU Arm Embedded Toolchain (`arm-none-eabi-gcc` 13.x or compatible LLVM toolchain).
* **Debug Probe:** SEGGER J-Link Software and Documentation Pack (integrated into e² studio or standalone v7.90+).
* **Target Hardware:**
  * **MCU Board:** Renesas **EK-RA8P1** (R7FA8P1BHECBD - Cortex-M85 @ 480 MHz + Arm Ethos-U55 NPU @ 500 MHz).
  * **Camera Module:** OmniVision OV5640 5MP CMOS camera connected via parallel VIN/CEU interface.
  * **Display Panel:** 800x480 / 640x480 RGB TFT LCD panel connected via GLCDC interface.
  * **(Optional) Telemetry Sensor Hub:** ESP32 + Sensirion SCD40 (CO₂, temperature, humidity) connected via SCI0 UART.

---

## 🚀 Step-by-Step: Importing the Project into e² studio

Follow these steps to import and build `TRON_V_01`:

### 1. Open e² studio
* Launch **Renesas e² studio**.
* Select or create a workspace directory of your choice (e.g., `C:\Users\<username>\e2_studio\workspace`).

### 2. Import the Project
1. In the top menu, go to **File** ➔ **Import...**
2. In the Import dialog, expand the **General** folder.
3. Select **Existing Projects into Workspace** and click **Next >**.
4. In the **Select root directory** field, click **Browse...** and navigate to the directory where this repository was cloned:
   ```
   <cloned-repo-path>/e2studio_project/TRON_V_01
   ```
5. In the **Projects** list, verify that **`TRON_V_01`** is detected and checked.
6. *(Optional)* If you want to keep working in the cloned repository location, leave **"Copy projects into workspace" unchecked**. If you prefer a separate copy in your workspace, check it.
7. Click **Finish**.

---

## ⚙️ FSP Configuration & Code Generation

1. In the **Project Explorer** window, locate the imported **`TRON_V_01`** project.
2. Double-click the **`configuration.xml`** file located in the root of `TRON_V_01` to open the Renesas FSP Configurator.
3. Verify that the target device is set to **`R7FA8P1BHECBD`** and board is **`EK-RA8P1`**.
4. In the upper right corner of the FSP configuration perspective, click **Generate Project Content** to ensure all BSP drivers, vector tables, and pin mappings are synchronized.

---

## 🔨 Building the Project

1. Right-click on **`TRON_V_01`** in the Project Explorer.
2. Select **Build Configurations** ➔ **Set Active** ➔ **Debug**.
3. Right-click the project and select **Build Project** (or use the shortcut `Ctrl + B` / click the hammer icon on the toolbar).
4. The build process will compile:
   * **μT-Kernel 3.0 RTOS Core:** Preemptive multitasking kernel, event flags, semaphores, and memory management (`mtk3_bsp2/`).
   * **Arm Ethos-U55 NPU Driver:** MicroNPU runtime and INT8 model layers (`src/ai_app/`).
   * **Hardware Drivers:** Parallel VIN (OV5640 Camera DMA), GLCDC (LCD Controller), DAVE2D graphics engine, Octal-SPI (OSPI CS1 high-speed DDR mode), and SCI0 UART.
5. Check the Console output to confirm the build succeeds with `0 errors` and generates:
   ```
   Debug/TRON_V_01.elf
   Debug/TRON_V_01.srec
   ```

---

## 🐞 Flashing and Debugging on EK-RA8P1

1. Connect your **EK-RA8P1** board to your PC via a micro-USB / Type-C cable plugged into the onboard **J-Link DEBUG** port (J10).
2. Ensure jumpers are configured for normal boot (single-chip mode, J-Link on-board enabled).
3. In e² studio:
   * Click the dropdown arrow next to the **Debug** (bug) icon on the toolbar.
   * Select **Debug Configurations...**
   * Under **Renesas GDB Hardware Debugging**, choose **`TRON_V_01 Debug_Flat`** (or create a new launch configuration selecting `J-Link ARM` and device `R7FA8P1BH`).
   * Under the **Debugger** tab, verify:
     * **Debug hardware:** `J-Link ARM`
     * **Target Device:** `R7FA8P1BH`
     * **Target Interface:** `SWD`
4. Click **Debug**.
5. Once the debugger halts at `hal_entry()` or `PowerON_Reset()`, click **Resume (F8)** to run the real-time AI pipeline.

---

## 📡 Optional: ESP32 Telemetry Transmitter Setup

The project includes an optional sensor hub sketch in [`esp32_transmitter/esp32_scd40_ra8p1.ino`](./TRON_V_01/esp32_transmitter/esp32_scd40_ra8p1.ino) to stream environmental data (CO₂, temperature, humidity) directly into the RTOS GUI over UART.

### Hardware Connections:
| EK-RA8P1 Expansion Header J4 | Function | Connected ESP32 Pin |
| :--- | :--- | :--- |
| **J4 Pin 8** | `RXD0` (P602) | **ESP32 GPIO 4** (Pin D4 / TX) |
| **J4 Pin 4** | `TXD0` (P603) | **ESP32 GPIO 16** (Pin RX2 / RX) |
| **J4 Pin 19** | **GND** | **ESP32 GND** (Common Reference) |

---

## 📂 Project Structure Overview

```text
e2studio_project/
├── README.md               # This import & setup guide
└── TRON_V_01/              # e² studio project root
    ├── .project            # Eclipse project definition
    ├── .cproject           # C/C++ compiler and build settings
    ├── configuration.xml   # Renesas FSP peripheral and pin configuration
    ├── mtk3_bsp2/          # μT-Kernel 3.0 RTOS kernel and BSP layer
    ├── src/
    │   ├── hal_entry.c     # RTOS initialization, task creations, and main loops
    │   ├── hal_warmstart.c # High-speed OSPI Octal-DDR init & warm-start hooks
    │   ├── ai_app/         # YOLOX-Tiny INT8 inference on Arm Ethos-U55 NPU
    │   ├── camera/         # OV5640 sensor init and VIN DMA frame capture
    │   ├── display_layer/  # GLCDC layer blending & DAVE2D accelerated rendering
    │   └── esp32/          # SCI0 UART asynchronous driver & telemetry parser
    ├── esp32_transmitter/  # Arduino/ESP32 firmware for SCD40 sensor broadcasting
    └── Debug/              # Precompiled binaries (.elf, .srec, .map)
```
