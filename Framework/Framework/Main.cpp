#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>

// 포트폴리오 영상 30초 안넘기게

// ** 참고 : https://www.youtube.com/watch?v=_nuS86ITjIM
// ** 아스키 아트 : http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20

// ** 검정	 0
// ** 어두운 파랑	 1
// ** 어두운 초록	 2
// ** 어두운 하늘	 3
// ** 어두운 빨강	 4
// ** 어두운 보라	 5
// ** 어두운 노랑	 6
// ** 회색	 7
// ** 어두운 회색	 8
// ** 파랑	 9
// ** 초록	 10
// ** 하늘	 11
// ** 빨강	 12
// ** 보라	 13
// ** 노랑	 14
// ** 하양	 15

const int Warrior = 1;
const int Hunter = 2;
const int Wizard = 3;

const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;
const int Scene_Battel = 4;
const int Scene_Town = 5;
const int Scene_Mab = 6;

int SceneState = 0;

int Check = 1;


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
	int Type;
}INFO;

typedef struct tagItem
{
	char* Name;
	int type;
	int quantity;
}Item;

typedef struct tagInventory
{
	Item Item[10];
}Inventory;

// ** 오브젝트 단위로 묶기 위한 구조체
typedef struct tagObject
{
	char* Name;
	INFO Info;
	Inventory Inventory;
}OBJECT;

Item HpPotion = { (char*)"HP포션",1,1 };
Item MpPotion = { (char*)"MP포션",2,1 };
//필요한 함수들의 전방선언

void SceneManager(OBJECT* _Player, OBJECT* _Enemy);
char* SetName();

void LogoScene();
void MenuScene();
void StageScene(OBJECT* _Player, OBJECT* _Enemy);

void InitializePlayer(OBJECT* _Player);
void PlayerScene(OBJECT* _Player);

void InitializeEnemy(OBJECT* _Enemy);
void EnemyScene(OBJECT* _Enemy);

void SetPosition(int _x, int _y, char* _str, int _Color=15);
void SetColor(int _Color);
void HideCursor();

int SetPlayerJob();
void LevelUp(OBJECT* _Player);
void PrintStatus(OBJECT* _Object);
void Move(int* Encounter);
int EnCounter();
void BattelScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter);

int main()
{

	// ** 커서를 안보이게 함
	HideCursor();

	// ** 콘솔창 사이즈 설정
	system("mode con:cols=120 lines=30");

	//**콘솔창 이름 설정
	system("title 전은평 Framework v0.7");

	// ** 전체 배경색을 변경함.
	//system("color 70");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);

	DWORD dwTime = GetTickCount(); // 1/1000 (1000분의 1초)
	int Delay = 1000;

	int UpCount = 0;

	while (true)
	{
		if (dwTime + Delay < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

			printf_s("%s\n", Player->Name);

			// ** 게임 루프
			SceneManager(Player, Monster);
		}
	}

	return 0;
}

void SceneManager(OBJECT* _Player, OBJECT* _Enemy)
{
	switch (SceneState)
	{
	case Scene_Logo:
		LogoScene();
		break;
	case Scene_Menu:
		MenuScene();
		break;
	case Scene_Stage:
		StageScene(_Player, _Enemy);
		break;
	case Scene_Exit:
		exit(NULL);// ** 프로그램 종료
		break;
	case Scene_Battel:
	//	BattelScene(_Player, _Enemy);
		break;
	case Scene_Town:
		TownScene(_Player);
		break;
	}
}

void LogoScene()
{
	int Width = (120 / 2) - (strlen("   __        _____    ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"   __         _____    ");
	SetPosition(Width, Height + 2, (char*)"  / /  ___   / ___/__  ");
	SetPosition(Width, Height + 3, (char*)" / /__/ _ \\/ (_ / _ \\ ");
	SetPosition(Width, Height + 4, (char*)"/____/\___/\\___/\\___/ ");

	Sleep(5000);
	SceneState++;
}

void MenuScene()
{
	printf_s("MenuScene\n");

	printf_s("게임을 시작 하시겠습니까?\n1. 시작\n2. 종료\n입력 : ");

	int i = 0;
	scanf("%d", &i);


	if (i == 1)
		SceneState++;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.Att = 20;
	_Player->Info.Def = 10;
	_Player->Info.EXP = 0;
	_Player->Info.HP = 100;
	_Player->Info.MP = 10;
	_Player->Info.Level = 1;
	_Player->Info.Type = SetPlayerJob();
}

void PlayerScene(OBJECT* _Player)
{
	PrintStatus(_Player);

	if (_Player->Info.EXP >= 100)
	{
		LevelUp(_Player);
		_Player->Info.EXP = 0;
	}
}

void InitializeEnemy(OBJECT* _Enemy)
{
	_Enemy->Name = (char*)"Enemy";

	_Enemy->Info.Att = 5;
	_Enemy->Info.Def = 10;
	_Enemy->Info.EXP = 0;
	_Enemy->Info.HP = 30;
	_Enemy->Info.MP = 5;
	_Enemy->Info.Level = 1;
	_Enemy->Info.Type = 0;
}

void EnemyScene(OBJECT* _Enemy)
{
	PrintStatus(_Enemy);
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
void StageScene(OBJECT* _Player, OBJECT* _Enemy)
{
	int Encounter = 0;
	//이동
	Move(&Encounter);
	
	// ** 전투
	if (Encounter)
	{
		system("cls");
		PlayerScene(_Player);
		EnemyScene(_Enemy);
		BattelScene(_Player, _Enemy, &Encounter);
	}
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x,_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int SetPlayerJob()
{
	int type = 0;
	system("cls");
	printf_s("당신의 직업은 무엇입니까?\n");
	printf_s("1.전사\t 2.궁수\t 3.마법사\n입력 : ");
	
	scanf_s("%d", &type);

	return type;
}

void LevelUp(OBJECT* _Player)
{
	_Player->Info.Level++;
	switch (_Player->Info.Type)
	{
	case Warrior:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	case Hunter:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	case Wizard:
		_Player->Info.Att += 10;
		_Player->Info.Def += 5;
		_Player->Info.HP += 100;
		_Player->Info.MP += 50;
		break;
	}
}

void PrintStatus(OBJECT* _Object)
{
	printf_s("%s\n", _Object->Name);
	printf_s("레벨 : %02d\n직업 : %d\n체력 : %d\n마나 : %d\n공격력 : %0.2f\n방어력 : %0.2f\n경험치 : %03d\n",
		_Object->Info.Level,_Object->Info.Type, _Object->Info.HP, _Object->Info.MP, _Object->Info.Att, _Object->Info.Def, _Object->Info.EXP);
}

void Move(int* Encounter)
{
	int MoveHelper = 0;
	printf_s("이동 하시겠습니까?\n1.이동 0.종료\n입력 : ");
	scanf("%d", &MoveHelper);
	switch (MoveHelper)
	{
	case 1:
		*Encounter = EnCounter();
		break;
	case 0:
		exit(NULL);
		break;
	}
	if (*Encounter)
		printf_s("몬스터 조우!\n");
	else
		printf_s("이동 성공\n");

	DWORD SetMoveTime = 0;
	if (SetMoveTime + 3000 < GetTickCount())
		Check = 1;

	if (Check)
	{
		SetMoveTime = GetTickCount();

		Check = 0;
	}
}

int EnCounter()
{
	int _Encounter = 0;
	srand(GetTickCount());

	_Encounter = (rand() % 100) + 1;

	if (_Encounter <= 80)
		return 0;
	if (_Encounter <= 5)
		return 2;
	else
		return 1;
}

void MapScene(OBJECT* _Player)
{
	int P_x = 0;
	int P_y = 0;
	/*
	SetPosition()
	*/
}

void TownScene(OBJECT* _Player)
{
	int TownHelper = 0;
	int Count = 0;
	Item _ShopHppotion = HpPotion;
	Item _ShopMppotion = MpPotion;
	_ShopHppotion.quantity = 20;
	OBJECT* Shop = (OBJECT*)malloc(sizeof(OBJECT));

	Shop->Name = (char*)"상점";
	Shop->Inventory.Item[1] = _ShopHppotion;
	Shop->Inventory.Item[2] = _ShopMppotion;
	while (SceneState==4)
	{
		system("cls");
		printf_s("어떤걸 구매하시겠습니까?\n1.HP포션 2.MP포션\n");
		scanf_s("%d", &TownHelper);

		switch (TownHelper)
		{
		case 1:
			if (Shop->Inventory.Item[1].quantity)
			{
				printf_s("몇개 구매하시겠습니까?1~%d\n", Shop->Inventory.Item[1].quantity);
				scanf_s("%d", &Count);
				_Player->Inventory.Item[1].quantity += Count;
				Shop->Inventory.Item[1].quantity -= Count;
				printf_s("구매 완료!\n");
				printf_s("현재 보유 갯수 %d개", _Player->Inventory.Item[1].quantity);
				break;
			}

			printf_s("재고 부족\n");
			break;
		case 2:
			if (Shop->Inventory.Item[2].quantity)
			{
				printf_s("몇개 구매하시겠습니까?1~%d\n", Shop->Inventory.Item[2].quantity);
				scanf_s("%d", &Count);
				_Player->Inventory.Item[2].quantity += Count;
				Shop->Inventory.Item[1].quantity -= Count;
				printf_s("현재 보유 갯수 %d개", _Player->Inventory.Item[2].quantity);
				break;
			}

			printf_s("재고 부족\n");
			break;
		}
		printf_s("계속 구매하시겠습니까?\n1.예 2.아니요");
		scanf_s("%d", &TownHelper);
		if (TownHelper == 2)
		{
			printf_s("마을에서 나갑니다\n");
			SceneState = 2;
		}
	}

	free(Shop);
}

void BattelScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter)
{
	int runcounter = 0;
	int runchance = 0;
	int battelhelper = 0;

	srand(GetTickCount());

	runchance = (rand() - (_Enemy->Info.Level - _Player->Info.Level) * 2) % 100;
	
	if (*Encounter == 1)
	{
		printf_s("도주하시겠습니까?\n1. 예 2. 아니요\n");
		scanf("%d", &runcounter);

		if (runcounter==1)
		{
			if (runchance>=30)
			{
				printf_s("도주 성공!\n");
				*Encounter = 0;				
			}
			else
				printf("도주 실패\n전투에 진입합니다\n");				
		}
		Sleep(500);

		while (*Encounter)
		{
			system("cls");

			PlayerScene(_Player);
			EnemyScene(_Enemy);

			printf_s("1. 공격 2. 마법 3. 아이템 사용\n");
			scanf("%d", &battelhelper);

			switch (battelhelper)
			{
			case 1:
				if (_Player->Info.Att>_Enemy->Info.Def)
				{
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Info.Att - _Enemy->Info.Def);
					printf_s("플레이어의 공격!\n%d 데미지!\n", (int)(_Player->Info.Att - _Enemy->Info.Def));
				}
				else
				{
					_Enemy->Info.HP -= 1;
					printf_s("플레이어의 공격!\n1 데미지!\n");
				}
				Sleep(500);
				if (_Enemy->Info.Att>_Player->Info.Def)
				{
					_Player->Info.HP = _Player->Info.HP - (int)(_Enemy->Info.Att - _Player->Info.Def);
					printf_s("%s의 공격!\n%d 데미지!\n", _Enemy->Name, (int)(_Enemy->Info.Att - _Player->Info.Def));
				}
				else
				{
					_Player->Info.HP -= 1;
					printf_s("%s의 공격!\n1 데미지!\n", _Enemy->Name);
				}
				Sleep(500);
				if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
				{
					printf_s("전투 종료");
					if (_Player->Info.HP<=0)
					{
						printf_s("당신은 사망하셨습니다.\n마을로 돌아갑니다");
						*Encounter = 0;
					}
					else
					{
						printf_s("승리!\n");
						_Player->Info.EXP = _Player->Info.EXP + (_Enemy->Info.Level * 50);
						*Encounter = 0;
					}
				}
				break;
			}
		}
	}
}
