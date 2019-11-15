/**
 * @file can_sci.c
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief CSP CAN driver for SCI module
 * 
 */

#include "can_horizon.h"

uint32_t TxMailbox;

static struct can_stcan_s
{
    CAN_HandleTypeDef hcan1;
    csp_iface_t interface;
} stcan[1] = {
    {
        .interface = {
            .name = "CAN",
            .nexthop = csp_can_tx,
            .mtu = CSP_CAN_MTU,
            .driver = &stcan[0],
        },
    },
};

/* TODO: Use IRQ for RX instead of a thread */
CSP_DEFINE_TASK(stcan_rx_thread)
{

    CAN_RxHeaderTypeDef rx_frame;
    uint8_t RxData[8];

    while (1)
    {
        if (HAL_CAN_GetRxFifoFillLevel(&stcan[0].hcan1, CAN_RX_FIFO0) != 1)
        {
            csp_log_info("RxFifo: empty");
            continue;
        }

        if (HAL_CAN_GetRxMessage(&stcan[0].hcan1, CAN_RX_FIFO0, &rx_frame, RxData) != HAL_OK)
        {
            csp_log_error("CANRx: error");
            continue;
        }

        csp_can_rx(&stcan[0].interface, rx_frame.ExtId, RxData, rx_frame.DLC, NULL);
    }
}

/**
 * @brief Transmits a CAN frame
 * 
 * @param   interface     CSP interface
 * @param   id            Message ID
 * @param   data          Data packet
 * @param   dlc           Data Length Code
 * @return  int           Status code
 */
int csp_can_tx_frame(csp_iface_t *interface, uint32_t id, const uint8_t *data, uint8_t dlc)
{
    CAN_TxHeaderTypeDef tx_frame;
    uint8_t TxData[8];

    int i, tries = 0;

    if (dlc > 8)
        return -1;

    /* Copy identifier (Extended) */
    // tx_frame.StdId = id;
    tx_frame.ExtId = id;
    tx_frame.RTR = CAN_RTR_DATA;
    tx_frame.IDE = CAN_ID_EXT;

    tx_frame.TransmitGlobalTime = DISABLE;

    /* Copy data to frame */
    for (i = 0; i < dlc; i++)
        TxData[i] = data[i];

    /* Set DLC */
    tx_frame.DLC = dlc;

    /* Send frame */
    HAL_CAN_AddTxMessage(&stcan[0].hcan1, &tx_frame, TxData, &TxMailbox);

    /* Wait transmission complete */
    while (HAL_CAN_GetTxMailboxesFreeLevel(&stcan[0].hcan1) != 3)
    {
        if (++tries < 1000)
        {
            /* Wait 10 ms and try again */
            csp_sleep_ms(10);
        }
        else
        {
            csp_log_error("write: error");
            break;
        }
    }

    return 0;
}

/* TODO: Implement CAN Filter (promiscuous) */
/**
 * @brief Initializes CSP CAN Interface
 * 
 * @param   ifc             Interface name (NOT USED)
 * @param   bitrate         Bitrate (1000, 500, 250, 100, 50) Kbit/s
 * @return  csp_iface_t*    CSP interface
 */
csp_iface_t *csp_can_init(const char *ifc, int bitrate)
{
    switch (bitrate)
    {
    case 1000:
        /* 1000 KBit/s */
        stcan->hcan1.Init.Prescaler = 10;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
        break;
    case 500:
        /* 500 KBit/s */
        stcan->hcan1.Init.Prescaler = 10;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
        break;

    case 250:
        /* 250 KBit/s */
        stcan->hcan1.Init.Prescaler = 20;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
        break;

    case 100:
        /* 100 KBit/s */
        stcan->hcan1.Init.Prescaler = 50;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
        break;

    case 50:
        /* 50 KBit/s */
        stcan->hcan1.Init.Prescaler = 100;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
        break;
    default:
        /* 1000 KBit/s */
        stcan->hcan1.Init.Prescaler = 10;
        stcan->hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
        stcan->hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
        break;
    }

    /* Set interface up */
    stcan->hcan1.Instance = CAN1;
    stcan->hcan1.Init.Mode = CAN_MODE;
    stcan->hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    stcan->hcan1.Init.TimeTriggeredMode = DISABLE;
    stcan->hcan1.Init.AutoBusOff = DISABLE;
    stcan->hcan1.Init.AutoWakeUp = DISABLE;
    stcan->hcan1.Init.AutoRetransmission = DISABLE;
    stcan->hcan1.Init.ReceiveFifoLocked = DISABLE;
    stcan->hcan1.Init.TransmitFifoPriority = DISABLE;
    HAL_CAN_Init(&stcan[0].hcan1);

    /* Configure filter 
     * Accepts any ID
     * TODO: use mask
     */
    CAN_FilterTypeDef sFilterConfig;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&stcan[0].hcan1, &sFilterConfig) != HAL_OK)
    {
        csp_log_error("CAN Filter Error\n");
        return (0);
    }

    /* Start CAN peripheral */
    if (HAL_CAN_Start(&stcan[0].hcan1) != HAL_OK)
    {
        /* Start Error */
        csp_log_error("CANSTART: error");
    }

    /* Create receive thread */
    csp_thread_handle_t can_rx_handle;
    csp_thread_create(stcan_rx_thread, "CAN RX", 200, NULL, 0, &can_rx_handle);

    csp_iflist_add(&stcan[0].interface);

    return &stcan[0].interface;
}
