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
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
	void ShowData()
	{
		cout << "num: " << num << endl;
	}
};

SoSimple SimpleFunObj(SoSimple ob)
{
	cout << "return ÀÌÀü" << endl;
	return ob;
}
int main()
{
	SoSimple obj(7);
	SimpleFunObj(obj).AddNum(30).ShowData();
	obj.ShowData();
	return 0;
}