/*
 * ZentriOS SDK LICENSE AGREEMENT | Zentri.com, 2015.
 *
 * Use of source code and/or libraries contained in the ZentriOS SDK is
 * subject to the Zentri Operating System SDK license agreement and
 * applicable open source license agreements.
 *
 */
/* Documentation for this app is available online.
 * See https://docs.zentri.com/wifi/sdk/latest/examples/basic/uart
 */
#include "zos.h"

#define UART_MAX_IRQ_EVENTS 8
#define UART_POLL_PERIOD_MS 100

static uint8_t rx_buffer[1024];
static uint8_t ring_buffer_data[1024];
static uint8_t data[1024];
static uint8_t *ptr = rx_buffer;

static uint8_t conf[4] = {65, 66, 67, 68};

static zos_bool_t toggle1;
static zos_bool_t toggle2;

/*************************************************************************************************/
void zn_app_init(void)
{
    const zos_uart_config_t config =
    {
        .baud_rate = 115200,
        .data_width = UART_WIDTH_8BIT,
        .parity = UART_NO_PARITY,
        .stop_bits = UART_STOP_BITS_1,
        .flow_control = UART_FLOW_DISABLED
    };
    const zos_uart_buffer_t uart_buffer =
    {
        .buffer = ring_buffer_data,
        .length = sizeof(ring_buffer_data)
    };

    // since we're overriding the STD uart we need to ensure the ZentriOS
    // command console is disabled.
    // Note that the cmd console can also be disable by setting the build flag:
    // GLOBAL_DEFINES := ZOS_FLAGS=ZOS_APP_FLAG_DISABLE_CMD_CONSOLE
    zn_cmd_set_console_enabled(ZOS_FALSE);
    zn_event_enable_irq_events(UART_MAX_IRQ_EVENTS);
    zn_uart_configure(PLATFORM_STD_UART, &config, &uart_buffer);
    zn_uart_register_rx_callback(PLATFORM_STD_UART, uart_rx_callback);

    zn_gpio_init(PLATFORM_LED1, GPIO_OUTPUT_PUSHPULL, ZOS_TRUE);
    zn_gpio_init(PLATFORM_LED2, GPIO_OUTPUT_PUSHPULL, ZOS_TRUE);

    ZOS_LOG("UART App Ready. Type something ...");

    uint32_t i = 0;
    for (i = 0; i < 1024; i++)
        data[i] = i+63;

    zn_event_register_periodic(uart_rx_event_handler, NULL, UART_POLL_PERIOD_MS, 0);
    
    transmit_test();

}

static void transmit_test()
{
    zn_uart_transmit_bytes(PLATFORM_STD_UART, data, 20);
}

/*************************************************************************************************
 * Executes in the UART IRQ
 */
// static void uart_rx_callback(uint32_t arg)
// {
//     zn_uart_transmit_bytes(PLATFORM_STD_UART, conf, 4);
//     UNUSED_PARAMETER(arg);
//     ZOS_LOG("test2\n");
//     zn_gpio_set(PLATFORM_LED2, toggle2);
//     toggle2 = !toggle2;
//     // zn_event_issue(uart_rx_event_handler, NULL, EVENT_FLAGS1(FROM_IRQ));
//     // zn_event_register_periodic(uart_rx_event_handler, NULL, UART_POLL_PERIOD_MS, EVENT_FLAGS1(RUN_NOW));
//     // zn_event_register_periodic(uart_rx_event_handler, NULL, UART_POLL_PERIOD_MS, 0);
//     ZOS_LOG("test\n");
// }


/*************************************************************************************************/
static void uart_rx_event_handler(void *arg)
{
    /*
    uint16_t bytes_available;
    const uint8_t *data;
    zn_gpio_set(PLATFORM_LED1, toggle1);
    zn_uart_transmit_bytes(PLATFORM_STD_UART, conf, 2);
    toggle1 = !toggle1;

    zn_uart_peek_bytes(PLATFORM_STD_UART, &data, &bytes_available);

    const uint32_t rx_len = MIN(bytes_available, sizeof(rx_buffer));
    if(rx_len > 0 && zn_uart_receive_bytes(PLATFORM_STD_UART, rx_buffer, rx_len, ZOS_WAIT_FOREVER) == ZOS_SUCCESS)
    {
        zn_uart_transmit_bytes(PLATFORM_STD_UART, rx_buffer, rx_len);
    }
    */

    const uint8_t *dummy;
    uint16_t bytes_read;
    zos_hs_handle_t handle = (zos_hs_handle_t)arg;
    
    // see if the UART had any data available
    zn_uart_peek_bytes(PLATFORM_STD_UART, &dummy, &bytes_read);
    const uint32_t rx_len = MIN(bytes_read, sizeof(rx_buffer));

    // each NMEA message begins with a ($) dollar sign.
    while(bytes_read > 0)
    {
        bytes_read--;
        // read and skip all characters till $ is found (record delimiter)
        // zn_uart_receive_bytes(PLATFORM_STD_UART, ptr, 1, ZOS_NO_WAIT);
        zn_uart_transmit_bytes(PLATFORM_STD_UART, rx_buffer, rx_len);
    }
}


/*************************************************************************************************/
zos_bool_t zn_app_idle(void)
{
    zn_uart_transmit_bytes(PLATFORM_STD_UART, conf, 1);
    return ZOS_TRUE;
}


/*************************************************************************************************/
void zn_app_deinit(void)
{
    // set the callback as NULL to
    zn_uart_register_rx_callback(PLATFORM_STD_UART, NULL);
}
