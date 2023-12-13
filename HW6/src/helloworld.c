
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"

#define IIC_Base_Addr   0x40800000

#define i2cAddr 0x4b
#define rxSize  2
#define CR      0x100
#define TX_FIFO 0x108
#define RX_FIFO 0x10C

void AXI_IIC_Config();

int main()
{
    init_platform();

    unsigned int rxBuffer;

    AXI_IIC_Config();

	Xil_Out32((IIC_Base_Addr + TX_FIFO), (0x100 | (i2cAddr<<1 )));
	Xil_Out32((IIC_Base_Addr + TX_FIFO), 0x0B);
	Xil_Out32((IIC_Base_Addr + TX_FIFO), (0x101 | (i2cAddr<<1 )));
	Xil_Out32((IIC_Base_Addr + TX_FIFO), 0x200 + 2);

	rxBuffer = Xil_In32(IIC_Base_Addr + RX_FIFO) ;

	xil_printf("%d",rxBuffer);

	for(int i=0;i<999;i++)
		for(int j=0;j<999;j++);


    cleanup_platform();
    return 0;
}

void AXI_IIC_Config(){
    Xil_Out32(IIC_Base_Addr+CR,Xil_In32(IIC_Base_Addr+CR)|0x01);
}