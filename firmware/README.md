# Firmware — Labs 0–5

Copia de los proyectos disponibles en el workspace `IoT_Development_Systems` del equipo, preparada para la entrega hasta el Lab 5. Se conservan los nombres de las aplicaciones, sus fuentes, `CMakeLists.txt`, configuraciones, overlays y scripts de enlace. El código base procede del [repositorio del curso](https://github.com/saacifuentesmu/4201327-iot_systems_design).

Esta copia recoge el estado disponible del workspace; no es un historial de versiones de cada sesión experimental. Las mediciones y decisiones permanecen en los [DDR](../README.md). Los registros disponibles se describen en [`datos/`](../datos/README.md).

## Proyectos

| Laboratorio | Carpeta | Uso / placa |
|---|---|---|
| 0 — HTTP | [`lab0_http/`](lab0_http/) | Aplicación HTTP sobre Wi-Fi, ESP32-C6 |
| 0 — MQTT | [`lab0_mqtt/`](lab0_mqtt/) | Cliente MQTT, dashboard HTML y configuración de Mosquitto, ESP32-C6 |
| 1 — Radio | [`lab1_radio/`](lab1_radio/) | Caracterización IEEE 802.15.4, ESP32-C6 |
| 2 — Mesh | [`lab2_mesh/`](lab2_mesh/) | Malla Thread, ESP32-C6 |
| 3 — CoAP | [`lab3_coap/`](lab3_coap/) | `/env/temp`, Observe y `/act/valve`, ESP32-C6 |
| 4 — Sensores | [`lab4_sensors/`](lab4_sensors/) | Sensor real y validez de lecturas, ESP32-C6 |
| 5 — Nodos S y C | [`lab4_5_sensors/`](lab4_5_sensors/) | Variante de sensores con SLAAC y potencia de transmisión de 20 dBm explícitos |
| 5 — Radio del OTBR | [`lab5_rcp/`](lab5_rcp/) | RCP OpenThread sobre UART/Spinel, ESP32-C6 |
| 5 — Host del OTBR | [`lab5_border_router/`](lab5_border_router/) | Border router Wi-Fi/Thread y NAT64, ESP32-S3 con PSRAM |

`lab4_5_sensors` conserva los mismos fuentes de `lab4_sensors`; su `prj.conf` añade `CONFIG_OPENTHREAD_SLAAC=y` y `CONFIG_OPENTHREAD_DEFAULT_TX_POWER=20`. Para los nodos del Lab 5 se usa esta variante: SLAAC permite obtener la dirección OMR anunciada por el border router. El DDR histórico llama a la aplicación de sensores `lab4_sensors`.

## Dependencias

[`manifest/west.yml`](manifest/west.yml) conserva el manifiesto del workspace y fija Zephyr al commit `2f0bc11264a8e72e214f3db0a3fa221eb022453a`. El workspace consultado tiene Zephyr en esa revisión. Los builds existentes del OTBR y el RCP registran **Zephyr SDK 1.0.1**, con toolchains Xtensa ESP32-S3 y RISC-V ESP32-C6.

Las [transcripciones originales](../datos/README.md) de los Labs 3–4 registran otros builds históricos: S imprime `v4.4.0-14199-g4c6971ba90a3` y C imprime `v4.4.2`. El manifiesto copiado describe el workspace disponible y los builds del OTBR; no identifica por sí solo la revisión de todas las imágenes usadas en esas sesiones anteriores.

Para preparar un clon nuevo, desde la raíz del repositorio:

```bash
cd firmware
python3 -m venv .venv
source .venv/bin/activate
python -m pip install west
west init -l manifest
west update
west zephyr-export
west packages pip --install
west blobs fetch hal_espressif
```

Se requiere el SDK y los toolchains indicados. Si el SDK no se detecta automáticamente, configurar `ZEPHYR_SDK_INSTALL_DIR` con la ruta de su instalación. `deps/`, `.west/`, entornos virtuales y compilaciones se generan localmente y están excluidos de Git.

## Compilar y flashear

Los siguientes comandos se ejecutan desde `firmware/`, con el entorno Zephyr activo. Cada aplicación tiene un directorio de build propio:

```bash
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab1_radio -d build/lab1
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab2_mesh -d build/lab2
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab3_coap -d build/lab3

# Lab 4: S con DS18B20; para DHT22 usar sensors/dht22.overlay.
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab4_sensors -d build/lab4_s -- -DEXTRA_DTC_OVERLAY_FILE=sensors/ds18b20.overlay

# Lab 5: S con DHT22 y C sin overlay de sensor.
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab4_5_sensors -d build/lab5_s -- -DEXTRA_DTC_OVERLAY_FILE=sensors/dht22.overlay
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab4_5_sensors -d build/lab5_c

# Lab 5: radio RCP y host S3.
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab5_rcp -d build/rcp
west build -p always -b esp32s3_devkitc/esp32s3/procpu lab5_border_router -d build/br
```

Para flashear, sustituir el puerto por el de la placa correspondiente:

```bash
west flash -d build/lab1 --esp-device <PUERTO_DE_LA_PLACA>
```

En el OTBR, flashear S3 y RCP por separado, sin los jumpers. Con ambas placas apagadas, conectar S3 GPIO5 (TX) → C6 GPIO4 (RX), S3 GPIO4 (RX) → C6 GPIO5 (TX) y GND → GND. Alimentar primero el RCP y luego el S3. Consultar `ot rcp version` desde la consola del S3 para verificar el enlace.

## Wi-Fi de los Labs 0

Las copias de `lab0_http/prj.conf` y `lab0_mqtt/prj.conf` usan `changeme` para SSID y contraseña. Crear `local.conf` dentro de la aplicación que se vaya a compilar:

```ini
CONFIG_LAB_WIFI_SSID="NOMBRE_DE_SU_RED"
CONFIG_LAB_WIFI_PSK="CONTRASENA_DE_SU_RED"
```

Desde `firmware/`, compilar con esa configuración adicional:

```bash
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab0_http -d build/lab0_http -- -DEXTRA_CONF_FILE=local.conf
west build -p always -b esp32c6_devkitc/esp32c6/hpcore lab0_mqtt -d build/lab0_mqtt -- -DEXTRA_CONF_FILE=local.conf
```

`local.conf` está excluido de Git. Para MQTT, ajustar también `CONFIG_LAB_BROKER_ADDR` y `CONFIG_LAB_BROKER_PORT` al broker de la sesión. Las credenciales originales se conservan únicamente en el workspace de origen.

## Herramientas del Lab 5

[`tools/`](tools/) incluye el dashboard CoAP y la consola serie disponibles en la sesión del equipo. [`requirements.txt`](tools/requirements.txt) registra las versiones encontradas en sus entornos Python.

Desde `firmware/`, con el entorno virtual activo:

```bash
python -m pip install -r tools/requirements.txt
python tools/dashboard_coap.py --host <DIRECCION_OMR_DE_S>
```

El portátil debe tener conectividad IPv6 hacia S a través del OTBR. Abrir `http://localhost:5000`; desde el celular, usar la IPv4 del portátil y el puerto 5000 estando en la misma red Wi-Fi. También se conserva el modo serie para Labs 3–4:

```bash
python tools/dashboard_coap.py --serial <PUERTO_DE_C> --node <ML_EID_DE_S>
python tools/consola_otbr.py <PUERTO_UART_DEL_S3>
```

La consola genera un `otbr_consola.log` local, ignorado por Git: puede contener credenciales introducidas durante la sesión. Los modos DTLS/Labs 6–8 que aparecen en el dashboard original requieren `coaps.py`, que no está en el workspace copiado y queda fuera de esta entrega.

## Alcance de la copia

Se excluyeron builds, binarios generados, dependencias descargadas, entornos virtuales y ajustes del editor. Los proyectos conservan su contenido original salvo la sustitución de SSID/contraseña en los Labs 0. Los registros publicados sustituyen las credenciales por `<redactado>`; sus fechas y procedencia están en el [inventario de datos](../datos/README.md).
