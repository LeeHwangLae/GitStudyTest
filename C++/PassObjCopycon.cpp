#include <iostream>
#include <string>
using namespace std;

class SoSimple
{
	int num;
public:
	SoSimple(int n) : num(n) {}
	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		cout << "Call SoSimple(const SoSimple& copy)" << endl;
	}
	void ShowData()
	{
		cout << "num: " << num << endl;
	}
};

void SimpleFunObj(SoSimple ob)
{
	ob.ShowData();
}
int main()
{
	SoSimple obj(7);
	cout << "함수호출 전" << endl;
	SimpleFunObj(obj);
	cout << "함수호출 후" << endl;
	return 0;
}