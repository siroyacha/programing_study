#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


//플레이어와 몬스터를 구분 하는 용도의 변수 선언
const int PLAYER = 0;
const int ENEMY	 = 1;
const int Max	 = 2;

//플레이어와 몬스터 등 캐릭터들의 정보를 구성하는 구조체
typedef struct tagInfo
{
	// ** 스탯 타입은 재량(int, float 상관 없음)
	char* Name;
	int HP;
	int MP;
	
	int EXP;

	float Att;
	float Def;
	
	int Level;

}INFO;

typedef struct tagObject
{
	INFO Info;

}OBJECT;

//필요한 함수들의 전방선언
void InitializeObject(OBJECT* _Obj, int ObjectType);
char* SetName();
void StageScene(OBJECT* Player, OBJECT* Enemy);

int main()
{
	//플레이어와 몬스터의 정보 구조체를 선언
	OBJECT Player;
	OBJECT Enemy;

	//구조체 배열의 선언
	OBJECT* Objects[Max];

	//플레이어와 몬스터를 동적 할당
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[PLAYER], PLAYER);

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeObject(Objects[ENEMY], ENEMY);
	
	//스테이지 신 출력(씬 매니저가 없어 임시적으로 직접 출력)
	StageScene(Objects[PLAYER], Objects[ENEMY]);


	return 0;
}

//캐릭터들의 정보를 초기화하는 함수
void InitializeObject(OBJECT* _Obj, int ObjectType)
{
	//스위치문을 통해 캐릭터 타입별로 다른 정보로 초기화
	switch (ObjectType)
	{
		//플레이어로 정보 초기화
	case PLAYER:
		_Obj->Info.Name = SetName();

		_Obj->Info.Att = 10;
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
		//몬스터로 정보 초기화
	case ENEMY:
		_Obj->Info.Name = (char*)"Enemy";

		_Obj->Info.Att = 5;
		_Obj->Info.Def = 15;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 30;
		_Obj->Info.MP = 5;
		_Obj->Info.Level = 7;
		break;
	}
}

//이름을 입력받는 함수
char* SetName()
{
	//이름을 입력받을 변수
	char Buffer[128] = "";

	printf_s("이름 입력 : ");
	scanf("%s", Buffer);

	//입력받은 이름을 동적할당으로 저장할 변수(null값을 포함하기 때문에 크기가 1이 더 크다)
	char* pName = (char*)malloc(strlen(Buffer) + 1);
	//문자열 복사로 이름을 저장
	strcpy(pName, Buffer);

	//이름 반환
	return pName;
}

//스테이지 신을 출력하는 함수
void StageScene(OBJECT* Player, OBJECT* Enemy)
{
	//루프문 체크를 할 변수
	int LoopCheck = 1;

	//상태창 출력을 하는 반복문
	while (LoopCheck)
	{
		// ** 콘솔창을 모두 지움.
		system("cls");

		printf_s("\n[%s]\n", Player->Info.Name);
		printf_s("HP : %d\n", Player->Info.HP);
		printf_s("MP : %d\n", Player->Info.MP);
		printf_s("공격력 : %.2f\n", Player->Info.Att);
		printf_s("방어력 : %.2f\n", Player->Info.Def);
		printf_s("EXP : %d\n", Player->Info.EXP);
		printf_s("Level : %d\n\n", Player->Info.Level);

		printf_s("[%s]\n", Enemy->Info.Name);
		printf_s("HP : %d\n", Enemy->Info.HP);
		printf_s("MP : %d\n", Enemy->Info.MP);
		printf_s("공격력 : %.2f\n", Enemy->Info.Att);
		printf_s("방어력 : %.2f\n", Enemy->Info.Def);
		printf_s("EXP : %d\n", Enemy->Info.EXP);
		printf_s("Level : %d\n\n", Enemy->Info.Level);

		//출력을 지연시키는 함수
		Sleep(500);

		//공격과 도망을 선택하는 선택지를 받을 변수
		int iChoice = 0;

		//도망 체크를 위한 값을 입력받을 변수
		int run = 0;

		printf_s("몬스터와 만났습니다. 공격하시겠습니까 ?\n1. 공격\n2. 도망\n입력 : ");
		scanf_s("%d", &iChoice);

		//플레이어의 선택으로 공격과 도망을 수행하는 스위치문
		switch (iChoice)
		{
			//공격 행동을 실행하는 부분
		case 1:
			//플레이어의 공격을 실행하는 부분
			printf("[%s]의 공격\n", Player->Info.Name);
			//플레이어의 공격력이 몬스터의 방어력보다 높은경우
			if (Player->Info.Att > Enemy->Info.Def)
			{
				Enemy->Info.HP -= Player->Info.Att - Enemy->Info.Def;
			}
			//플레이어의 공격력이 몬스터의 방어력보다 낮은 경우
			else
				Enemy->Info.HP -= 1;

			//몬스터의 공격을 실행하는 부분
			printf("[%s]의 공격\n", Enemy->Info.Name);
			//몬스터의 공격력이 플레이어의 방어력보다 높은 경우
			if (Enemy->Info.Att > Player->Info.Def)
			{
				Player->Info.HP -= Enemy->Info.Att - Player->Info.Def;
			}
			//몬스터의 공격력이 플레이어의 방어력보다 낮은 경우
			else			
				Player->Info.HP -= 1;

			//공격 종료
			break;

			//도망 행동을 실행하는 부분
		case 2:
			//랜덤 시드 초기화
			srand(time(NULL));
			//랜덤함수를 통한 확률 결정
			run = rand() % 100;

			//몬스터의 레벨이 플레이어보다 높을 경우 플레이어에게 패널티를 주어 도망 확률을 낮추는 과정
			if (Enemy->Info.Level > Player->Info.Level)
			{
				//패널티를 감안하여 도주 확률을 결정하고 성공한 경우
				if (run - (Enemy->Info.Level - Player->Info.Level) * 5 > 30)
				{
					printf_s("도망치는것에 [성공] 했습니다.\n");
					//도망치는데 성공하여 씬이 끝나는 부분
					LoopCheck = 0;
					break;
				}
				//도망에 실패했을 경우
				else
				{
					printf_s("도망치는것에 [실패] 했습니다.\n");
					//다음 씬 출력전 지연을 주는 부분
					Sleep(500);
				}
			}

			//플레이어의 레벨이 몬스터보다 높은 경우
			else
				//70프로의 확률로 도망에 성공
				if (run > 30)
				{
					printf_s("도망치는것에 [성공] 했습니다.\n");
					//도망치는데 성공하여 씬이 끝나는 부분
					LoopCheck = 0;
					break;
				}
			//도망에 실패했을 경우
				else
				{
					printf_s("도망치는것에 [실패] 했습니다.\n");
					//다음 씬 출력전 지연을 주는 부분
					Sleep(500);
				}
			//도망 부분이 끝나고 돌아가는 부분
			break;
		}
	}
}
