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
	cout << "树高：" << a->Height << endl;

	cout << "先序遍历:" << endl;
	PreOrder(a);

	a = Remove(2, a);
	a = Remove(4, a);
	cout << endl;

	cout << "先序遍历:" << endl;
	PreOrder(a); cout << endl;
	cout << "中序遍历:" << endl;
	InOrder(a);

	Destory(a);
	a = NULL;
	cout << "中序遍历:" << endl;
	InOrder(a);
	return 0;
}