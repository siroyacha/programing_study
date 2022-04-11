#include <stdio.h>

int main()
{
	/*
	int iNumber1 = 10;
	int iNumber2 = 100;

	printf_s("iNumber1 : %d\n", iNumber1);
	printf_s("iNumber2 : %d\n", iNumber2);

	printf_s("iNumber1 林家蔼: %d\n", &iNumber1);
	printf_s("iNumber2 林家蔼: %d\n", &iNumber2);
	*/
	
	/*
	int iNumber1 = 10;
	int iNumber2 = 100;

	int* pPointer = &iNumber2;

	printf_s("pPointer狼 蔼 : %d\n", *pPointer);
	*/

	/*
	int iNumber = 19;
	int* piNumber;
	piNumber = &iNumber;

	printf_s("iNumber   : %d\n", iNumber);
	printf_s("*piNumber : %d\n", *piNumber);
	printf_s("piNumber  : %d\n", piNumber);
	printf_s("&iNumber  : %d\n", &iNumber);
	printf_s("&piNumber : %d\n\n", &piNumber);
	*/

	printf_s("char   : %d\n", sizeof(char));
	printf_s("short  : %d\n", sizeof(short));
	printf_s("long   : %d\n", sizeof(long));
	printf_s("int    : %d\n", sizeof(int));
	printf_s("float  : %d\n", sizeof(float));
	printf_s("double : %d\n\n", sizeof(double));

	printf_s("char*   : %d\n", sizeof(char*));
	printf_s("short*  : %d\n", sizeof(short*));
	printf_s("long*   : %d\n", sizeof(long*));
	printf_s("int*    : %d\n", sizeof(int*));
	printf_s("float*  : %d\n", sizeof(float*));
	printf_s("double* : %d\n\n", sizeof(double*));
	
	return 0;		 
}