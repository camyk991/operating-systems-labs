import psutil
import time
from datetime import datetime

LOG_FILE = "./open_ports.log"

while True:
    with open(LOG_FILE, "a") as log_file:
        for conn in psutil.net_connections(kind='inet'):
            if conn.status == "LISTEN":
                log_file.write(
                    f"{datetime.now()} - Port: {conn.laddr.port}, Status: {conn.status}\n"
                )
    time.sleep(60)

