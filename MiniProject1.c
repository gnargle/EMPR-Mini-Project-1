#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"

#include "lpc17xx_uart.h"       // Central include files
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "serial.h" 

#define LED_BITS 0xB40000
#define LED0 0x40000
#define LED1 0x100000
#define LED2 0x200000
#define LED3 0x800000

#define zero 0x0
#define one 0x40000
#define two 0x100000
#define three 0x140000
#define four 0x200000
#define five 0x240000
#define six 0x300000
#define seven 0x340000
#define eight 0x800000
#define nine 0x840000
#define ten 0x900000
#define eleven 0x940000
#define twelve 0xA00000
#define thirteen 0xA40000
#define fourteen 0xB00000
#define fifteen 0xB40000

void SysTick_Handler(void);

int i = 0;
int j = 0;
int k = 5;

int main (void){
    serial_init();
    GPIO_SetDir(1,LED_BITS,1);
    SYSTICK_Cmd(ENABLE);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_InternalInit(100);
    while (1){
        write_usb_serial_blocking("Hello World\n\r", 13);
    }
}

void SysTick_Handler(void){
    if (i < 10){
        i++;
    }
    else{
        Show_Numbers();
    i = 0;
    }
}

void Show_Numbers(void){
    if (k > 0){
        if (j == 0){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, zero);
            j++;
        }
        else if (j == 1){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, one);
            j++;
        }
        else if (j == 2){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, two);
            j++;
        }
        else if (j == 3){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, three);
            j ++;
        }
        else if (j == 4){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, four);
            j ++;
        }
        else if (j == 5){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, five);
            j++;
        }
        else if (j == 6){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, six);
            j++;
        }
        else if (j == 7){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, seven);
            j ++;
        }
        else if (j == 8){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, eight);
            j ++;
        }
        else if (j == 9){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, nine);
            j++;
        }
        else if (j == 10){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, ten);
            j++;
        }
        else if (j == 11){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, eleven);
            j ++;
        }
        else if (j == 12){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, twelve);
            j ++;
        }
        else if (j == 13){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, thirteen);
            j++;
        }
        else if (j == 14){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, fourteen);
            j ++;
        }
        else if (j == 15){
            GPIO_ClearValue(1, LED_BITS);
            GPIO_SetValue(1, fifteen);
            j = 0;
            k--;
        }
    }
    else if (k == 0){
        GPIO_ClearValue(1, LED_BITS);
    }
}

// Read options
int read_usb_serial_none_blocking(char *buf,int length)
{
    return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

// Write options
int write_usb_serial_blocking(char *buf,int length)
{
    return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}

// init code for the USB serial line
void serial_init(void)
{
    UART_CFG_Type UARTConfigStruct;         // UART Configuration structure variable
    UART_FIFO_CFG_Type UARTFIFOConfigStruct;    // UART FIFO configuration Struct variable
    PINSEL_CFG_Type PinCfg;             // Pin configuration for UART
    /*
     * Initialize UART pin connect
     */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    // USB serial first
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 2;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 3;
    PINSEL_ConfigPin(&PinCfg);
        
    /* Initialize UART Configuration parameter structure to default state:
     * - Baudrate = 9600bps
     * - 8 data bit
     * - 1 Stop bit
     * - None parity
     */
    UART_ConfigStructInit(&UARTConfigStruct);
    /* Initialize FIFOConfigStruct to default state:
     * - FIFO_DMAMode = DISABLE
     * - FIFO_Level = UART_FIFO_TRGLEV0
     * - FIFO_ResetRxBuf = ENABLE
     * - FIFO_ResetTxBuf = ENABLE
     * - FIFO_State = ENABLE
     */
    UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
    // Built the basic structures, lets start the devices/
    // USB serial
    UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);        // Initialize UART0 peripheral with given to corresponding parameter
    UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);  // Initialize FIFO for UART0 peripheral
    UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);          // Enable UART Transmit
    
}
