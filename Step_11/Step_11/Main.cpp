#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>
#include<time.h>


int main(void)
{
	/*
	char cAlphabet;
	char cHanguel;

	cAlphabet = 'A';
	cHanguel = '한';

	printf_s("Alphabet : %c / Hanguel : %c\n", cAlphabet, cHanguel);

	char cHarray[] = "한";
	printf_s("%s\n\n", cHarray);
	*/

	/*
	char* cpArray = (char*)"Character Poiner Array";

	printf_s("&cpArray    : %d\n", &cpArray);
	printf_s("cpArray     : %d\n", cpArray);
	printf_s("&cpArray[0] : %d\n", &cpArray[0]);
	printf_s("cpArray     : %s\n\n", cpArray);

	printf_s("*cpArray    : %c\n", *cpArray);
	printf_s("cpArray[0]  : %c\n", cpArray[0]);
	printf_s("cpArray[1]  : %c\n\n", cpArray[1]);

	printf_s("*cpArray++  : %c\n", *cpArray++);
	printf_s("cpArray     : %s\n", cpArray);
	printf_s("*cpArray--  : %c\n", *cpArray--);
	printf_s("cpArray     : %s\n\n", cpArray);

	printf_s("cpArray     : %d\n", cpArray);
	printf_s("*cpArray    : %c\n", *cpArray);
	cpArray++;
	printf_s("cpArray     : %d\n", cpArray);
	printf_s("cpArray[0]  : %c\n\n", cpArray[0]);
	*/
	
	/*
	srand(time(NULL));

	int i = rand() % 45 + 1;

	printf_s("%d\n", i);
	*/
	
	int Lottery[7] = {};

	srand(time(NULL));

	for (int i = 0; i < 7; i++)
	{
		Lottery[i] = rand() % 45 + 1;
	}

	printf_s("당첨 번호는 ");
	for (int i = 0; i < 6; i++)
	{
		printf_s("%d ", Lottery[i]);
	}
	printf_s("+ %d 입니다.\n", Lottery[6]);

	time_t tTime = time(NULL);
	int i = 0;

	while (true)
	{
		if (tTime<time(NULL))
		{
			tTime = time(NULL);
			srand(tTime);
			Lottery[i] = rand() % 45 + 1;
			printf_s("%d ", Lottery[i]);
			i++;
			if (i>=6)
			{
				break;
			}
		}
	}
	return 0;
}