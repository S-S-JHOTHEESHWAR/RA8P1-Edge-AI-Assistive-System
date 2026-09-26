# e² studio Project: Import, Build & Debug Guide

Guide to import, build, and debug the `TRON_V_01` project in Renesas e² studio, including SEGGER RTT Viewer setup.

---

## 📥 1. Importing the Project into e² studio

1. Launch **Renesas e² studio** and open your workspace.
2. In the top menu, go to **File** ➔ **Import...**
3. In the Import wizard, select **General** ➔ **Existing Projects into Workspace** and click **Next >**.
4. In **Select root directory**, click **Browse...** and select the folder:
   ```
   <cloned-repo-path>/e2studio_project/TRON_V_01
   ```
5. Ensure **`TRON_V_01`** is checked in the Projects list.
6. Click **Finish**.

---

## 🔨 2. Building the Project

1. In the **Project Explorer**, right-click **`TRON_V_01`**.
2. Select **Build Configurations** ➔ **Set Active** ➔ **Debug**.
3. Right-click the project and select **Build Project** (or press `Ctrl + B`).
4. Once compilation finishes, verify the output binaries generated in the `Debug/` folder:
   * `TRON_V_01.elf`
   * `TRON_V_01.srec`

---

## 🐞 3. Flashing & Debugging

1. Connect the **EK-RA8P1** board to your PC via a USB cable connected to the onboard **J-Link DEBUG** port (J10).
2. In e² studio, click the dropdown arrow next to the **Debug** (bug) icon on the toolbar and select **Debug Configurations...**
3. Under **Renesas GDB Hardware Debugging**, select **`TRON_V_01 Debug_Flat`**.
4. Under the **Debugger** tab, verify the target settings:
   * **Debug hardware:** `J-Link ARM`
   * **Target Device:** `R7FA8P1BH`
   * **Target Interface:** `SWD`
5. Click **Debug** to flash the firmware.
6. When execution halts at the initial breakpoint, click **Resume (F8)** to start the real-time AI system.

---

## 📟 4. Connecting SEGGER J-Link RTT Viewer

To monitor real-time system logs, RTOS task activity, Ethos-U55 NPU inference timings, and sensor telemetry:

1. Launch **J-Link RTT Viewer**.
2. In the **Configuration** connection dialog, set:
   * **Connection to J-Link:** `USB`
   * **Specify Target Device:** `R7FA8P1BH`
   * **Target Interface & Speed:** `SWD` @ `4000 kHz` (or auto)
   * **RTT Control Block:** Select **Specify Address** and enter:
     ```
     0x22086d98
     ```
3. Click **OK** to connect.
4. You will now see live debug output and performance logs streamed directly from the board over RTT without CPU overhead.

> [!TIP]
> **If the RTT Address cannot be resolved:**
> If RTT Viewer fails to locate the control block (for instance, after modifying code and recompiling), open the linker map file:
> ```
> e2studio_project/TRON_V_01/Debug/TRON_V_01.map
> ```
> Search for **`_SEGGER_RTT`** to find its current memory address (listed under `.bss._SEGGER_RTT`, e.g., `22086d98`), and enter that address in J-Link RTT Viewer.
