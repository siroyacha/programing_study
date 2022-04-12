#include<stdio.h>
#include<string>
#include<malloc.h>

/*
typedef struct tagInfo
{
	int iKor;
	int iEng;
	int iMath;
}INFO;
*/

typedef struct tagInventory
{
	int iHPotion;
	int iMPotion;
}INVENTORY;

typedef struct tagInfo
{
	int iX;
	int iY;
	INVENTORY* pInventory;
}INFO;

int main()
{
	/*
	printf_s("%d\n", sizeof(INFO*));
	printf_s("%d\n", sizeof(INFO));
	*/

	INFO* pInfo = (INFO*)malloc(sizeof(INFO));
	pInfo->pInventory = (INVENTORY*)malloc(sizeof(INVENTORY));

	pInfo->iX = 10;
	pInfo->iY = 20;
	pInfo->pInventory->iHPotion = 1;
	pInfo->pInventory->iMPotion = 2;

	printf_s("iX : iY = %d : %d\n", pInfo->iX, pInfo->iY);
	printf_s("iHPotion : iMPotion = %d : %d\n", pInfo->pInventory->iHPotion, pInfo->pInventory->iMPotion);
	
	free(pInfo->pInventory);
	free(pInfo);

	return 0;
}