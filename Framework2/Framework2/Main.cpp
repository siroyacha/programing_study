#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

typedef struct tagInfo
{
	int iNumber;

	tagInfo()
	{
		cout << "�⺻ ������" << endl;
	};
	tagInfo(int _iNumber)
	{
		iNumber = _iNumber;
		cout << "���� ������" << endl;
	};

}INFO;

int main(void)
{
	//cout << "���� ���" << endl;
	//cout << "endl�� ����ϸ�" << endl << "�ٹٲ�" << endl;

	/*
	int iNumber = 0;

	cout << "�Է� : ";
	cin >> iNumber;
	cout << "��� : " << iNumber << endl;
	*/

	//INFO* pInfo = (INFO*)malloc(sizeof(INFO));
	//INFO* pInfo = new INFO(15);
	//cout << pInfo->iNumber << endl;

	//free(pInfo);
	//delete(pInfo);

	INFO* pInfo[10];

	for (int i = 0; i < 10; i++)
	{
		pInfo[i] = new INFO(i + 2);
		cout << pInfo[i]->iNumber << endl;
	}

	return 0;
}