#include "AvlTree.h"
#include <iostream>
using namespace std;

int main()
{
	AvlTree a;
	a = NULL;
	int av[] = { 4,5};
	for (int i = 0; i < 2; i++)
		a = Insert(av[i], a);
	cout << "���ߣ�" << a->Height << endl;

	cout << "�������:" << endl;
	PreOrder(a);

	a = Remove(2, a);
	a = Remove(4, a);
	cout << endl;

	cout << "�������:" << endl;
	PreOrder(a); cout << endl;
	cout << "�������:" << endl;
	InOrder(a);

	Destory(a);
	a = NULL;
	cout << "�������:" << endl;
	InOrder(a);
	return 0;
}