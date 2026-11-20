# IoT Systems Design — Equipo L4F (Los4Fantasticos)

Repositorio del equipo para **Desarrollo de Sistemas IoT** (4201327), Universidad Nacional de Colombia, 2026-2.

| Integrante | Labs 1–4 | Labs 5–8 |
|---|---|---|
| Nicolas Castaño | Pareja 1 | Equipo |
| Oscar Andres Tepud | Pareja 1 | Equipo |
| Anderson Kaleth Angel | Pareja 2 | Equipo |
| Camilo Obando | Pareja 2 | Equipo |

## Organización

| Carpeta | Contenido |
|---|---|
| [`ddr/labs1-4_pareja1/`](ddr/labs1-4_pareja1/DDR.md) | DDR de la pareja 1, labs 1–4 |
| [`ddr/labs1-4_pareja2/`](ddr/labs1-4_pareja2/DDR.md) | DDR de la pareja 2, labs 1–4 |
| [`ddr/labs5-8_equipo/`](ddr/labs5-8_equipo/DDR.md) | DDR del equipo completo, labs 5–8 |
| [`firmware/`](firmware/README.md) | Código y configuraciones de los labs 0–5, herramientas y dependencias de Zephyr |
| [`datos/`](datos/README.md) | Transcripciones y consolas de Labs 1–5, lecturas del sensor en CSV y procedencia |
| [`presentacion_lorawan/`](presentacion_lorawan/) | Presentación sobre LoRaWAN (13-nov-2026) |
| [`proyecto_final/`](proyecto_final/) | Business case y pitch final |

Cada DDR sigue la [plantilla del curso](https://github.com/saacifuentesmu/4201327-iot_systems_design/blob/main/docs/ddr_template.md) y guarda su evidencia (fotos, capturas) en su carpeta `img/labN/`.

La copia del firmware del workspace del equipo está en [`firmware/`](firmware/README.md), organizada por laboratorio e incluyendo la variante de sensores para el Lab 5. El código base y las guías provienen del [repo del curso](https://github.com/saacifuentesmu/4201327-iot_systems_design). Las instrucciones de compilación y las diferencias entre versiones están en el README de firmware.

Para la entrega hasta el **Lab 5**, consultar los dos DDR de pareja (Labs 1–4) y el DDR del equipo (Lab 5). Las fotos y las transcripciones incluidas en los DDR conservan su contexto; el [inventario de datos](datos/README.md) precisa qué archivos de consola están disponibles y qué registros originales faltan.

## Reglas

- **No subir secretos:** claves de Wi-Fi o del hotspot, la Network Key de Thread, datasets en hex ni tokens. Si una evidencia los muestra, reemplazarlos por `<redactado>`.
- Nombres de archivo en minúsculas, sin espacios ni tildes (por ejemplo `img/lab5/d_dashboard_celular.jpg`).
- Un commit por cambio lógico, con un mensaje que diga qué lab o sección se actualizó.
