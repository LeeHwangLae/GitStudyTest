#include <iostream>
#include<cstdlib>
#include<ctime>
#include <fstream>
using namespace std;

int main()
{
	char* file = "user.bin";
	
	int userNum;
	cout << "����� ���� �Է�: ";
	cin >> userNum;
	cout << "### ������ ���� ###"<<endl;

	ofstream fout;
	fout.open(file, ios::out | ios::binary);
	if (!fout)
	{
		cout << "���� ���� ����";
		return 0;
	}

	int *userSize=new int[userNum];
	int *levelSize = new int[userNum];
	srand((unsigned)time(NULL));
	for (int i = 0; i < userNum; i++)
	{
		userSize[i] = (i+1)*100;
		levelSize[i]= rand() % 1000 + 1;
		cout << userSize[i] << " " << levelSize[i] <<endl;
		fout.write((char*)&userSize[i], sizeof(userSize[i]));
		//fout.write((char*)(&levelSize[i]), sizeof(levelSize[i]));
	}
	
	fout.close();

	cout << "���� user.bin�� �����Ͽ����ϴ�." << endl;
	cout << "### �������� user.bin ������ ###" << endl;

	ifstream fin(file, ios::in | ios::binary);
	if (!fin)
	{
		cout << "���� ���� ����";
		return 0;
	}
	
	for (int i = 0; i < userNum; i++)
	{
		fin.read((char*)&userSize[i], sizeof(userSize[i]));
		//fin.read((char*)(&levelSize[i]), sizeof(levelSize[i]));
		cout << userSize[i] << " " << levelSize[i] << endl;
	}
	fin.close();

	delete[] userSize;
	delete[] levelSize;
}