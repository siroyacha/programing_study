#include <stdio.h>

int main(void)
{
	/*
	int i = 0;

	while (i<10)
	{
		printf_s("Hello World!\n");
		i++;
	}
	*/

	int iFahrenheit, iCelsius = 0;
	int iLower, iUpper, iStep;

	iLower = 0;
	iUpper = 300;
	iStep = 20;
	iFahrenheit = iLower;

	while (iFahrenheit<=iUpper)
	{
		iCelsius = 5 * (iFahrenheit - 32) / 9;
		printf_s("È­¾¾ : %d\t¼·¾¾ : %d\n", iFahrenheit, iCelsius);
		iFahrenheit += iStep;
	}

	printf_s("\n");
	
	return 0;
}