#ifndef ADChFunctions


#define ADChFunctions


void initializeADC(void)
{
	//make sure adc is off
	ADC1 ->CR2 &= ~ADC_CR2_ADON;

	//calibrate adc, wait for calibration to complete
	ADC1 ->CR2 |= ADC_CR2_CAL;

	while ((ADC1 ->CR2 & ADC_CR2_CAL) != 0)
	{}

	//initialize and setup the adc clock
	RCC ->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC ->CR |= RCC_CR_HSION;

	//wait for the high speed internal clock ready signal
	while ((RCC ->CR & RCC_CR_HSIRDY) == 0)
	{}

	RCC ->CFGR &= ~RCC_CFGR_ADCPRE;
	ADC1 ->CR2 |= ADC_CR2_ADON;


	ADC1 ->SMPR1 |= ADC_SAMPLETIME_239CYCLES5_SMPR1ALLCHANNELS;

	ADC1 ->CR2 |= ADC_CR2_ADON;
}

//select channel 0 - 17 and conversion sequence number
void sequenceChannelSelADC(uint8_t convNum, uint8_t chanNum)
{
	if(convNum <= 6)
	{
		ADC1 ->SQR3 |= (chanNum << ((convNum - 1) * 5));
	}
	if((convNum <= 12) & (convNum >= 7))
	{
		ADC1 -> SQR2 |= (chanNum << ((convNum - 7) * 5));
	}
	if(convNum >= 13)
	{
		ADC1 -> SQR1 |= (chanNum << ((convNum - 13) * 5));
	}
}

//select the number of conversions to do. this should be the number of times sequenceChannelSelADC is called
void numberOfConversionsADC(uint16_t numberOfConversions)
{
	ADC1 ->SQR1 |= ((numberOfConversions - 1) << 24);
}

#endif
