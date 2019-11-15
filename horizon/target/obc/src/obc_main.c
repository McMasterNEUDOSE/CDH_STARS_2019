#include "obc_main.h"

csp_thread_return_t collectionTask(void *pvParameters)
{
    /* Create socket without any socket options */
    csp_socket_t *sock = csp_socket(CSP_SO_NONE);
    /* Bind all ports to socket */
    csp_bind(sock, CSP_ANY);
    /* Create 10 connections backlog queue */
    csp_listen(sock, 10);
    /* Pointer to current connection and packet */
    csp_conn_t *conn;
    csp_packet_t *packet;

    while (1)
    {
        /* Wait for connection, 10000 ms timeout */
        if ((conn = csp_accept(sock, 10000)) == NULL)
            continue;

        /* Read packets. Timout is 100 ms */
        while ((packet = csp_read(conn, 100)) != NULL)
        {
            switch (csp_conn_dport(conn))
            {
            case TELEM_PORT:
                /* Process packet here */
                printf("Telemtry received\r\n");
                const unsigned char SYNC = 0x16;
                const unsigned char TELEM = 0x01;
                printf("%02x", SYNC);
                printf("%02x", TELEM);
                for (int i = 0; i < packet->length; i++)
                {
                    printf("%02x", packet->data[i]);
                }
                printf("\r\n");
                csp_buffer_free(packet);
                break;
            default:
                /* Let the service handler reply pings, buffer use, etc. */
                csp_service_handler(conn, packet);
                break;
            }
        }

        /* Close current connection, and handle next */
        csp_close(conn);
    }
}

int main(void)
{
    xOBCInit();

    /* Init buffer system with 3 packets of maximum 300 bytes each */
    csp_buffer_init(3, 300);

    /* Init CSP with address MY_ADDRESS */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    csp_conf.address = CSP_ADDRESS;
    csp_init(&csp_conf);

    /* Setup CAN interface */
    static csp_iface_t *csp_if_can;
    const char *ifc = "can0";
    csp_if_can = csp_can_init(ifc, 1000); // 1000 Kbit/s bitrate, promisc ON
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

    csp_thread_handle_t collectionHandle;
    csp_thread_create(collectionTask, "Collection", 300, NULL, 0, &collectionHandle);

    vTaskStartScheduler();

    /* Loop forever */
    while (1)
    {
        csp_sleep_ms(100000);
    }
    return 0;
}