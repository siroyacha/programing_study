#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

typedef struct tagInfo
{
	int iNumber;

	tagInfo()
	{
		cout << "기본 생성자" << endl;
	};
	tagInfo(int _iNumber)
	{
		iNumber = _iNumber;
		cout << "복사 생성자" << endl;
	};

}INFO;

int main(void)
{
	//cout << "문자 출력" << endl;
	//cout << "endl을 사용하면" << endl << "줄바꿈" << endl;

	/*
	int iNumber = 0;

	cout << "입력 : ";
	cin >> iNumber;
	cout << "출력 : " << iNumber << endl;
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