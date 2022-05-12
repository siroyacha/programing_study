#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>

// 포트폴리오 영상 30초 안넘기게
// 16일 학원 출발 '전'까지 영상 보내기

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
const int Scene_Town = 4;
const int Scene_Mab = 5;
const int Scene_Invetory = 6;

int SceneState = 0;

int Check = 1;


//플레이어와 몬스터 등 캐릭터들의 정보를 구성하는 구조체
typedef struct tagInfo
{
	char* Name;
	int HP;
	int MP;
	
	int EXP;

	float Att;
	float Def;
	int Int;

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

typedef struct tagSkil
{
	char* Name;
	int Tier;

	float Att;

	int Mp;
}Skil;

// ** 오브젝트 단위로 묶기 위한 구조체
typedef struct tagObject
{
	char* Name;
	INFO Info;
	Inventory Inventory;
	Skil Skill[3];
	int P_x;
	int P_y;
}OBJECT;

Item HpPotion = { (char*)"HP포션",1,1 };
Item MpPotion = { (char*)"MP포션",2,1 };
Item Gold = { (char*)"보유골드",0,100 };

Skil Tier1 = { (char*)"1티어 기술",1,7,10 };
Skil Tier2 = { (char*)"2티어 기술",2,10,15 };
Skil Tier3 = { (char*)"3티어 기술",3,12,25 };

//필요한 함수들의 전방선언
void SceneManager(OBJECT* _Player);
char* SetName();

void LogoScene();
void MenuScene();
void StageScene(OBJECT* _Player);

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
void Move(OBJECT* _Player, int* Encounter);
int EnCounter();
void BattelScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter);
void MapScene(OBJECT* _Player);
void TownScene(OBJECT* _Player);
void InventoryScene(OBJECT* _Player);
void HorizenLine();
void MonsterLevel(int Player_X, int Player_Y, OBJECT* _Enemy);

int main()
{
	// ** 커서를 안보이게 함
	HideCursor();

	// ** 콘솔창 사이즈 설정
	system("mode con:cols=120 lines=30");

	//**콘솔창 이름 설정
	system("title 전은평 Framework v0.9");

	// ** 전체 배경색을 변경함.
	//system("color 70");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

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
			SceneManager(Player);
		}
	}

	free(Player);
	return 0;
}

void SceneManager(OBJECT* _Player)
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
		StageScene(_Player);
		break;
	case Scene_Exit:
		exit(NULL);// ** 프로그램 종료
		break;
	case Scene_Town:
		TownScene(_Player);
		break;
	case Scene_Invetory:
		InventoryScene(_Player);
		break;
	case Scene_Mab:
		MapScene(_Player);
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
	SetPosition(Width, Height + 4, (char*)"/____/\\___/\\___/\\___/ ");

	Sleep(1000);
	SceneState++;
}

void MenuScene()
{
	int Width = (120 / 2) - (strlen("게임을 시작 하시겠습니까?") / 2);
	int Height = 12;
	int i = 0;
		
	SetPosition(Width, Height, (char*)"게임을 시작 하시겠습니까?\n");
	SetPosition(Width, Height+2, (char*)"1. 시작\n");
	SetPosition(Width, Height+4, (char*)"2. 종료\n");
	SetPosition(Width, Height+6, (char*)"입력 : ");
	scanf("%d", &i);


	if (i == 1)
		SceneState++;
	else if (i == 2)
		SceneState = Scene_Exit;
}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.Type = SetPlayerJob();

	switch (_Player->Info.Type)
	{
	case Warrior:
		_Player->Info.Att = 30;
		_Player->Info.Def = 20;
		_Player->Info.EXP = 0;
		_Player->Info.HP = 250;
		_Player->Info.MP = 50;
		_Player->Info.Int = 5 * _Player->Info.Type;
		_Player->Info.Level = 1;
		break;
	case Hunter:
		_Player->Info.Att = 40;
		_Player->Info.Def = 10;
		_Player->Info.EXP = 0;
		_Player->Info.HP = 250;
		_Player->Info.MP = 25;
		_Player->Info.Int = 5 * _Player->Info.Type;
		_Player->Info.Level = 1;
		break;
	case Wizard:
		_Player->Info.Att = 20;
		_Player->Info.Def = 10;
		_Player->Info.EXP = 0;
		_Player->Info.HP = 200;
		_Player->Info.MP = 100;
		_Player->Info.Int = 5 * _Player->Info.Type;
		_Player->Info.Level = 1;
		break;
	}
	_Player->P_x = 10;
	_Player->P_y = 18;
	_Player->Skill[0] = Tier1;
	_Player->Skill[1] = Tier2;
	_Player->Skill[2] = Tier3;

	_Player->Inventory.Item[0] = Gold;
	_Player->Inventory.Item[1] = HpPotion;
	_Player->Inventory.Item[2] = MpPotion;
}

void PlayerScene(OBJECT* _Player)
{
	PrintStatus(_Player);
}

void InitializeEnemy(OBJECT* _Enemy)
{
	srand(GetTickCount());
	_Enemy->Info.Type = (rand() % 3) + 1;

	switch (_Enemy->Info.Type)
	{
	case 1:
		_Enemy->Info.Att = 10;
		_Enemy->Info.Def = 15;
		_Enemy->Info.EXP = 0;
		_Enemy->Info.HP = 200;
		_Enemy->Info.MP = 0;
		_Enemy->Info.Level = 1;
		_Enemy->Name = (char*)"Enemy1";
		break;
	case 2:
		_Enemy->Info.Att = 15;
		_Enemy->Info.Def = 10;
		_Enemy->Info.EXP = 0;
		_Enemy->Info.HP = 250;
		_Enemy->Info.MP = 0;
		_Enemy->Info.Level = 1;
		_Enemy->Name = (char*)"Enemy2";
		break;
	case 3:
		_Enemy->Info.Att = 25;
		_Enemy->Info.Def = 5;
		_Enemy->Info.EXP = 0;
		_Enemy->Info.HP = 150;
		_Enemy->Info.MP = 0;
		_Enemy->Info.Level = 1;
		_Enemy->Name = (char*)"Enemy3";
		break;
	}
	_Enemy->P_y = 21;
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
	int Width = (120 / 2) - (strlen("이름 입력 : "));
	int Height = 12;

	SetPosition(Width, Height, (char*)"이름 입력 : ");
	scanf("%s", Buffer);

	//입력받은 이름을 동적할당으로 저장할 변수(null값을 포함하기 때문에 크기가 1이 더 크다)
	char* pName = (char*)malloc(strlen(Buffer) + 1);
	//문자열 복사로 이름을 저장
	strcpy(pName, Buffer);

	//이름 반환
	return pName;
}

//스테이지 신을 출력하는 함수
void StageScene(OBJECT* _Player)
{
	int Encounter = 0;
	//이동
	Move(_Player, &Encounter);
	
	// ** 전투
	if (Encounter)
	{
		OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
		InitializeEnemy(Monster);
		MonsterLevel(_Player->P_x, _Player->P_y, Monster);

		system("cls");
		PlayerScene(_Player);
		EnemyScene(Monster);
		BattelScene(_Player, Monster, &Encounter);

		free(Monster);
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

	int Width = (120 / 2) - (strlen("당신의 직업은 무엇입니까?") / 2);
	int Height = 12;

	system("cls");
	SetPosition(Width-2, Height, (char*)"당신의 직업은 무엇입니까?\n");
	SetPosition(Width-2, Height + 2, (char*)"1.전사  2.궁수  3.마법사\n");
	SetPosition(Width + 6, Height + 4, (char*)"입력 : ");
	scanf_s("%d", &type);

	return type;
}

void LevelUp(OBJECT* _Player)
{
	int LevelUpHelper = 0;
	int Width = (120 / 2) - (strlen("레벨 업!") / 2);
	int Height = 15;

	LevelUpHelper = _Player->Info.EXP / 100;

	if (_Player->P_y<20)
	{
		system("cls");
		SetPosition(Width, Height, (char*)"레벨 업!\n", 11);
		Sleep(1000);
		SetPosition(Width, Height, (char*)" ", 15);
	}

	_Player->Info.Level = _Player->Info.Level + LevelUpHelper;

	switch (_Player->Info.Type)
	{
	case Warrior:
		_Player->Info.Att = _Player->Info.Att + ((_Player->Info.Level - 1) * 15);
		_Player->Info.Def = _Player->Info.Def + ((_Player->Info.Level - 1) * 20);
		_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 150);
		_Player->Info.MP = 50 + ((_Player->Info.Level - 1) * 100);
		_Player->Info.Int = _Player->Info.Int + ((_Player->Info.Level - 1) * 2);
		break;
	case Hunter:
		_Player->Info.Att = _Player->Info.Att + ((_Player->Info.Level - 1) * 20);
		_Player->Info.Def = _Player->Info.Def + ((_Player->Info.Level - 1) * 5);
		_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 100);
		_Player->Info.MP = 25 + ((_Player->Info.Level - 1) * 50);
		_Player->Info.Int = _Player->Info.Int + ((_Player->Info.Level - 1) * 1);
		break;
	case Wizard:
		_Player->Info.Att = _Player->Info.Att + ((_Player->Info.Level - 1) * 10);
		_Player->Info.Def = _Player->Info.Def + ((_Player->Info.Level - 1) * 10);
		_Player->Info.HP = 200 + ((_Player->Info.Level - 1) * 100);
		_Player->Info.MP = 100 + ((_Player->Info.Level - 1) * 150);
		_Player->Info.Int = _Player->Info.Int + ((_Player->Info.Level - 1) * 3);
		break;
	}
	_Player->Info.EXP = _Player->Info.EXP % 100;
}

void PrintStatus(OBJECT* _Object)
{
	printf_s("%s\n", _Object->Name);
	printf_s("레벨 : %02d\n직업 : %d\n체력 : %d\n마나 : %d\n공격력 : %0.2f\n방어력 : %0.2f\n경험치 : %03d\n",
		_Object->Info.Level,_Object->Info.Type, _Object->Info.HP, _Object->Info.MP, _Object->Info.Att, _Object->Info.Def, _Object->Info.EXP);
}

void Move(OBJECT* _Player, int* Encounter)
{
	int MoveHelper = 0;
	int Width = (120 / 2) - (strlen("몬스터 조우!") / 2);
	int Height = 15;
	HorizenLine();
	
	printf_s("이동 하시겠습니까?\n\n");
	printf_s("1.상단이동 2.하단이동 3.좌측이동 4.우측이동 5.아이템 사용(확인) 6.지도열기 7.상점 0.종료 \n입력 : ");;
	scanf("%d", &MoveHelper);
	switch (MoveHelper)
	{
	case 1:
		*Encounter = EnCounter();
		_Player->P_y -= 1;
		break;
	case 2:
		*Encounter = EnCounter();
		_Player->P_y += 1;
		break;
	case 3:
		*Encounter = EnCounter();
		_Player->P_x -= 3;
		break;
	case 4:
		*Encounter = EnCounter();
		_Player->P_x += 3;
		break;
	case 5:
		SceneState = Scene_Invetory;
		break;
	case 6:
		SceneState = Scene_Mab;
		break;
	case 7:
		SceneState = Scene_Town;
		break;
	case 8:
		*Encounter = 1;
		break;
	case 0:
		exit(NULL);
		break;
	}	
	if (*Encounter) {
		system("cls");
		SetPosition(Width, Height, (char*)"몬스터 조우!\n", 4);
		Sleep(1000);
		SetPosition(Width, Height, (char*)" ", 15);
	}

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
	int MabHelper = 1;
	int P_x = 0;
	int P_y = 0;

	P_x = _Player->P_x;
	P_y = _Player->P_y;
	SetPosition(P_x, P_y, (char*)"test\n");
	HorizenLine();
	printf_s("종료를 원하면 0입력\n");
	scanf("%d", &MabHelper);

	if (MabHelper == 0)
		SceneState = Scene_Stage;
}

void TownScene(OBJECT* _Player)
{
	int TownHelper = 1;
	int Count = 0;
	Item _ShopHppotion = HpPotion;
	Item _ShopMppotion = MpPotion;
	_ShopHppotion.quantity = 20;
	_ShopMppotion.quantity = 20;
	OBJECT* Shop = (OBJECT*)malloc(sizeof(OBJECT));

	Shop->Name = (char*)"상점";
	Shop->Inventory.Item[0] = _ShopHppotion;
	Shop->Inventory.Item[1] = _ShopMppotion;

	HorizenLine();
	if (_Player->Inventory.Item[0].quantity < 100)
	{
		printf_s("금액부족!\n상점에서 나갑니다");

		SceneState = 2;
		TownHelper = 0;
	}
	while (TownHelper)
	{
		printf_s("어떤걸 구매하시겠습니까?\n1.HP포션(100골드) 2.MP포션(150골드)\n");
		scanf_s("%d", &TownHelper);

		switch (TownHelper)
		{
		case 1:
			if (Shop->Inventory.Item[0].quantity)
			{
				system("cls");
				HorizenLine();
				printf_s("몇개 구매하시겠습니까?1~%d\n", Shop->Inventory.Item[0].quantity);
				scanf_s("%d", &Count);

				if (_Player->Inventory.Item[0].quantity < (100 * Count))
				{
					printf_s("금액 부족!\n");

					break;
				}

				_Player->Inventory.Item[0].quantity = _Player->Inventory.Item[0].quantity - (100 * Count);
				_Player->Inventory.Item[1].quantity = _Player->Inventory.Item[1].quantity + Count;
				Shop->Inventory.Item[0].quantity = Shop->Inventory.Item[0].quantity - Count;

				system("cls");
				HorizenLine();
				printf_s("구매 완료!\n");
				printf_s("현재 보유 갯수 %d개\n\n", _Player->Inventory.Item[1].quantity);
				break;
			}

			printf_s("재고 부족\n");
			break;
		case 2:
			if (Shop->Inventory.Item[1].quantity)
			{
				system("cls");
				HorizenLine();
				printf_s("몇개 구매하시겠습니까?1~%d\n", Shop->Inventory.Item[1].quantity);
				scanf_s("%d", &Count);

				if (_Player->Inventory.Item[0].quantity < (150 * Count))
				{
					printf_s("금액 부족!\n");

					break;
				}
				
				_Player->Inventory.Item[0].quantity = _Player->Inventory.Item[0].quantity - (150 * Count);
				_Player->Inventory.Item[2].quantity = _Player->Inventory.Item[2].quantity + Count;
				Shop->Inventory.Item[2].quantity = Shop->Inventory.Item[2].quantity - Count;

				system("cls");
				HorizenLine();
				printf_s("구매 완료!\n");
				printf_s("현재 보유 갯수 %d개\n\n", _Player->Inventory.Item[2].quantity);
				break;
			}

			printf_s("재고 부족\n");
			break;
		}
		printf_s("계속 구매하시겠습니까?\n1.예 2.아니요\n");
		scanf_s("%d", &TownHelper);
		if (TownHelper == 2)
		{
			printf_s("마을에서 나갑니다\n");
			SceneState = 2;
			TownHelper = 0;
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
	HorizenLine();
		printf_s("도주하시겠습니까?\n1. 예 2. 아니요\n");
		scanf("%d", &runcounter);

		if (runcounter==1)
		{
			if (runchance>=30)
			{
				SetPosition(119, 29, (char*)" ", 11);
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

			HorizenLine();

			printf_s("1. 공격 2. 마법 3. 아이템 사용\n\n");
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
				break;
			case 2:
				if (_Player->Info.MP<_Player->Skill[0].Mp)
				{
					printf_s("MP 부족!!\n");
					break;
				}
				printf_s("어떤 스킬을 사용하시겠습니까?\n");

				for (int i = 0; i < 3; i++)
					printf_s("%d.%s\n", _Player->Skill[i].Tier, _Player->Skill[i].Name);

				scanf("%d", &battelhelper);

				switch (battelhelper-1)
				{
				case 0:
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[0].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[0].Mp;
					printf_s("%s 사용!\n%d의 데미지!", _Player->Skill[0].Name, (int)(_Player->Skill[0].Att * _Player->Info.Int));
					break;
				case 1:
					if (_Player->Info.MP < _Player->Skill[1].Mp)
					{
						printf_s("MP 부족!!\n");
						break;
					}
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[1].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[1].Mp;
					printf_s("%s 사용!\n%d의 데미지!", _Player->Skill[1].Name, (int)(_Player->Skill[1].Att * _Player->Info.Int));
					break;
				case 2:
					if (_Player->Info.MP < _Player->Skill[2].Mp)
					{
						printf_s("MP 부족!!\n");
						break;
					}
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[2].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[2].Mp;
					printf_s("%s 사용!\n%d의 데미지!", _Player->Skill[2].Name, (int)(_Player->Skill[2].Att * _Player->Info.Int));
					break;
				}
				if (_Player->Info.MP < 0)
					_Player->Info.MP = 0;
				Sleep(500);
				if (_Enemy->Info.Att > _Player->Info.Def)
				{
					_Player->Info.HP = _Player->Info.HP - (int)(_Enemy->Info.Att - _Player->Info.Def);
					printf_s("%s의 공격!\n%d 데미지!\n", _Enemy->Name, (int)(_Enemy->Info.Att - _Player->Info.Def));
				}
				else
				{
					_Player->Info.HP -= 1;
					printf_s("%s의 공격!\n1 데미지!\n", _Enemy->Name);
				}
				break;
			case 3:
				printf_s("어떤 아이템을 사용하시겠습니까?\n");
				for (int i = 0; i < 3; i++)
					printf_s("%d.%s(%d개)",0 , _Player->Inventory.Item[i].Name, _Player->Inventory.Item[i].quantity);
				printf_s("0.사용하지 않음");
				scanf("%d", &battelhelper);
				switch (battelhelper)
				{
				case 1:
					_Player->Info.HP += 50;
					_Player->Inventory.Item[1].quantity--;
					switch (_Player->Info.Type)
					{
					case Warrior:
						if (_Player->Info.HP > 250 + ((_Player->Info.Level - 1) * 150))
							_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 150);
						break;
					case Hunter:
						if (_Player->Info.HP > 250 + ((_Player->Info.Level - 1) * 100))
							_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 100);
						break;
					case Wizard:
						if (_Player->Info.HP > 200 + ((_Player->Info.Level - 1) * 100))
							_Player->Info.HP = 200 + ((_Player->Info.Level - 1) * 100);
						break;
					}
					printf_s("%s사용(남은 개수%d개)", _Player->Inventory.Item[1].Name, _Player->Inventory.Item[1].quantity);
					break;
				case 2:
					_Player->Info.MP += 25;
					_Player->Inventory.Item[2].quantity--;
					switch (_Player->Info.Type)
					{
					case Warrior:
						if (_Player->Info.MP > 50 + ((_Player->Info.Level - 1) * 100))
							_Player->Info.MP = 50 + ((_Player->Info.Level - 1) * 100);
						break;
					case Hunter:
						if (_Player->Info.MP > 25 + ((_Player->Info.Level - 1) * 50))
							_Player->Info.MP = 25 + ((_Player->Info.Level - 1) * 50);
						break;
					case Wizard:
						if (_Player->Info.MP > 100 + ((_Player->Info.Level - 1) * 150))
							_Player->Info.MP = 100 + ((_Player->Info.Level - 1) * 150);
						break;
					}
					printf_s("%s사용(남은 개수%d개)", _Player->Inventory.Item[2].Name, _Player->Inventory.Item[2].quantity);
					break;
				case 0:
					printf_s("아이템을 사용하지 않습니다.\n");
					break;
				}
				break;
			}

			Sleep(500);
			if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
			{
				printf_s("전투 종료");
				if (_Player->Info.HP <= 0)
				{
					printf_s("당신은 사망하셨습니다.\n마을로 돌아갑니다");
					*Encounter = 0;
				}
				else
				{
					printf_s("승리!\n");
					_Player->Info.EXP = _Player->Info.EXP + (_Enemy->Info.Level * 10);
					_Player->Inventory.Item[0].quantity = _Player->Inventory.Item[0].quantity + (_Enemy->Info.Level * 100);
					if (_Player->Info.EXP >= 100)
					{
						LevelUp(_Player);
					}
					*Encounter = 0;
				}
			}
		}
	}
}

void InventoryScene(OBJECT* _Player)
{
	int inventoryHelper = 1;
	int itemtype = 0;

	HorizenLine();

	while (inventoryHelper)
	{
		printf_s("사용할 아이템 선택\n\n");
		for (int i = 0; i < 3; i++)
		{
			printf_s("%d. %s(%d개) ", i, _Player->Inventory.Item[i].Name, _Player->Inventory.Item[i].quantity);
		}
		printf_s("0. 종료\n");
		scanf("%d", &inventoryHelper);
		if (_Player->Inventory.Item[itemtype].type==0)
		{
			_Player->Inventory.Item[itemtype].quantity++;
		}
		_Player->Inventory.Item[itemtype].quantity--;
		itemtype = _Player->Inventory.Item->type;
		switch (itemtype)
		{
		case 1:
			_Player->Info.HP += 50;
			switch (_Player->Info.Type)
			{
			case Warrior:
				if (_Player->Info.HP > 250 + ((_Player->Info.Level - 1) * 150))
					_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 150);
				break;
			case Hunter:
				if (_Player->Info.HP > 250 + ((_Player->Info.Level - 1) * 100))
					_Player->Info.HP = 250 + ((_Player->Info.Level - 1) * 100);
				break;
			case Wizard:
				if (_Player->Info.HP > 200 + ((_Player->Info.Level - 1) * 100))
					_Player->Info.HP = 200 + ((_Player->Info.Level - 1) * 100);
				break;
			}
			break;
		case 2:
			_Player->Info.MP += 25;
			switch (_Player->Info.Type)
			{
			case Warrior:
				if (_Player->Info.MP > 50 + ((_Player->Info.Level - 1) * 100))
					_Player->Info.MP = 50 + ((_Player->Info.Level - 1) * 100);
				break;
			case Hunter:
				if (_Player->Info.MP > 25 + ((_Player->Info.Level - 1) * 50))
					_Player->Info.MP = 25 + ((_Player->Info.Level - 1) * 50);
				break;
			case Wizard:
				if (_Player->Info.MP > 100 + ((_Player->Info.Level - 1) * 150))
					_Player->Info.MP = 100 + ((_Player->Info.Level - 1) * 150);
				break;
			}
			break;
		}
	}

	SceneState = Scene_Stage;
}

void HorizenLine()
{
	int Width = 0;
	int Height = 20;
	SetPosition(Width, Height, (char*)"------------------------------------------------------------------------------------------------------------------------\n");
}

void MonsterLevel(int Player_X, int Player_Y, OBJECT* _Enemy)
{
	int Levelcounter = 0;

	srand(GetTickCount());

	if (Player_X < 20 || Player_Y > 16)
	{
		for (int i = 0; i < Levelcounter; i++)
		{
			_Enemy->Info.Att -= 5;
			_Enemy->Info.Def -= 5;
			_Enemy->Info.HP -= 25;
			_Enemy->Info.MP -= 50;
		}
	}
	else if (Player_X < 30 || Player_Y > 15)
	{
		Levelcounter = (rand() % 3) + 1;
		_Enemy->Info.EXP = Levelcounter * 100;
		LevelUp(_Enemy);
		for (int i = 0; i < Levelcounter; i++)
		{
			_Enemy->Info.Att -= 5;
			_Enemy->Info.Def -= 5;
			_Enemy->Info.HP -= 25;
			_Enemy->Info.MP -= 50;
		}
	}

	else if (Player_X < 60 || Player_Y > 6)
	{
		Levelcounter = (rand() % 3) + 4;
		_Enemy->Info.EXP = Levelcounter * 100;
		LevelUp(_Enemy);
		for (int i = 0; i < Levelcounter; i++)
		{
			_Enemy->Info.Att -= 5;
			_Enemy->Info.Def -= 5;
			_Enemy->Info.HP -= 25;
			_Enemy->Info.MP -= 50;
		}
	}

	else if (Player_X < 120 && Player_Y > 0)
	{
		Levelcounter = (rand() % 3) + 7;
		_Enemy->Info.EXP = Levelcounter * 100;
		LevelUp(_Enemy);
		for (int i = 0; i < Levelcounter; i++)
		{
			_Enemy->Info.Att -= 5;
			_Enemy->Info.Def -= 5;
			_Enemy->Info.HP -= 25;
			_Enemy->Info.MP -= 50;
		}
	}
}