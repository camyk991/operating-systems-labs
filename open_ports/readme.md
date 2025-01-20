# Open Ports Monitoring Daemon

This project is a Python-based daemon that monitors open ports on the system and logs their status to a file.

## Features

- Monitors open ports in real-time.
- Logs information about open ports to `open_ports.log`.
- Runs as a background service using `systemd`.

## Installation

1. Copy the `open_ports.py` script to your desired location.
2. Create the `opened_ports.service` file in the `/etc/systemd/system/` directory with the following configuration:
   ```ini
   [Unit]
   Description=Opened Ports Daemon
   After=network.target

   [Service]
   ExecStart=/path/to/python /path/to/open_ports.py
   Restart=always
   User=root

   [Install]
   WantedBy=multi-user.target

Replace /path/to/python and /path/to/open_ports.py with the actual paths to your Python interpreter and script.
3. Reload the systemd daemon to apply the changes and start service:
    ```bash
    sudo systemctl daemon-reload
    sudo systemctl enable opened_ports.service
    sudo systemctl start opened_ports.service

## Requirements

- Python 3
- psutil library (install with pip install psutil)