#include "sci_main.h"

#define NUM_FLOATS 9 // Number to be transmitted

typedef union {
	float f;
	char bytes[4];
} float_u;

csp_thread_return_t telemetryTask(void *pvParameters)
{
	xInitLibSci();
	csp_packet_t *packet;
	csp_conn_t *conn;
	for (;;)
	{

		float xyzAccel[3];
		float xyzMag[3];

		/* Acceleration XYZ */
		float_u acc_x;
		float_u acc_y;
		float_u acc_z;

		/* Humidity */
		float_u humidity;

		/* Magnetometer */
		float_u mag_x;
		float_u mag_y;
		float_u mag_z;

		/* Pressure */
		float_u pressure;

		/* Temperature */
		float_u temperature;

		/* Get Acceleration */
		xGetAcceleration(xyzAccel);
		acc_x.f = xyzAccel[0];
		acc_y.f = xyzAccel[1];
		acc_z.f = xyzAccel[2];

		/* Get humidity */
		humidity.f = xGetHumidity();

		/* Get magnetometer data */
		xGetMagnetometer(xyzMag);
		mag_x.f = xyzMag[0];
		mag_y.f = xyzMag[1];
		mag_z.f = xyzMag[2];

		/* Get pressure data */
		pressure.f = xGetPressure();

		/* Get temperature data */
		temperature.f = xGetTemperature();

		printf("ACCELERATION: X:%.2f Y:%.2f Z:%.2f\r\n", xyzAccel[0], xyzAccel[1], xyzAccel[2]);
		printf("HUMIDITY: %.2f\r\n", xGetHumidity());
		printf("MAGNETOMETER: X:%.2f Y:%.2f Z:%.2f\r\n", xyzMag[0], xyzMag[1], xyzMag[2]);
		printf("PRESSURE: %.2f\r\n", xGetPressure());
		printf("TEMPERATURE: %.2f\r\n", xGetTemperature());

		packet = csp_buffer_get(100);
		if (packet == NULL)
		{
			/* Could not get buffer element */
			printf("Failed to get buffer element\n");
			return CSP_TASK_RETURN;
		}
		/* Connect to host HOST, port PORT with regular UDP-like protocol and 1000 ms timeout */
		conn = csp_connect(CSP_PRIO_NORM, 1, TELEM_PORT, 1000, CSP_O_NONE);
		if (conn == NULL)
		{
			/* Connect failed */
			printf("Connection failed\n");
			/* Remember to free packet buffer */
			csp_buffer_free(packet);
			return CSP_TASK_RETURN;
		}

		memcpy(packet->data, acc_x.bytes, sizeof(float));
		memcpy(packet->data + sizeof(float), acc_y.bytes, sizeof(float));
		memcpy(packet->data + 2 * sizeof(float), acc_z.bytes, sizeof(float));
		memcpy(packet->data + 3 * sizeof(float), humidity.bytes, sizeof(float));
		memcpy(packet->data + 4 * sizeof(float), mag_x.bytes, sizeof(float));
		memcpy(packet->data + 5 * sizeof(float), mag_y.bytes, sizeof(float));
		memcpy(packet->data + 6 * sizeof(float), mag_z.bytes, sizeof(float));
		memcpy(packet->data + 7 * sizeof(float), pressure.bytes, sizeof(float));
		memcpy(packet->data + 8 * sizeof(float), temperature.bytes, sizeof(float));
		/* Set packet length */
		packet->length = NUM_FLOATS * sizeof(float);

		/* Send packet */
		if (!csp_send(conn, packet, 1000))
		{
			/* Send failed */
			printf("Send failed\n");
			csp_buffer_free(packet);
		}

		/* Close connection */
		csp_close(conn);
		printf("===================================\r\n");
		csp_sleep_ms(100);
	}
	vTaskDelete(NULL);
}

int main(void)
{
	/* Initialize SCI */
	xSCIInit();

	/* Init buffer system with 3 packets of maximum 300 bytes each */
	csp_buffer_init(3, 300);

	/* Init CSP with address CSP_ADDRESS */
	csp_conf_t csp_conf;
	csp_conf_get_defaults(&csp_conf);
	csp_conf.address = CSP_ADDRESS;
	csp_init(&csp_conf);

	/* Setup CAN interface */
	static csp_iface_t *csp_if_can;
	const char *ifc = "can0";
	csp_if_can = csp_can_init(ifc, 1000); // 1000 Kbit/s bitrate
	csp_rtable_set(CSP_ADDRESS, CSP_ID_HOST_SIZE, csp_if_can, CSP_NODE_MAC);
	csp_rtable_set(CSP_DEFAULT_ROUTE, CSP_ID_HOST_SIZE, csp_if_can, CSP_NODE_MAC);

	/* Start router task with 500 word stack, OS task priority 1 */
	csp_route_start_task(500, 1);

/* Enable debug output from CSP */
// #undef CSP_DEBUG
#ifdef CSP_DEBUG
	/* Print Firmware Info */
	printf("\033[0m========== \033[0;36mNEUDOSE STARS DEMO\033[0m ===========\r\n");
	printf("\033[0;36mNODE: \033[0;33m%s\r\n", TARGET_BOARD);
	printf("\033[0;36mFreeRTOS VERSION: \033[0;33m%s\r\n", tskKERNEL_VERSION_NUMBER);
	printf("\033[0;36mLIBCSP VERSION: \033[0;33m%s\r\n", LIBCSP_VERSION);
	printf("\033[0m======================================\r\n");
	printf("Debug enabled\r\n");
	csp_debug_toggle_level(3);
	csp_debug_toggle_level(4);

	printf("Conn table\r\n");
	csp_conn_print_table();

	printf("Route table\r\n");
	csp_rtable_print();

	printf("Interfaces\r\n");
	csp_iflist_print();
#endif

	csp_thread_handle_t telemtryHandle;
	csp_thread_create(telemetryTask, "Telemetry", 500, NULL, 0, &telemtryHandle);

	vTaskStartScheduler();

	/* Loop forever */
	while (1)
	{
		csp_sleep_ms(100000);
	}
	return 0;
}