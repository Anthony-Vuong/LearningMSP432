#include "msp.h"
#include "string.h"

int main(void)
{
    int validDCO = 0;
    char inputDCO[4] = "3"
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P2->SEL0 |= BIT0;    //PIN 2.0 GPIO IS RED LED
	P2->SEL1 &= ~BIT0;
	P2->DIR |= BIT0;

	validDCO = setDCO(inputDCO);

	if(validDCO == -1){
	    return -1;
	}




	return 0;

}

int setDCO(char* freq){

    CSKEY = CS_KEY_VAL;
    switch(freq){
        case"1.5":
            CS->CTL0 = CS_CTL0_DCORSEL_0;
            break;
        case "3":
            CS->CTL0 = CS_CTL0_DCORSEL_1;
            break;
        case "6":
            CS->CTL0 = CS_CTL0_DCORSEL_2;
            break;
        case "12":
            CS->CTL0 = CS_CTL0_DCORSEL_3;
            break;
        case "24":
            CS->CTL0 = CS_CTL0_DCORSEL_4;
            break;
        case "48":
            CS->CTL0 = CS_CTL0_DCORSEL_5;
            break;
        default:
            printf("Not a valid DCO option.");
            CSKEY = 0;
            return -1;
    }
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM_3;
    CSKEY = 0;

    return 1;
}
