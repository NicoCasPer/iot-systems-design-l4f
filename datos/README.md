# Datos y evidencia disponibles hasta el Lab 5

Los datos proceden de dos fuentes: los cinco textos **IOT LAB 1–5** aportados por el equipo y los archivos del workspace `IoT_Development_Systems`. Se incorporaron las transcripciones disponibles; no se generaron nuevas mediciones.

## Textos aportados y extractos de consola

Cada `apuntes_y_consola.txt` conserva el texto completo recibido, incluidas las instrucciones, anotaciones y salidas de consola. Los archivos `consola_*.txt` extraen únicamente las secciones de resultados indicadas en la tabla. Las instrucciones y sus ejemplos se conservan como contexto y no se contabilizan como mediciones.

Los datasets Thread completos, sus fragmentos en el eco de consola y otras credenciales identificadas se sustituyeron por `<redactado>`. Los separadores Unicode de línea de los textos pegados se normalizaron a saltos LF para que las referencias de línea funcionen al abrirlos en GitHub. Se conservaron el resto del texto y el orden de los registros. Los adjuntos originales permanecen fuera del repositorio.

| Lab | Texto completo | Extractos y líneas del texto completo | Datos disponibles |
|---|---|---|---|
| 1 | [Apuntes y consola](lab1/apuntes_y_consola.txt) | [Radio](lab1/consola_radio.txt), líneas 95–609 | Pings individuales y resúmenes de pérdida/RTT; tablas de vecinos, RSSI y LQ; distancias anotadas de <1, ≈5, ≈10 y ≈20 m. |
| 2 | [Apuntes y consola](lab2/apuntes_y_consola.txt) | [B](lab2/consola_b.txt), 167–256; [A](lab2/consola_a.txt), 259–876 | Cambios de rol, contadores MAC, vecinos, configuración y resultados de ping. |
| 3 | [Apuntes y consola](lab3/apuntes_y_consola.txt) | [S](lab3/consola_s.txt), 151–471; [C](lab3/consola_c.txt), 475–867 | GET/PUT, CBOR y tamaños CoAP, 34 notificaciones Observe, payload inválido, timeouts y pings con periodos de sondeo de 1, 5 y 15 s. |
| 4 | [Apuntes y consola](lab4/apuntes_y_consola.txt) | [S](lab4/consola_s.txt), 155–423; [C](lab4/consola_c.txt), 430–578 | Lecturas del DS18B20 con timestamp, estadísticas de adquisición, `Sensor lost`, recuperación y respuestas Observe registradas por C. |
| 5 | [Apuntes y consola](lab5/apuntes_y_consola.txt) | [Tarea A](lab5/consola_tarea_a.txt), 158–168 | PSRAM de 8 MB, versiones de Zephyr/OpenThread, respuesta del RCP y estado inicial del host. |

[`procedencia.csv`](procedencia.csv) relaciona los textos completos y los extractos publicados con su fuente y su intervalo de líneas. El campo `sha256_adjunto_original` identifica el adjunto recibido **antes de ocultar credenciales**; no es el hash de la copia publicada. Las fechas de compilación que aparecen en los arranques no se usan como fechas de captura. Los DDR documentan las sesiones de Labs 1–4 del 22–23 de octubre y del Lab 5 del 29 de octubre de 2026.

### Repeticiones y alcance de los registros

- **Lab 3:** las líneas 872–925 del texto completo repiten las respuestas de ping ya presentes en las líneas 823–860. Se conserva esa repetición en el texto completo; el extracto de C termina en la línea 867 y contiene una sola copia de cada serie. Son **10 intentos por periodo**, no dos ensayos independientes. Los replies registrados son 6, 9 y 10 respectivamente.
- **Lab 4:** se mantienen separadas las consolas de S y C. La ML-EID mostrada por S y el destino Observe usado por C en estas transcripciones son distintos; no se sincronizan sus eventos por suposición ni se atribuyen todas las notificaciones al DS18B20 de S.
- **Lab 5:** el texto aporta resultados de la Tarea A, que coinciden con el fragmento ya incluido en el DDR. Las tareas B–F de este texto son instrucciones, sin nuevas salidas de consola de esas pruebas.

## Lecturas del sensor en CSV

[`lab4/lecturas_ds18b20.csv`](lab4/lecturas_ds18b20.csv) contiene las **151 lecturas** de `reading: ds18b20` presentes en la transcripción de S, conservando repeticiones y ventanas separadas. Es una extracción de la consola para facilitar tablas o gráficas.

| Columna | Significado |
|---|---|
| `tiempo_desde_arranque_s` | Timestamp de la consola de S convertido a segundos desde el arranque; no es hora civil. |
| `temperatura_c` | Temperatura impresa por el firmware, sin interpolar ni corregir valores. |
| `linea_apuntes` | Línea de origen en `lab4/apuntes_y_consola.txt`. |

## Archivos del workspace del OTBR

| Archivo | Fecha de origen | Contenido y alcance |
|---|---|---|
| [`lab5/red_otbr_2026-10-29.txt`](lab5/red_otbr_2026-10-29.txt) | 29-oct-2026 | Notas de configuración del OTBR de la sesión documentada en el DDR. No es una serie de mediciones. |
| [`lab5/otbr_consola_2026-11-06_y_13.txt`](lab5/otbr_consola_2026-11-06_y_13.txt) | 6 y 13-nov-2026 | Captura de consola serie con tres aperturas fechadas; corresponde a una réplica posterior. |
| [`lab5/avance.md`](lab5/avance.md) | 6-nov-2026 | Notas de comprobación del host/RCP y preparación de la red. |
| [`lab5/flasheo_2026-11-13.md`](lab5/flasheo_2026-11-13.md) | 13-nov-2026 | Registro de flasheo, tamaños y SHA-256 de las imágenes existentes. No demuestra por sí solo la conectividad entre placas. |

La captura y las notas de red del workspace también ocultan credenciales. En `avance.md` se actualizó el nombre relativo del registro trasladado. Los originales permanecen en el workspace de origen.

## Relación con los DDR y evidencia pendiente

- **Labs 1–4, pareja 1:** [DDR](../ddr/labs1-4_pareja1/DDR.md) y [fotos disponibles](../ddr/labs1-4_pareja1/img/lab4/). Las nuevas transcripciones respaldan los valores de radio, ping, CoAP y sensor ya documentados.
- **Labs 1–4, pareja 2:** [DDR](../ddr/labs1-4_pareja2/DDR.md) y [capturas por laboratorio](../ddr/labs1-4_pareja2/img/). Conservan su propia procedencia.
- **Lab 5, equipo:** [DDR](../ddr/labs5-8_equipo/DDR.md), [fotos del 29 de octubre](../ddr/labs5-8_equipo/img/lab5/) y [fragmento de Tarea A](lab5/consola_tarea_a.txt).

Se mantienen los límites experimentales del DDR: no aparece el escaneo de energía del Lab 1; el Lab 2 no fija el instante de desconexión de B para calcular un tiempo de recuperación; no se registran diez GET con RTT del Lab 3 ni el `5.03` en C durante la falla del sensor del Lab 4. Las lecturas nuevas permiten revisar las curvas térmicas, pero no aportan una medición simultánea de referencia para calibración.

Para el Lab 5, las mediciones de latencia, NAT64 y caída del OTBR de octubre siguen respaldadas por las transcripciones y fotos del DDR; falta su captura completa de consola como archivo independiente. El registro de noviembre se conserva como evidencia adicional de su propia sesión.
