#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>

// ��Ʈ������ ���� 30�� �ȳѱ��
// 16�� �п� ��� '��'���� ���� ������

// ** ���� : https://www.youtube.com/watch?v=_nuS86ITjIM
// ** �ƽ�Ű ��Ʈ : http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20

// ** ����	 0
// ** ��ο� �Ķ�	 1
// ** ��ο� �ʷ�	 2
// ** ��ο� �ϴ�	 3
// ** ��ο� ����	 4
// ** ��ο� ����	 5
// ** ��ο� ���	 6
// ** ȸ��	 7
// ** ��ο� ȸ��	 8
// ** �Ķ�	 9
// ** �ʷ�	 10
// ** �ϴ�	 11
// ** ����	 12
// ** ����	 13
// ** ���	 14
// ** �Ͼ�	 15

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
const int Scene_Invetory = 7;

int SceneState = 0;

int Check = 1;


//�÷��̾�� ���� �� ĳ���͵��� ������ �����ϴ� ����ü
typedef struct tagInfo
{
	// ** ���� Ÿ���� �緮(int, float ��� ����)
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

// ** ������Ʈ ������ ���� ���� ����ü
typedef struct tagObject
{
	char* Name;
	INFO Info;
	Inventory Inventory;
	int P_x;
	int P_y;
}OBJECT;

Item HpPotion = { (char*)"HP����",1,1 };
Item MpPotion = { (char*)"MP����",2,1 };
//�ʿ��� �Լ����� ���漱��

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
void Move(OBJECT* _Player, int* Encounter);
int EnCounter();
void BattelScene(OBJECT* _Player, OBJECT* _Enemy, int* Encounter);
void MapScene(OBJECT* _Player);
void TownScene(OBJECT* _Player);
void InventoryScene(OBJECT* _Player);

int main()
{

	// ** Ŀ���� �Ⱥ��̰� ��
	HideCursor();

	// ** �ܼ�â ������ ����
	system("mode con:cols=120 lines=30");

	//**�ܼ�â �̸� ����
	system("title ������ Framework v0.8");

	// ** ��ü ������ ������.
	//system("color 70");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	OBJECT* Monster = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy(Monster);

	DWORD dwTime = GetTickCount(); // 1/1000 (1000���� 1��)
	int Delay = 1000;

	int UpCount = 0;

	while (true)
	{
		if (dwTime + Delay < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

			printf_s("%s\n", Player->Name);

			// ** ���� ����
			SceneManager(Player, Monster);
		}
	}

	free(Player);
	free(Monster);
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
		exit(NULL);// ** ���α׷� ����
		break;
	case Scene_Battel:
	//	BattelScene(_Player, _Enemy, Encounter)
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
	printf_s("MenuScene\n");

	printf_s("������ ���� �Ͻðڽ��ϱ�?\n1. ����\n2. ����\n�Է� : ");

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

	_Player->Info.Type = SetPlayerJob();

	_Player->Info.Att = 20;
	_Player->Info.Def = 10;
	_Player->Info.EXP = 0;
	_Player->Info.HP = 100;
	_Player->Info.MP = 10;
	_Player->Info.Level = 1;

	_Player->P_x = 10;
	_Player->P_y = 15;

	_Player->Inventory.Item[1] = HpPotion;
	_Player->Inventory.Item[2] = MpPotion;
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
void StageScene(OBJECT* _Player, OBJECT* _Enemy)
{
	int Encounter = 0;
	//�̵�
	Move(_Player, &Encounter);
	
	// ** ����
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
	printf_s("���� : %02d\n���� : %d\nü�� : %d\n���� : %d\n���ݷ� : %0.2f\n���� : %0.2f\n����ġ : %03d\n",
		_Object->Info.Level,_Object->Info.Type, _Object->Info.HP, _Object->Info.MP, _Object->Info.Att, _Object->Info.Def, _Object->Info.EXP);
}

void Move(OBJECT* _Player, int* Encounter)
{
	int MoveHelper = 0;

	int Width = 0;
	int Height = 20;
	SetPosition(Width, Height, (char*)"-------------------------------------------------------------------------------------------------\n");
	
	printf_s("�̵� �Ͻðڽ��ϱ�?\n1.����̵� 2.�ϴ��̵� 3.�����̵� 4.�����̵� 5.������ ���(Ȯ��) 6.�������� 7.���� 0.���� \n�Է� : ");
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
		_Player->P_x -= 5;
		break;
	case 4:
		*Encounter = EnCounter();
		_Player->P_x += 5;
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
	case 0:
		exit(NULL);
		break;
	}
	if (*Encounter)
		printf_s("���� ����!\n");
	else
		printf_s("�̵� ����\n");

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
	int MabHelper = 0;
	int P_x = 0;
	int P_y = 0;
	int UI_x = 0;
	int UI_y = 50;

	P_x = _Player->P_x;
	P_y = _Player->P_y;
	SetPosition(P_x, P_y, (char*)"test\n");

	SetPosition(UI_x, UI_y, (char*)"���Ḧ ���ϸ� 1�Է�\n");

	scanf("%d", &MabHelper);

	if (MabHelper)
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

	Shop->Name = (char*)"����";
	Shop->Inventory.Item[0] = _ShopHppotion;
	Shop->Inventory.Item[1] = _ShopMppotion;
	while (TownHelper)
	{
		printf_s("��� �����Ͻðڽ��ϱ�?\n1.HP���� 2.MP����\n");
		scanf_s("%d", &TownHelper);

		switch (TownHelper)
		{
		case 1:
			if (Shop->Inventory.Item[0].quantity)
			{
				printf_s("� �����Ͻðڽ��ϱ�?1~%d\n", Shop->Inventory.Item[0].quantity);
				scanf_s("%d", &Count);
				_Player->Inventory.Item[1].quantity = _Player->Inventory.Item[1].quantity + Count;
				Shop->Inventory.Item[0].quantity = Shop->Inventory.Item[0].quantity - Count;
				printf_s("���� �Ϸ�!\n");
				printf_s("���� ���� ���� %d��\n", _Player->Inventory.Item[0].quantity);
				break;
			}

			printf_s("��� ����\n");
			break;
		case 2:
			if (Shop->Inventory.Item[1].quantity)
			{
				printf_s("� �����Ͻðڽ��ϱ�?1~%d\n", Shop->Inventory.Item[1].quantity);
				scanf_s("%d", &Count);
				_Player->Inventory.Item[2].quantity = _Player->Inventory.Item[2].quantity + Count;
				Shop->Inventory.Item[1].quantity = Shop->Inventory.Item[1].quantity - Count;
				printf_s("���� ���� ���� %d��\n", _Player->Inventory.Item[1].quantity);
				break;
			}

			printf_s("��� ����\n");
			break;
		}
		printf_s("��� �����Ͻðڽ��ϱ�?\n1.�� 2.�ƴϿ�\n");
		scanf_s("%d", &TownHelper);
		if (TownHelper == 2)
		{
			printf_s("�������� �����ϴ�\n");
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
		printf_s("�����Ͻðڽ��ϱ�?\n1. �� 2. �ƴϿ�\n");
		scanf("%d", &runcounter);

		if (runcounter==1)
		{
			if (runchance>=30)
			{
				printf_s("���� ����!\n");
				*Encounter = 0;				
			}
			else
				printf("���� ����\n������ �����մϴ�\n");				
		}
		Sleep(500);

		while (*Encounter)
		{
			system("cls");

			PlayerScene(_Player);
			EnemyScene(_Enemy);

			printf_s("1. ���� 2. ���� 3. ������ ���\n");
			scanf("%d", &battelhelper);

			switch (battelhelper)
			{
			case 1:
				if (_Player->Info.Att>_Enemy->Info.Def)
				{
					_Enemy->Info.HP = _Enemy->Info.HP - (int)(_Player->Info.Att - _Enemy->Info.Def);
					printf_s("�÷��̾��� ����!\n%d ������!\n", (int)(_Player->Info.Att - _Enemy->Info.Def));
				}
				else
				{
					_Enemy->Info.HP -= 1;
					printf_s("�÷��̾��� ����!\n1 ������!\n");
				}
				Sleep(500);
				if (_Enemy->Info.Att>_Player->Info.Def)
				{
					_Player->Info.HP = _Player->Info.HP - (int)(_Enemy->Info.Att - _Player->Info.Def);
					printf_s("%s�� ����!\n%d ������!\n", _Enemy->Name, (int)(_Enemy->Info.Att - _Player->Info.Def));
				}
				else
				{
					_Player->Info.HP -= 1;
					printf_s("%s�� ����!\n1 ������!\n", _Enemy->Name);
				}
				Sleep(500);
				if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
				{
					printf_s("���� ����");
					if (_Player->Info.HP<=0)
					{
						printf_s("����� ����ϼ̽��ϴ�.\n������ ���ư��ϴ�");
						*Encounter = 0;
					}
					else
					{
						printf_s("�¸�!\n");
						_Player->Info.EXP = _Player->Info.EXP + (_Enemy->Info.Level * 50);
						*Encounter = 0;
					}
				}
				break;
			}
		}
	}
}

void InventoryScene(OBJECT* _Player)
{
	int inventoryHelper = 1;
	int itemtype = 0;
	//null���� �ƴ� �ٸ� ������� ������ ���� Ȯ���ؾ� ��
	/*
	if (_Player->Inventory.Item==NULL)
	{
		printf_s("�������� �������� �ʽ��ϴ�!!\n�̵�ȭ������ ���ư��ϴ�");
		inventoryHelper = 0;
	}
	*/
	while (inventoryHelper)
	{
		printf_s("����� ������ ����\n");
		for (int i = 1; i < 3; i++)
		{
			printf_s("%d. %s(%d��) ", i, _Player->Inventory.Item[i].Name, _Player->Inventory.Item[i].quantity);
		}
		printf_s("0. ����\n");
		scanf("%d", &inventoryHelper);

		_Player->Inventory.Item[inventoryHelper].quantity--;
		itemtype = _Player->Inventory.Item[inventoryHelper].type;

		switch (itemtype)
		{
		case 1:
			_Player->Info.HP += 10;
			break;
		case 2:
			_Player->Info.MP += 10;
			break;
		}
	}

	SceneState = Scene_Stage;
}
