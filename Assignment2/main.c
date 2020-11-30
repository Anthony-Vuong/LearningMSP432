#include "msp.h"
#include "string.h"
#include "stdio.h"

#define DCOFREQ_1_5 1500000
#define DCOFREQ_3 3000000
#define DCOFREQ_6 6000000
#define DCOFREQ_12 12000000
#define DCOFREQ_24 24000000
#define DCOFREQ_48 48000000

int setDCO(int frequency);
void initializePins();
void delayMs(int delay);
void delayMs(int delay);



int main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	initializePins();

	P2->SEL0 |= BIT0;    //PIN 2.0 GPIO IS RED LED
	P2->SEL1 &= ~BIT0;
	P2->DIR |= BIT0;


	if(setDCO(DCOFREQ_6) == -1){
	    return -1;
	}

    while(1){
        P2->OUT ^= BIT0;
        delayMs(1000);

    }

}

int setDCO(int frequency){

    CS->KEY = CS_KEY_VAL;
    switch(frequency){
        case DCOFREQ_1_5:
            CS->CTL0 = CS_CTL0_DCORSEL_0;
            break;
        case DCOFREQ_3:
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            break;
        case DCOFREQ_6:
            CS->CTL0 = CS_CTL0_DCORSEL_2;
            break;
        case DCOFREQ_12:
            CS->CTL0 = CS_CTL0_DCORSEL_3;
            break;
        case DCOFREQ_24:
            CS->CTL0 = CS_CTL0_DCORSEL_4;
            break;
        case DCOFREQ_48:
            CS->CTL0 = CS_CTL0_DCORSEL_5;
            break;
        default:
            printf("Not a valid DCO option.");
            CS->KEY = 0;
            return -1;
    }
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM_3;
    CS->KEY = 0;

    return 1;
}

void initializePins(){
    // GPIO Port Configuration for lowest power configuration
       P1->OUT = 0x00; P1->DIR = 0xFF;
       P2->OUT = 0x00; P2->DIR = 0xFF;
       P3->OUT = 0x00; P3->DIR = 0xFF;
       P4->OUT = 0x00; P4->DIR = 0xFF;
       P5->OUT = 0x00; P5->DIR = 0xFF;
       P6->OUT = 0x00; P6->DIR = 0xFF;
       P7->OUT = 0x00; P7->DIR = 0xFF;
       P8->OUT = 0x00; P8->DIR = 0xFF;
       P9->OUT = 0x00; P9->DIR = 0xFF;
       P10->OUT = 0x00; P10->DIR = 0xFF;
       PJ->OUT = 0x00; PJ->DIR = 0xFF;

       // Enter LPM0
       __sleep();
       __no_operation();
}


void delayMs(int delay) {
    int i, j;

    for (j = 0; j < delay; j++)
        for (i = 750; i > 0; i--);      /* Delay 1 ms */
}

void delayUs(int dela) {
    int i, j;

    for (j = 0; j < delay; j++)
        for (i = 250; i > 0; i--);      /* Delay 1 us */
}
