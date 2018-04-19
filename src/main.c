/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include <stm32f1xx.h>
#include "LCDdriverF.h"
#include "ADC.h"

void send2StrtoLCD(char *str21, char *str22)
{
	sendCmdLCD(LCDclearDsp);
	sendCmdLCD(LCDsetEntr_L1B1);
	sendStrLCD(str21);
	sendCmdLCD(LCDsetEntr_L2B1);
	sendStrLCD(str22);
	badTimDelLCD(1000000);
}

int main(void)
{
initializeADC();
sequenceChannelSelADC(1, 8);
numberOfConversionsADC(1);

	while(1)
	{

		while ((ADC1 ->SR & ADC_SR_EOC) == 0)
		{}
		int read = ADC1->DR;
		sendCmdLCD(LCDsetEntr_L1B1);
		sendStrLCD("Potentiometer = ");
		sendCmdLCD(LCDsetEntr_L2B1);
		sendIntNumberToLCD(read, 8);

	}
}
