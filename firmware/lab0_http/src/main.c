/*
 * Lab 0 - Minimal IoT Implementation (HTTP)
 *
 * Sensing capability:   GET  /api/sensor  -> {"temperature": 24.5}
 * Actuating capability: POST /api/control <- {"state": 0|1}
 *
 * The C6-DevKitC-1's on-board LED is an addressable WS2812 on GPIO8, not a
 * plain GPIO, so it is driven through the led_strip API.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/data/json.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/net/http/server.h>
#include <zephyr/net/http/service.h>
#include <zephyr/net/net_event.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/random/random.h>
#include <zephyr/logging/log.h>

#if !defined(CONFIG_WIFI) || !defined(CONFIG_HTTP_SERVER) || \
	!defined(CONFIG_JSON_LIBRARY) || !defined(CONFIG_LED_STRIP)
#error "TASK 1 is not done yet: add the four capability symbols to prj.conf. \
The lab guide lists them under 'Which subsystems get built'."
#endif

LOG_MODULE_REGISTER(lab0_http, LOG_LEVEL_INF);

static const struct device *const strip = DEVICE_DT_GET(DT_ALIAS(led_strip));

static K_SEM_DEFINE(ipv4_ready, 0, 1);

static struct net_mgmt_event_callback wifi_cb;
static struct net_mgmt_event_callback ipv4_cb;

/* --- Actuating capability ------------------------------------------------ */

struct control_cmd {
	int state;
};

static const struct json_obj_descr control_cmd_descr[] = {
	JSON_OBJ_DESCR_PRIM(struct control_cmd, state, JSON_TOK_NUMBER),
};

static void led_set(int on)
{
	struct led_rgb color = on ? (struct led_rgb){ .r = 0, .g = 32, .b = 0 }
				  : (struct led_rgb){ .r = 0, .g = 0, .b = 0 };

	led_strip_update_rgb(strip, &color, 1);
}

/* --- Sensing capability -------------------------------------------------- */

static int sensor_handler(struct http_client_ctx *client, enum http_transaction_status status,
			  const struct http_request_ctx *request_ctx,
			  struct http_response_ctx *response_ctx, void *user_data)
{
	static uint8_t body[64];
	static const struct http_header headers[] = {
		{ .name = "Content-Type", .value = "application/json" },
		{ NULL, NULL }
	};

	if (status != HTTP_SERVER_REQUEST_DATA_FINAL) {
		return 0;
	}

	/* Simula una temperatura entre 20.0 °C y 29.9 °C */
	float temp = 20.0f + (sys_rand32_get() % 100) / 10.0f;
	int len = snprintf((char *)body, sizeof(body), "{\"temperature\": %.1f}", (double)temp);

	response_ctx->status = HTTP_200_OK;
	response_ctx->headers = headers;
	response_ctx->body = body;
	response_ctx->body_len = len;
	response_ctx->final_chunk = true;

	return 0;
}

static struct http_resource_detail_dynamic sensor_resource_detail = {
	.common = {
		.type = HTTP_RESOURCE_TYPE_DYNAMIC,
		.bitmask_of_supported_http_methods = BIT(HTTP_GET),
	},
	.cb = sensor_handler,
	.user_data = NULL,
};

static int control_handler(struct http_client_ctx *client, enum http_transaction_status status,
			   const struct http_request_ctx *request_ctx,
			   struct http_response_ctx *response_ctx, void *user_data)
{
	static uint8_t payload[64];
	static size_t cursor;
	static const struct http_header headers[] = {
		{ .name = "Content-Type", .value = "application/json" },
		{ NULL, NULL }
	};
	static const char ok_body[] = "{\"status\": \"ok\"}";

	if (status == HTTP_SERVER_TRANSACTION_ABORTED ||
	    status == HTTP_SERVER_TRANSACTION_COMPLETE) {
		cursor = 0;
		return 0;
	}

	/* A small payload can still arrive split across callbacks. */
	if (cursor + request_ctx->data_len > sizeof(payload)) {
		cursor = 0;
		return -ENOMEM;
	}

	memcpy(payload + cursor, request_ctx->data, request_ctx->data_len);
	cursor += request_ctx->data_len;

	if (status == HTTP_SERVER_REQUEST_DATA_FINAL) {
		struct control_cmd cmd = { 0 };
		int ret = json_obj_parse((char *)payload, cursor, control_cmd_descr,
					 ARRAY_SIZE(control_cmd_descr), &cmd);

		if (ret >= 0) {
			led_set(cmd.state);
		}

		response_ctx->status = HTTP_200_OK;
		response_ctx->headers = headers;
		response_ctx->body = (const uint8_t *)ok_body;
		response_ctx->body_len = sizeof(ok_body) - 1;
		response_ctx->final_chunk = true;

		cursor = 0;
	}

	return 0;
}

static struct http_resource_detail_dynamic control_resource_detail = {
	.common = {
		.type = HTTP_RESOURCE_TYPE_DYNAMIC,
		.bitmask_of_supported_http_methods = BIT(HTTP_POST),
	},
	.cb = control_handler,
	.user_data = NULL,
};

/* --- Dashboard: served by the ESP32 itself so the browser and the device
 * share the same origin (no CORS headers needed for the fetch() calls). --- */

static const char index_html[] =
	"<!DOCTYPE html>\n"
	"<html lang=\"es\">\n"
	"<head>\n"
	"<meta charset=\"UTF-8\">\n"
	"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
	"<title>ESP32-C6 Dashboard</title>\n"
	"<style>\n"
	"  body{font-family:sans-serif;max-width:420px;margin:40px auto;text-align:center;background:#111;color:#eee}\n"
	"  .temp{font-size:3rem;margin:20px 0}\n"
	"  button{font-size:1.1rem;padding:12px 24px;margin:8px;border:none;border-radius:8px;cursor:pointer;color:#fff}\n"
	"  .on{background:#2ecc71}\n"
	"  .off{background:#e74c3c}\n"
	"  #status{margin-top:10px;color:#888;font-size:.9rem}\n"
	"</style>\n"
	"</head>\n"
	"<body>\n"
	"  <h1>ESP32-C6 IoT Dashboard</h1>\n"
	"  <div class=\"temp\" id=\"temp\">-- &deg;C</div>\n"
	"  <button class=\"on\" onclick=\"setLed(1)\">Encender LED</button>\n"
	"  <button class=\"off\" onclick=\"setLed(0)\">Apagar LED</button>\n"
	"  <div id=\"status\"></div>\n"
	"<script>\n"
	"async function poll(){\n"
	"  try{\n"
	"    const r = await fetch('/api/sensor');\n"
	"    const d = await r.json();\n"
	"    document.getElementById('temp').textContent = d.temperature.toFixed(1) + ' \\u00b0C';\n"
	"    document.getElementById('status').textContent = 'Actualizado ' + new Date().toLocaleTimeString();\n"
	"  }catch(e){\n"
	"    document.getElementById('status').textContent = 'Error de conexion con el ESP32';\n"
	"  }\n"
	"}\n"
	"async function setLed(state){\n"
	"  try{\n"
	"    await fetch('/api/control', {\n"
	"      method: 'POST',\n"
	"      headers: {'Content-Type': 'application/json'},\n"
	"      body: JSON.stringify({state})\n"
	"    });\n"
	"  }catch(e){\n"
	"    document.getElementById('status').textContent = 'Error al enviar comando';\n"
	"  }\n"
	"}\n"
	"poll();\n"
	"setInterval(poll, 2000);\n"
	"</script>\n"
	"</body>\n"
	"</html>\n";

static struct http_resource_detail_static index_html_resource_detail = {
	.common = {
		.type = HTTP_RESOURCE_TYPE_STATIC,
		.bitmask_of_supported_http_methods = BIT(HTTP_GET),
		.content_type = "text/html",
	},
	.static_data = index_html,
	.static_data_len = sizeof(index_html) - 1,
};

static uint16_t http_port = 80;

HTTP_SERVICE_DEFINE(iot_service, NULL, &http_port, 2, 4, NULL, NULL, NULL);
HTTP_RESOURCE_DEFINE(index_resource, iot_service, "/", &index_html_resource_detail);
HTTP_RESOURCE_DEFINE(sensor_resource, iot_service, "/api/sensor", &sensor_resource_detail);
HTTP_RESOURCE_DEFINE(control_resource, iot_service, "/api/control", &control_resource_detail);

/* --- Interface capability: join the Wi-Fi network ------------------------ */

static void wifi_event_handler(struct net_mgmt_event_callback *cb, uint64_t event,
			       struct net_if *iface)
{
	const struct wifi_status *st = (const struct wifi_status *)cb->info;

	if (event == NET_EVENT_WIFI_CONNECT_RESULT) {
		if (st->status) {
			LOG_ERR("Wi-Fi association failed (%d)", st->status);
		} else {
			LOG_INF("Associated with \"%s\"", CONFIG_LAB_WIFI_SSID);
		}
	} else if (event == NET_EVENT_WIFI_DISCONNECT_RESULT) {
		LOG_WRN("Wi-Fi disconnected");
	}
}

static void ipv4_event_handler(struct net_mgmt_event_callback *cb, uint64_t event,
			       struct net_if *iface)
{
	if (event != NET_EVENT_IPV4_ADDR_ADD) {
		return;
	}

	for (int i = 0; i < NET_IF_MAX_IPV4_ADDR; i++) {
		char buf[NET_IPV4_ADDR_LEN];

		if (iface->config.ip.ipv4->unicast[i].ipv4.addr_type != NET_ADDR_DHCP) {
			continue;
		}

		LOG_INF("IPv4 address: %s",
			net_addr_ntop(AF_INET,
				      &iface->config.ip.ipv4->unicast[i].ipv4.address.in_addr,
				      buf, sizeof(buf)));
		k_sem_give(&ipv4_ready);
	}
}

static int wifi_connect(void)
{
	struct net_if *iface = net_if_get_first_wifi();
	struct wifi_connect_req_params params = { 0 };

	if (iface == NULL) {
		LOG_ERR("No Wi-Fi interface found");
		return -ENODEV;
	}

	params.ssid = (const uint8_t *)CONFIG_LAB_WIFI_SSID;
	params.ssid_length = strlen(CONFIG_LAB_WIFI_SSID);
	params.psk = (const uint8_t *)CONFIG_LAB_WIFI_PSK;
	params.psk_length = strlen(CONFIG_LAB_WIFI_PSK);
	params.security = WIFI_SECURITY_TYPE_PSK;
	params.channel = WIFI_CHANNEL_ANY;
	params.band = WIFI_FREQ_BAND_2_4_GHZ;
	params.mfp = WIFI_MFP_OPTIONAL;

	LOG_INF("Connecting to \"%s\"...", CONFIG_LAB_WIFI_SSID);

	return net_mgmt(NET_REQUEST_WIFI_CONNECT, iface, &params, sizeof(params));
}

int main(void)
{
	if (!device_is_ready(strip)) {
		LOG_ERR("LED strip device not ready");
		return -ENODEV;
	}
	led_set(0);

	net_mgmt_init_event_callback(&wifi_cb, wifi_event_handler,
				     NET_EVENT_WIFI_CONNECT_RESULT |
					     NET_EVENT_WIFI_DISCONNECT_RESULT);
	net_mgmt_add_event_callback(&wifi_cb);

	net_mgmt_init_event_callback(&ipv4_cb, ipv4_event_handler, NET_EVENT_IPV4_ADDR_ADD);
	net_mgmt_add_event_callback(&ipv4_cb);

	if (wifi_connect() != 0) {
		LOG_ERR("Wi-Fi connect request failed");
		return -EIO;
	}

	k_sem_take(&ipv4_ready, K_FOREVER);

	http_server_start();
	LOG_INF("HTTP server listening on port %u", http_port);

	return 0;
}