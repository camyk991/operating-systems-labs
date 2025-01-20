# CPU Monitor Kernel Module

This kernel module monitors CPU usage by calculating the percentage of time the CPU is active versus idle. It uses a timer to log the CPU usage at a specified interval.

## Features:
- Logs CPU usage at regular intervals.
- Customizable log interval through the `log_interval` parameter (in milliseconds).

## Installation:
1. Compile the module:
    ```bash
    make
    ```

2. Insert the module with a custom logging interval (e.g., 3000 ms):
    ```bash
    sudo insmod cpumonitor.ko log_interval=3000
    ```

3. Check the log output:
    ```bash
    dmesg
    ```

4. To remove the module:
    ```bash
    sudo rmmod cpumonitor
    ```

## Files:
- `cpumonitor.c`: The kernel module source code.
- `Makefile`: The build script.
