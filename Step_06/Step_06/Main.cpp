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

	/*
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
	*/
	
	/*
	for (int i = 0; i < 10; i++)
	{
		printf_s("LoopCount! : %d\n", i);
	}

	for (int i = 2; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			printf_s("%d X %d = %003d  ", i, j, i * j);
		}
		printf_s("\n");
	}
	printf_s("\n");
	*/
	
	double cost = 24.0f;
	for (int i = 1627; i < 2021; i++)
	{
		cost = cost+(cost * 0.08f);
	}
	printf_s("ÇöÀç °¡Ä¡´Â ¾à %.2f´Þ·¯\n", cost);
	

	/*
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j < i; j++)
		{
			printf_s("*");
		}
		printf_s("\n");
	}
	printf_s("\n");

	for (int i = 0; i < 10; i++)
	{
		for (int j = 10; j > i; j--)
		{
			printf_s("*");
		}
		printf_s("\n");
	}

	for (int i = 10; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			printf_s(" ");
		}
		for (int k = 10; k > i; k--)
		{
			printf_s("*");
		}
		printf_s("\n");
	}

	printf_s("\n");
	for (int i = 10; i > 0; i--)
	{
		for (int j = 10; j > i; j--)
		{
			printf_s(" ");
		}
		for (int k = 0; k < i; k++)
		{
			printf_s("*");
		}
		printf_s("\n");
	}
	*/
	for (int i = 0; i <= 10; i++)
	{
		for (int k = 10; k > i; k--)
		{
			printf_s(" ");
			
		}
		for (int j = 0; j < i; j++)
		{
			printf_s("**");			
		}
		printf_s("\n");
	}
	for (int i = 10; i >= 0; i--)
	{
		for (int k = 10; k > i; k--)
		{
			printf_s(" ");

		}
		for (int j = 0; j < i; j++)
		{
			printf_s("**");
		}
		printf_s("\n");
	}
	return 0;
}