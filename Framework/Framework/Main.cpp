#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>

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

const int Town_X = 30;
const int Town_y = 15;
const int Town_X2 = 60;
const int Town_y2 = 12;
const int Town_X3 = 105;
const int Town_y3 = 6;

const int UI_Y = 11;

int SceneState = 0;

int Check = 1;

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

typedef struct tagObject
{
	char* Name;
	INFO Info;
	Inventory Inventory;
	Skil Skill[3];
	int P_x;
	int P_y;
}OBJECT;

Item HpPotion = { (char*)"HP����",1,1 };
Item MpPotion = { (char*)"MP����",2,1 };
Item Gold = { (char*)"�������",0,100 };

Skil Tier1 = { (char*)"1Ƽ�� ���",1,7,10 };
Skil Tier2 = { (char*)"2Ƽ�� ���",2,10,15 };
Skil Tier3 = { (char*)"3Ƽ�� ���",3,12,25 };

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
void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter);
void MapScene(OBJECT* _Player);
void TownScene(OBJECT* _Player);
void InventoryScene(OBJECT* _Player);
void HorizenLine();
void MonsterLevel(int Player_X, int Player_Y, OBJECT* _Enemy);

int main()
{
	HideCursor();

	system("mode con:cols=120 lines=30");

	system("title ������ Framework v1.0");

	// ** ��ü ������ ������.
	//system("color 70");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	DWORD dwTime = GetTickCount(); // 1/1000 (1000���� 1��)
	int Delay = 1000;

	int UpCount = 0;

	while (true)
	{
		if (dwTime + Delay < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

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
		exit(NULL);// ** ���α׷� ����
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
	SetPosition(Width, Height + 2, (char*)"  / /  ___   / ___/ __ ");
	SetPosition(Width, Height + 3, (char*)" / /__/ _ A / (_ / /_ A ");
	SetPosition(Width, Height + 4, (char*)"/____/ A___/A___/ A___/ ");

	Sleep(1000);
	SceneState++;
}

void MenuScene()
{
	int Width = (120 / 2) - (strlen("������ ���� �Ͻðڽ��ϱ�?") / 2);
	int Height = 12;
	int i = 0;
		
	SetPosition(Width, Height, (char*)"������ ���� �Ͻðڽ��ϱ�?\n");
	SetPosition(Width, Height+2, (char*)"1. ����\n");
	SetPosition(Width, Height+4, (char*)"2. ����\n");
	SetPosition(Width, Height+6, (char*)"�Է� : ");
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
	_Player->P_x = 3;
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

//�̸��� �Է¹޴� �Լ�
char* SetName()
{
	//�̸��� �Է¹��� ����
	char Buffer[128] = "";
	int Width = (120 / 2) - (strlen("�̸� �Է� : "));
	int Height = 12;

	SetPosition(Width, Height, (char*)"�̸� �Է� : ");
	scanf("%s", Buffer);

	//�Է¹��� �̸��� �����Ҵ����� ������ ����(null���� �����ϱ� ������ ũ�Ⱑ 1�� �� ũ��)
	char* pName = (char*)malloc(strlen(Buffer) + 1);
	//���ڿ� ����� �̸��� ����
	strcpy(pName, Buffer);

	//�̸� ��ȯ
	return pName;
}

//�������� ���� ����ϴ� �Լ�
void StageScene(OBJECT* _Player)
{
	int Encounter = 0;
	//�̵�
	Move(_Player, &Encounter);
	
	// ** ����
	if (Encounter)
	{
		OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
		InitializeEnemy(Monster);
		MonsterLevel(_Player->P_x, _Player->P_y, Monster);

		system("cls");
		PlayerScene(_Player);
		EnemyScene(Monster);
		BattleScene(_Player, Monster, &Encounter);

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

	int Width = (120 / 2) - (strlen("����� ������ �����Դϱ�?") / 2);
	int Height = 12;

	system("cls");
	SetPosition(Width-2, Height, (char*)"����� ������ �����Դϱ�?\n");
	SetPosition(Width-2, Height + 2, (char*)"1.����  2.�ü�  3.������\n");
	SetPosition(Width + 6, Height + 4, (char*)"�Է� : ");
	scanf_s("%d", &type);

	return type;
}

void LevelUp(OBJECT* _Player)
{
	int LevelUpHelper = 0;
	int UI_X = (120 / 2) - (strlen(" ___      _______  __   __  _______  ___        __   __  _______  __   __ ") / 2);

	LevelUpHelper = _Player->Info.EXP / 100;

	if (_Player->P_y<20)
	{
		system("cls");
		SetPosition(UI_X, UI_Y, (char*)" ___      _______  __   __  _______  ___        __   __  _______  __   __ ", 11);
		SetPosition(UI_X, UI_Y + 1, (char*)"|   |    |       ||  | |  ||       ||   |      |  | |  ||       ||  | |  |", 11);
		SetPosition(UI_X, UI_Y + 2, (char*)"|   |    |    ___||  |_|  ||    ___||   |      |  | |  ||    _  ||  | |  |", 11);
		SetPosition(UI_X, UI_Y + 3, (char*)"|   |    |   |___ |       ||   |___ |   |      |  |_|  ||   |_| ||  | |  |", 11);
		SetPosition(UI_X, UI_Y + 4, (char*)"|   |___ |    ___||       ||    ___||   |___   |       ||    ___||__| |__|", 11);
		SetPosition(UI_X, UI_Y + 5, (char*)"|       ||   |___  |     | |   |___ |       |  |       ||   |     __   __ ", 11);
		SetPosition(UI_X, UI_Y + 6, (char*)"|_______||_______|  |___|  |_______||_______|  |_______||___|    |__| |__|", 11);
		Sleep(1000);	  
		SetPosition(UI_X, UI_Y , (char*)" ", 15);
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
	printf_s("%s\n���� : %02d\n", _Object->Name, _Object->Info.Level);
	switch (_Object->Info.Type)
	{
	case Warrior:
		printf_s("���� : ����\n");
		break;
	case Hunter:
		printf_s("���� : �ü�\n");
		break;
	case Wizard:
		printf_s("���� : ������\n");
		break;
	}
	printf_s("ü�� : %d\n���� : %d\n���ݷ� : %0.2f\n���� : %0.2f\n����ġ : %03d\n",
		_Object->Info.HP, _Object->Info.MP, _Object->Info.Att, _Object->Info.Def, _Object->Info.EXP);
}

void Move(OBJECT* _Player, int* Encounter)
{
	int MoveHelper = 0;
	int Width = (120 / 2) - (strlen(" _______  _______  _______  _______  ___      _______  __   __ ") / 2);
	int Width2 = (120 / 2) - (strlen("�̵� �Ͻðڽ��ϱ�?") / 2);
	int Height = 21;
	int Width3 = (120 / 2) - (strlen("1.����̵� 2.�ϴ��̵� 3.�����̵� 4.�����̵� 5.������ ���(Ȯ��) 6.�������� 0.����") / 2);
	HorizenLine();
	
	SetPosition(Width2, Height,(char*)"�̵� �Ͻðڽ��ϱ�?");
	if (_Player->P_x == Town_X && _Player->P_y == Town_y)
	{
		SetPosition(Width3, Height + 2, (char*)"1.����̵� 2.�ϴ��̵� 3.�����̵� 4.�����̵� 5.������ ���(Ȯ��) 6.�������� 7.���� �̵� 0.����");;
	}
	
	else
		SetPosition(Width3, Height + 2, (char*)"1.����̵� 2.�ϴ��̵� 3.�����̵� 4.�����̵� 5.������ ���(Ȯ��) 6.�������� 0.����");
	
	SetPosition(Width2 + 2, Height + 4, (char*)" ");

	printf_s("�Է� : ");
	scanf("%d", &MoveHelper);

	switch (MoveHelper)
	{
	case 1:
		*Encounter = EnCounter();
		_Player->P_y -= 1;
		break;
	case 2:
		if (_Player->P_y<=20)
		{
			*Encounter = EnCounter();
			_Player->P_y = 19;
			break;
		}
		*Encounter = EnCounter();
		_Player->P_y += 1;
		break;
	case 3:
		*Encounter = EnCounter();
		_Player->P_x -= 3;
		break;
	case 4:
		if (_Player->P_x >= 120)
		{
			*Encounter = EnCounter();
			_Player->P_x = 119;
			break;
		}
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
	//�׽�Ʈ��
	case 8:
		*Encounter = 1;
		break;
	case 0:
		SceneState = Scene_Menu;
		break;
	}	

	if (*Encounter) {
		system("cls");
		SetPosition(Width, UI_Y, (char*)" _______  _______  _______  _______  ___      _______  __   __ ", 12);
		SetPosition(Width, UI_Y + 1, (char*)"|  _    ||   _   ||       ||       ||   |    |       ||  | |  |", 12);
		SetPosition(Width, UI_Y + 2, (char*)"| |_|   ||  |_|  ||_     _||_     _||   |    |    ___||  | |  |", 12);
		SetPosition(Width, UI_Y + 3, (char*)"|       ||       |  |   |    |   |  |   |    |   |___ |  | |  |", 12);
		SetPosition(Width, UI_Y + 4, (char*)"|  _   | |       |  |   |    |   |  |   |___ |    ___||__| |__|", 12);
		SetPosition(Width, UI_Y + 5, (char*)"| |_|   ||   _   |  |   |    |   |  |       ||   |___  __   __ ", 12);
		SetPosition(Width, UI_Y + 6, (char*)"|_______||__| |__|  |___|    |___|  |_______||_______||__| |__|", 12);
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

	if (_Encounter <= 65)
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
	int Map_X = 90;
	int Map_Y = 0;
	int MapUI_X = (120 / 2) - (strlen("���Ḧ ���ϸ� 0�Է� ") / 2);

	P_x = _Player->P_x;
	P_y = _Player->P_y;

	SetPosition(Map_X, Map_Y, (char*)"          /A         ");
	SetPosition(Map_X, Map_Y + 1, (char*)"         /**A            ");
	SetPosition(Map_X, Map_Y + 2, (char*)"        /****A   /A      ");
	SetPosition(Map_X, Map_Y + 3, (char*)"       /      A /**A     ");
	SetPosition(Map_X, Map_Y + 4, (char*)"      /  /A    /    A    ",6);
	SetPosition(Map_X, Map_Y + 5, (char*)"     /  /  A  /      A   ",6);
	SetPosition(Map_X, Map_Y + 6, (char*)"    /  /    A/ /A     A  ",6);
	SetPosition(Map_X, Map_Y + 7, (char*)"   /  /      A/  A/A   A ",6);
	SetPosition(Map_X, Map_Y + 8, (char*)"__/__/_______/___/__A___A",6);

	SetPosition(Map_X - 60, Map_Y + 10, (char*)"         /A          /A          /A          /A     ", 10);
	SetPosition(Map_X - 60, Map_Y + 11, (char*)"        /  A        /  A        /  A        /  A    ", 2);
	SetPosition(Map_X - 60, Map_Y + 12, (char*)"       /    A      /    A      /    A      /    A   ", 2);
	SetPosition(Map_X - 60, Map_Y + 13, (char*)"      /      A    /      A    /      A    /      A  ", 2);
	SetPosition(Map_X - 60, Map_Y + 14, (char*)"     /________A  /________A  /________A  /________A ", 2);
	SetPosition(Map_X - 60, Map_Y + 15, (char*)"        i  i        i  i        i  i        i  i    ", 6);
	SetPosition(Map_X - 60, Map_Y + 16, (char*)"        I__I        I__I        I__I        I__I    ", 6);

	SetPosition(P_x, P_y, (char*)"Player");
	SetPosition(Town_X, Town_y, (char*)"T",11);
	SetPosition(Town_X2, Town_y2, (char*)"T",11);
	SetPosition(Town_X3, Town_y3, (char*)"T",11);


	HorizenLine();
	SetPosition(MapUI_X, 21, (char*)"���Ḧ ���ϸ� 0�Է�");
	SetPosition(MapUI_X + 8, 23, (char*)" ");
	scanf("%d", &MabHelper);

	if (MabHelper == 0)
		SceneState = Scene_Stage;
}

void TownScene(OBJECT* _Player)
{
	int TownHelper = 1;
	int Count = 0;

	int TownUI_X = (120 / 2) - (strlen("��� �����Ͻðڽ��ϱ�?") / 2);
	
	OBJECT* Shop = (OBJECT*)malloc(sizeof(OBJECT));

	Shop->Name = (char*)"����";
	Shop->Inventory.Item[0] = Gold;
	Shop->Inventory.Item[1] = HpPotion;
	Shop->Inventory.Item[2] = MpPotion;
	Shop->Inventory.Item[0].quantity = 5000;
	Shop->Inventory.Item[1].quantity = 20;
	Shop->Inventory.Item[2].quantity = 20;

	HorizenLine();
	if (_Player->Inventory.Item[0].quantity < 100)
	{
		SetPosition(TownUI_X + 7, 13, (char*)"�ݾ׺���!");
		SetPosition(TownUI_X + 3, 14, (char*)"�������� �����ϴ�");

		SceneState = 2;
		TownHelper = 0;
	}
	while (TownHelper)
	{
		SetPosition(TownUI_X, 21, (char*)"��� �����Ͻðڽ��ϱ�?");
		SetPosition(TownUI_X - 5, 23, (char*)"1.HP����(100���) 2.MP����(150���)");

		SetPosition(TownUI_X + 9, 25, (char*)" ");
		scanf_s("%d", &TownHelper);

		switch (TownHelper)
		{
		case 1:
			if (Shop->Inventory.Item[1].quantity)
			{
				system("cls");
				HorizenLine();

				SetPosition(TownUI_X - 4, 21, (char*)" ");
				printf_s("� �����Ͻðڽ��ϱ�?1~%d : ", Shop->Inventory.Item[1].quantity);
				scanf_s("%d", &Count);

				if (_Player->Inventory.Item[0].quantity < (100 * Count))
				{
					SetPosition(TownUI_X + 7, 13, (char*)"�ݾ׺���!");
					break;
				}

				_Player->Inventory.Item[0].quantity = _Player->Inventory.Item[0].quantity - (100 * Count);
				Shop->Inventory.Item[0].quantity = Shop->Inventory.Item[0].quantity + (100 * Count);
				_Player->Inventory.Item[1].quantity = _Player->Inventory.Item[1].quantity + Count;
				Shop->Inventory.Item[1].quantity = Shop->Inventory.Item[1].quantity - Count;

				system("cls");
				HorizenLine();

				SetPosition(TownUI_X + 6, 21, (char*)"���� �Ϸ�!");
				SetPosition(TownUI_X + 2, 23, (char*)" ");
				printf_s("���� ���� ���� %d��\n\n", _Player->Inventory.Item[1].quantity);
				break;
			}
			else
				SetPosition(TownUI_X + 6, 14, (char*)"��� ����", 14);
			
			break;
		case 2:
			if (Shop->Inventory.Item[2].quantity)
			{
				system("cls");
				HorizenLine();

				SetPosition(TownUI_X - 4, 21, (char*)" ");
				printf_s("� �����Ͻðڽ��ϱ�?1~%d : ", Shop->Inventory.Item[2].quantity);
				scanf_s("%d", &Count);

				if (_Player->Inventory.Item[0].quantity < (100 * Count))
				{
					SetPosition(TownUI_X + 7, 13, (char*)"�ݾ׺���!");
					break;
				}
				
				_Player->Inventory.Item[0].quantity = _Player->Inventory.Item[0].quantity - (150 * Count);
				Shop->Inventory.Item[0].quantity = Shop->Inventory.Item[0].quantity + (150 * Count);
				_Player->Inventory.Item[2].quantity = _Player->Inventory.Item[2].quantity + Count;
				Shop->Inventory.Item[2].quantity = Shop->Inventory.Item[2].quantity - Count;

				system("cls");
				HorizenLine();
				SetPosition(TownUI_X + 6, 21, (char*)"���� �Ϸ�!");
				SetPosition(TownUI_X + 2, 23, (char*)" ");
				printf_s("���� ���� ���� %d��\n\n", _Player->Inventory.Item[2].quantity);
				break;
			}
			else
				SetPosition(TownUI_X + 6, 14, (char*)"��� ����", 14);

			break;
		}
		Sleep(1000);

		system("cls");
		HorizenLine();

		SetPosition(TownUI_X+1, 21, (char*)"��� �����Ͻðڽ��ϱ�?");
		SetPosition(TownUI_X + 5, 23, (char*)"1.�� 2.�ƴϿ�");

		SetPosition(TownUI_X + 9, 25, (char*)" ");
		scanf_s("%d", &TownHelper);
		if (TownHelper == 2)
		{
			system("cls");
			SetPosition(TownUI_X + 4, 14, (char*)"�������� �����ϴ�");;

			printf_s("�������� �����ϴ�\n");
			SceneState = 2;
			TownHelper = 0;
		}
	}

	free(Shop);
}

void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter)
{
	int runcounter = 0;
	int Runchance = 0;
	int Battlehelper = 0;

	int RunUI_X = (120 / 2) - (strlen("�����Ͻðڽ��ϱ� ?") / 2);
	int BattleUI_X= (120 / 2) - (strlen("1. ���� 2. ���� 3. ������ ���") / 2);
	int SkilUI_X = (120 / 2) - (strlen("� ��ų�� ����Ͻðڽ��ϱ�?") / 2);
	int VictoryUI_X = (120 / 2) - (strlen(" __   __  ___   _______  _______  _______  ______    __   __  __   __ ") / 2);
	int DeadUI_X = (120 / 2) - (strlen(" __   __  _______  __   __    ______   _______  _______  ______  ") / 2);

	
	srand(GetTickCount());

	Runchance = (rand() - (_Enemy->Info.Level - _Player->Info.Level) * 2) % 100;
	
	if (*Encounter == 1)
	{
		HorizenLine();
		SetPosition(RunUI_X, 21, (char*)"�����Ͻðڽ��ϱ�?");
		SetPosition(RunUI_X+1, 23, (char*)"1. �� 2. �ƴϿ�");
		SetPosition(RunUI_X+6, 25, (char*)" ");
		scanf("%d", &runcounter);

		if (runcounter==1)
		{
			if (Runchance>=30)
			{
				system("cls");
				SetPosition(RunUI_X + 3, 14, (char*)"���� ����!");
				*Encounter = 0;				
			}
			else
			{
				system("cls");
				SetPosition(RunUI_X + 4, 14, (char*)"���� ����!", 12);
				SetPosition(RunUI_X - 1, 15, (char*)"������ �����մϴ�!", 12);
				SetPosition(RunUI_X + 3, 29, (char*)" ", 15);
			}
		}
		Sleep(500);

		while (*Encounter)
		{
			system("cls");

			PlayerScene(_Player);
			EnemyScene(_Enemy);

			HorizenLine();

			SetPosition(BattleUI_X, 21, (char*)"1. ���� 2. ���� 3. ������ ���");
			SetPosition(BattleUI_X + 12, 23, (char*)" ");
			scanf("%d", &Battlehelper);

			switch (Battlehelper)
			{
			case 1:
				system("cls");
				if (_Player->Info.Att>_Enemy->Info.Def)
				{
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Info.Att - _Enemy->Info.Def);
					SetPosition(BattleUI_X + 4, 13, (char*)"�÷��̾��� ����!");
					SetPosition(BattleUI_X + 6, 14, (char*)" ");
					printf_s("%d ������!", (int)(_Player->Info.Att - _Enemy->Info.Def));
				}
				else
				{
					_Enemy->Info.HP -= 1;
					SetPosition(BattleUI_X + 4, 13, (char*)"�÷��̾��� ����!");
					SetPosition(BattleUI_X + 6, 14, (char*)" ");
					printf_s("1 ������!");
				}
				Sleep(500);
				if (_Enemy->Info.Att>_Player->Info.Def)
				{
					_Player->Info.HP = _Player->Info.HP - (int)(_Enemy->Info.Att - _Player->Info.Def);
					SetPosition(BattleUI_X + 4, 15, (char*)" ");
					printf_s("%s�� ����!", _Enemy->Name);
					SetPosition(BattleUI_X + 6, 16, (char*)" ");
					printf_s("%d ������!", (int)(_Enemy->Info.Att - _Player->Info.Def));
				}
				else
				{
					_Player->Info.HP -= 1;
					SetPosition(BattleUI_X + 4, 15, (char*)" ");
					printf_s("%s�� ����!", _Enemy->Name);
					SetPosition(BattleUI_X + 6, 16, (char*)" ");
					printf_s("1 ������!");
				}
				break;
			case 2:
				system("cls");

				if (_Player->Info.MP<_Player->Skill[0].Mp)
				{
					SetPosition(BattleUI_X + 7, 15, (char*)"MP ����!!", 12);
					SetPosition(BattleUI_X, 29, (char*)" ", 15);
					break;
				}
				HorizenLine();
				SetPosition(SkilUI_X, 21, (char*)"� ��ų�� ����Ͻðڽ��ϱ�?");
				SetPosition(SkilUI_X - 7, 23, (char*)" ");

				for (int i = 0; i < 3; i++)
					printf_s("%d.%s\t", _Player->Skill[i].Tier, _Player->Skill[i].Name);

				SetPosition(SkilUI_X + 11, 25, (char*)" ");
				scanf("%d", &Battlehelper);

				system("cls");
				switch (Battlehelper-1)
				{
				case 0:
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[0].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[0].Mp;

					SetPosition(SkilUI_X + 6, 13, (char*)" ");
					printf_s("%s ���!", _Player->Skill[0].Name);

					SetPosition(SkilUI_X + 7, 14, (char*)" ");
					printf_s("%d�� ������!", (int)(_Player->Skill[0].Att * _Player->Info.Int));
					break;
				case 1:
					if (_Player->Info.MP < _Player->Skill[1].Mp)
					{
						SetPosition(BattleUI_X + 7, 15, (char*)"MP ����!!", 12);
						SetPosition(BattleUI_X, 29, (char*)" ", 15);
						break;
					}
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[1].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[1].Mp;
					SetPosition(SkilUI_X + 6, 13, (char*)" ");
					printf_s("%s ���!", _Player->Skill[1].Name);

					SetPosition(SkilUI_X + 7, 14, (char*)" ");
					printf_s("%d�� ������!", (int)(_Player->Skill[1].Att* _Player->Info.Int));
					break;
				case 2:
					if (_Player->Info.MP < _Player->Skill[2].Mp)
					{
						SetPosition(BattleUI_X + 7, 15, (char*)"MP ����!!", 12);
						SetPosition(BattleUI_X, 29, (char*)" ", 15);
						break;
					}
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Skill[2].Att * _Player->Info.Int);
					_Player->Info.MP = _Player->Info.MP - _Player->Skill[2].Mp;
					SetPosition(SkilUI_X + 6, 13, (char*)" ");
					printf_s("%s ���!", _Player->Skill[2].Name);

					SetPosition(SkilUI_X + 7, 14, (char*)" ");
					printf_s("%d�� ������!", (int)(_Player->Skill[2].Att * _Player->Info.Int));
					break;
				}
				if (_Player->Info.MP < 0)
					_Player->Info.MP = 0;
				Sleep(500);
				if (_Enemy->Info.Att > _Player->Info.Def)
				{
					_Player->Info.HP = _Player->Info.HP - (int)(_Enemy->Info.Att - _Player->Info.Def);
					SetPosition(BattleUI_X + 7, 15, (char*)" ");
					printf_s("%s�� ����!", _Enemy->Name);
					SetPosition(BattleUI_X + 8, 16, (char*)" ");
					printf_s("%d ������!", (int)(_Enemy->Info.Att - _Player->Info.Def));
				}
				else
				{
					_Player->Info.HP -= 1;
					SetPosition(BattleUI_X + 7, 15, (char*)" ");
					printf_s("%s�� ����!", _Enemy->Name);
					SetPosition(BattleUI_X + 8, 16, (char*)" ");
					printf_s("1 ������!");
				}
				break;
			case 3:
				SetPosition(SkilUI_X - 1, 21, (char*)"� �������� ����Ͻðڽ��ϱ�?");

				SetPosition(SkilUI_X - 15, 23, (char*)" ");
				for (int i = 0; i < 3; i++)
					printf_s("%d.%s(%d��)",i , _Player->Inventory.Item[i].Name, _Player->Inventory.Item[i].quantity);
				printf_s("0.������� ����");

				SetPosition(SkilUI_X + 12, 25, (char*)" ");
				scanf("%d", &Battlehelper);
				switch (Battlehelper)
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
					SetPosition(SkilUI_X + 3, 25, (char*)" ");
					printf_s("%s���(���� ����%d��)", _Player->Inventory.Item[1].Name, _Player->Inventory.Item[1].quantity);
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
					SetPosition(SkilUI_X + 3, 25, (char*)" ");
					printf_s("%s���(���� ����%d��)", _Player->Inventory.Item[2].Name, _Player->Inventory.Item[2].quantity);
					break;
				case 0:
					SetPosition(SkilUI_X + 2, 25, (char*)"�������� ������� �ʽ��ϴ�.");
					break;
				}
				break;
			//����� ���
			case 4:
				_Enemy->Info.HP = 0;
				break;
			}

			Sleep(500);
			if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
			{
				if (_Player->Info.HP <= 0)
				{
					system("cls");
					SetPosition(DeadUI_X, UI_Y, (char*)" __   __  _______  __   __    ______   _______  _______  ______  ", 8);
					SetPosition(DeadUI_X, UI_Y + 1, (char*)"|  | |  ||       ||  | |  |  |      | |       ||   _   ||      | ", 8);
					SetPosition(DeadUI_X, UI_Y + 2, (char*)"|  |_|  ||   _   ||  | |  |  |  _    ||    ___||  |_|  ||  _    |", 8);
					SetPosition(DeadUI_X, UI_Y + 3, (char*)"|       ||  | |  ||  |_|  |  | | |   ||   |___ |       || | |   |", 8);
					SetPosition(DeadUI_X, UI_Y + 4, (char*)"|_     _||  |_|  ||       |  | |_|   ||    ___||       || |_|   |", 8);
					SetPosition(DeadUI_X, UI_Y + 5, (char*)"  |   |  |       ||       |  |       ||   |___ |   _   ||       |", 8);
					SetPosition(DeadUI_X, UI_Y + 6, (char*)"  |___|  |_______||_______|  |______| |_______||__| |__||______| ", 8);
					Sleep(1000);

					SetPosition(BattleUI_X + 6, 14, (char*)"������ ���ư��ϴ�");

					_Player->P_x = Town_X;
					_Player->P_y = Town_y;
					*Encounter = 0;
				}
				else
				{
					system("cls");
					SetPosition(VictoryUI_X, UI_Y, (char*)" __   __  ___   _______  _______  _______  ______    __   __  __   __ ", 3);
					SetPosition(VictoryUI_X, UI_Y + 1, (char*)"|  | |  ||   | |       ||       ||       ||    _ |  |  | |  ||  | |  |", 3);
					SetPosition(VictoryUI_X, UI_Y + 2, (char*)"|  |_|  ||   | |       ||_     _||   _   ||   | ||  |  |_|  ||  | |  |", 3);
					SetPosition(VictoryUI_X, UI_Y + 3, (char*)"|       ||   | |   ____|  |   |  |  | |  ||   |_||_ |       ||  | |  |", 3);
					SetPosition(VictoryUI_X, UI_Y + 4, (char*)"|       ||   | |   |      |   |  |  |_|  ||    __  ||_     _||__| |__|", 3);
					SetPosition(VictoryUI_X, UI_Y + 5, (char*)" |     | |   | |   |___   |   |  |       ||   |  | |  |   |   __   __ ", 3);
					SetPosition(VictoryUI_X, UI_Y + 6, (char*)"  |___|  |___| |_______|  |___|  |_______||___|  |_|  |___|  |__| |__|", 3);
					Sleep(1000);

					//����� ��ġ ��Ƣ��(������ 25)
					_Player->Info.EXP = _Player->Info.EXP + (_Enemy->Info.Level * 25);
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
	int Width = (120 / 2) - (strlen("����� ������ ����") / 2);

	HorizenLine();

	while (inventoryHelper)
	{
		SetPosition(Width, 21, (char*)"����� ������ ����\n");
		SetPosition(Width-20, 23, (char*)" ");

		for (int i = 0; i < 3; i++)
			printf_s("%d. %s(%d��) ", i, _Player->Inventory.Item[i].Name, _Player->Inventory.Item[i].quantity);
		printf_s("0. ����\n");
		SetPosition(Width, 21, (char*)"����� ������ ����\n");
		SetPosition(Width + 9, 25, (char*)" ");
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
	for (int i = 0; i < 120; i++)
		SetPosition(Width+i, Height, (char*)"-");
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