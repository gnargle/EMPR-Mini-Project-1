#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_uart.h"       // Central include files
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "serial.h"
#include "LPC17xx.h"     

#define LED_BITS 0xB40000
#define LED1 0x40000
#define LED2 0x100000
#define LED3 0x200000
#define LED4 0x800000

void SysTick_Handler(void);

int i = 0;

int main (void){
    serial_init();
    GPIO_SetDir(1,LED_BITS,1);   
    SYSTICK_InternalInit(1000);
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_Cmd(ENABLE);
    /*SysTick_Config(SystemCoreClock);*/

    while(1){
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

void SYSTICK_Handler(void){
    GPIO_SetValue(1, LED1);
    if (i == 0){
        GPIO_ClearValue(1, LED_BITS);
        GPIO_SetValue(1, LED1);
        i++;
    }
    else if (i == 1){
        GPIO_ClearValue(1, LED_BITS);
        GPIO_SetValue(1, LED2);
        i++;
    }
    else if (i == 2){
        GPIO_ClearValue(1, LED_BITS);
        GPIO_SetValue(1, LED3);
        i++;
    }
    else if (i == 3){
        GPIO_ClearValue(1, LED_BITS);
        GPIO_SetValue(1, LED4);
        i++;
    }
}
