import sys
import threading
from datetime import datetime
from pathlib import Path
import serial

port = sys.argv[1]
log_path = Path(__file__).with_name('otbr_consola.log')
ser = serial.Serial(port=None, baudrate=115200, timeout=0.2)
ser.dtr = False
ser.rts = False
ser.port = port
ser.open()
log = log_path.open('a', buffering=1)
log.write(f'\n--- Apertura {datetime.now().astimezone().isoformat()} {port} ---\n')
running = threading.Event()
running.set()

def receive():
    while running.is_set():
        try:
            raw = ser.read(4096)
        except serial.SerialException as exc:
            print(f'\nSERIAL ERROR: {exc}', flush=True)
            running.clear()
            break
        if raw:
            output = raw.decode('utf-8', errors='replace')
            log.write(output)
            print(output, end='', flush=True)

thread = threading.Thread(target=receive, daemon=True)
thread.start()
print(f'Consola abierta: {port}. Log local: {log_path}. /exit cierra.', flush=True)
try:
    for line in sys.stdin:
        if line.strip() == '/exit':
            break
        if not running.is_set():
            break
        log.write(f'\n>>> {line}')
        ser.write(line.rstrip('\r\n').encode() + b'\r\n')
        ser.flush()
finally:
    running.clear()
    thread.join(timeout=1)
    ser.close()
    log.close()
