
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
#define TX_FIFO_OCY 0x114
#define RX_FIFO_OCY 0x118

void AXI_IIC_Config();
int main()
{
    init_platform();

     uint32_t  rxBuffer,rxBuffer1;
     AXI_IIC_Config();
     while(1){

	Xil_Out32((IIC_Base_Addr + TX_FIFO), (0x100 | (i2cAddr<<1 )));
	Xil_Out32((IIC_Base_Addr + TX_FIFO), 0x00);
	Xil_Out32((IIC_Base_Addr + TX_FIFO), (0x101 | (i2cAddr<<1 )));
	Xil_Out32((IIC_Base_Addr + TX_FIFO), 0x200 + rxSize);
 	Xil_Out32(IIC_Base_Addr+CR,Xil_In32(IIC_Base_Addr+CR)|0x0d);
	rxBuffer = Xil_In32(IIC_Base_Addr + RX_FIFO);
	for(int i=0;i<9;i++)
			for(int j=0;j<99;j++);
	rxBuffer1 = Xil_In32(IIC_Base_Addr + RX_FIFO) ;

// 	xil_printf("%x\r\n",Xil_In32(IIC_Base_Addr + 0x104));

//	xil_printf("%x  %x\r\n",rxBuffer,rxBuffer1);
	xil_printf("%d°C\r\n",((rxBuffer<<5)|(rxBuffer1>>3))>>4);

	for(int i=0;i<9990;i++)
		for(int j=0;j<999;j++);

   }
    cleanup_platform();
    return 0;
}

void AXI_IIC_Config(){
 Xil_Out32(IIC_Base_Addr+CR,Xil_In32(IIC_Base_Addr+CR)|0x01);
}
