# Avance de la réplica — 6 de noviembre de 2026

## Tarea A: comprobación de host y radio completada

- Puerto S3: `/dev/cu.usbmodem5C850330501`.
- PSRAM detectada: 8 MB.
- Zephyr: `v4.4.0-13939-g2f0bc11264a8`.
- `ot rcp version`: `OPENTHREAD/e4d97681c; Zephyr; Oct 29 2026 16:31:35`, `Done`.
- `ot version`: `OPENTHREAD/e4d97681c; Zephyr; Oct 29 2026 16:31:51`, `Done`.
- No se recompiló ni flasheó: las placas conservan firmware funcional.
- Usuario confirmó conexión física del host y RCP.
- Evidencia de consola en `otbr_consola_2026-11-06_y_13.txt`.

## Tarea B: completada

- Wi-Fi: COMPLETED, iPhone de Oscar T, 2.4 GHz, canal Wi-Fi 6, WPA2-PSK.
- IPv4: 172.20.10.3; gateway: 172.20.10.1.
- Link-local Wi-Fi: fe80::e272:a1ff:fef3:d348.
- Se restauró el dataset histórico de SoilSense-L4F (canal Thread 25).
- Thread: leader; BR: running; NAT64: PrefixManager Active / Translator Active.
- OMR Local/Favored: fd5d:ecb4:d503:1::/64, anunciado con paros.
- Ruta NAT64: fd5d:ecb4:d503:2:0:0::/96, flags sn.
- Tabla de hijos vacía y tabla de routers con solo el OTBR (RLOC16 0x5800) al preparar el traspaso.
- No se modificó el ahorro de energía Wi-Fi; falta medir PS on/off en la tarea D.

## Pendiente: tarea C

Entregar para_companero_tarea_C.md al compañero y esperar estados, estadísticas de sensor, direcciones de S y resultado de 10 pings C→S.
Mantener S3 y RCP alimentados y la consola abierta.
