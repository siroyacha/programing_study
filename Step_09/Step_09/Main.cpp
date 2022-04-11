#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>

typedef struct tagInfo
{
	char Name[7];
	int Number;

	int iKor;
	int iEng;
	int IMath;
}INFO;

int main()
{
	/*
	tagInfo StudentA;
	tagInfo StudentB;

	printf_s("StudentA : \n");
	printf_s("국어 점수 : ");
	scanf_s("%d", &StudentA.iKor);
	printf_s("영어 점수 : ");
	scanf_s("%d", &StudentA.iEng);
	printf_s("수학 점수 : ");
	scanf_s("%d", &StudentA.IMath);
	printf_s("국 : %d, 영 : %d, 수 : %d\n", StudentA.iKor, StudentA.iEng, StudentA.IMath);


	printf_s("StudentB : \n");
	printf_s("국어 점수 : ");
	scanf_s("%d", &StudentB.iKor);
	printf_s("영어 점수 : ");
	scanf_s("%d", &StudentB.iEng);
	printf_s("수학 점수 : ");
	scanf_s("%d", &StudentB.IMath);
	printf_s("국 : %d, 영 : %d, 수 : %d\n", StudentB.iKor, StudentB.iEng, StudentB.IMath);
	*/
	
	/*
	INFO info;

	strcpy(info.Name, "홍길동");

	info.iKor = 10;
	info.iEng = 20;
	info.IMath = 30;

	printf_s("%s : \n", info.Name);
	printf_s("%d, %d, %d", info.iKor, info.iEng, info.IMath);
	*/

	/*
	INFO info;
	int iIndex = 0;

	printf_s("당신의 직업은 무엇입니까??\n");
	printf_s("**************************\n");
	printf_s("*     1. 도       적     *\n");
	printf_s("*     2. 마   법  사     *\n");
	printf_s("*     3. 전       사     *\n");
	printf_s("**************************\n");
	scanf_s("%d",&iIndex);


	switch (iIndex)
	{
	case 1:
		break;
	case 2:
		strcpy(info.Name, "마법사");
		break;
	case 3:
		strcpy(info.Name, "전사");
		break;
	default:
		printf_s("잘못된 입력입니다.\n");
	}

	printf_s("%s\n", info.Name);
	*/

	INFO info[3];
	char name[7];
	printf_s("학생의 점수를 입력하세요.\n");

	/*
	for (int i = 0; i < 3; i++)
	{
		printf_s("이름 입력 : \n");
		scanf_s("%s", name);
		strcpy(info[i].Name, name);
	}
	*/
	
	strcpy(info[0].Name, "홍길동");
	strcpy(info[1].Name, "김철수");
	strcpy(info[2].Name, "이영희");
	/*
	*/

	for (int i = 0; i < 3; i++)
	{
		printf_s("국어 영어 수학: \n");
		scanf_s(" %d %d %d", &info[i].iKor, &info[i].iEng, &info[i].IMath);
	}

	for (int i = 0; i < 3; i++)
	{
		printf_s("%s : %d, %d, %d", info[i].Name, info[i].iKor, info[i].iEng, info[i].IMath);
	}

	return 0;
}