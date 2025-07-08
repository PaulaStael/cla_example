//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "scicomm.h"
#include <math.h>

// Parte de compartilhamento de memória

#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM");
float fVal;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM");
float fResult;



void main(void)
{
        Device_init();

        Interrupt_initModule();

        Interrupt_initVectorTable();

        Board_init();
        EINT;
        ERTM;

        for (;;)
        {
            NOP;
        }
    }

    // ISR de retorno da CLA (opcional, mantém atualizações sincronizadas)
    __interrupt void cla1Isr1()
    {
        protocolSendData(SCI0_BASE, &fResult,sizeof(float));
        Interrupt_clearACKGroup(INT_myCLA01_INTERRUPT_ACK_GROUP);
    }

    __interrupt void INT_SCI0_RX_ISR(void)
    {
        protocolReceiveData(SCI0_BASE,&fVal,sizeof(float));
        SCI_clearInterruptStatus(SCI0_BASE, SCI_INT_RXFF);
        Interrupt_clearACKGroup(INT_SCI0_RX_INTERRUPT_ACK_GROUP);


    }

