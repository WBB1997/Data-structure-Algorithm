#include "AvlTree.h"
#include <iostream>
using std::cout;
#define max(a,b) a>b?a:b

static int Height(Position P) {
	if (P == NULL)
		return 0;
	else
		return P->Height;
}

static Position SingleRotateWithLeft(Position K2) {
	Position K1;
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = (max(Height(K2->Left), Height(K2->Right))) + 1;
	K1->Height = (max(Height(K1->Left), Height(K1->Right))) + 1;
	return K1;
}

static Position SingleRotateWithRight(Position K2) {
	Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = (max(Height(K2->Left), Height(K2->Right))) + 1;
	K1->Height = (max(Height(K1->Left), Height(K1->Right))) + 1;
	return K1;
}

static Position DoubleRotateWithLeft(Position K3) {

	K3->Left = SingleRotateWithLeft(K3->Left);
	return SingleRotateWithRight(K3);
}

static Position DoubleRotateWithRight(Position K3) {

	K3->Right = SingleRotateWithRight(K3->Right);
	return SingleRotateWithLeft(K3);
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		delete(T);
	}
	return NULL;
}

Position FindMin(AvlTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(AvlTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Right == NULL)
		return T;
	else
		return FindMax(T->Right);
}

Position Find(int X, AvlTree T) {
	if (T == NULL)
		return NULL;
	else if (X > T->Element)
		return Find(X, T->Left);
	else if (X < T->Element)
		return Find(X, T->Right);
	else
		return T;
}

AvlTree Insert(int X, AvlTree T) {
	if (T == NULL) {
		T = new AvlNode;
		if (T == NULL)
			cout << "Out of space!!!";
		else {
			T->Element = X;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (X < T->Element) {
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
			if (X < T->Left->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
			if (X > T->Right->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithRight(T);
	}

	T->Height = (max(Height(T->Left), Height(T->Right))) + 1;
	return T;
}

AvlTree Remove(int X, AvlTree T) {

	Position Tmp;
	if (T != NULL) {

		if (X == T->Element) {
			if (T->Left != NULL && T->Right != NULL) {
				if (Height(T->Left) > Height(T->Right)) {
					Tmp = FindMax(T->Left);
					T->Element = Tmp->Element;
					T->Left = Remove(Tmp->Element, T->Left);
				}
				else {
					Tmp = FindMin(T->Right);
					T->Element = Tmp->Element;
					T->Right = Remove(Tmp->Element, T->Right);
				}
			}
			else {
				Tmp = T;
				if (T->Left == NULL) {
					T = T->Right;
				}
				else if (T->Right = NULL) {
					T = T->Left;
				}
				delete Tmp;
			}
		}
		else if (X > T->Element) {
			T->Right = Remove(X, T->Right);
			// Removing the imbalance caused by the right node is equivalent 
			// to adding a node to the left node.
			if (Height(T->Left) - Height(T->Right) == 2)
			{
				if (T->Left->Right != NULL) 
					T = DoubleRotateWithLeft(T);
				else
					T = SingleRotateWithRight(T);
			}
		}
		else if (X < T->Element) {
			T->Left = Remove(X, T->Left);
			// Removing the imbalance caused by the left node is equivalent 
			// to adding a node to the right node.
			if (Height(T->Right) - Height(T->Left) == 2) {
				if (T->Right->Left != NULL)
					T = DoubleRotateWithRight(T);
				else
					T = SingleRotateWithLeft(T);
			}
		}
	}
	return T;
}

void PreOrder(AvlTree T) {
	if (T != NULL) {
		cout << T->Element << " ";
		PreOrder(T->Left);
		PreOrder(T->Right);
	}
}

void InOrder(AvlTree T) {
	if (T != NULL) {
		InOrder(T->Left);
		cout << T->Element << " ";
		InOrder(T->Right);
	}
}

void PostOrder(AvlTree T) {
	if (T != NULL) {
		PreOrder(T->Left);
		PreOrder(T->Right);
		cout << T->Element << " ";
	}
}

void Destory(AvlTree T) {
	if (T != NULL) {
		Destory(T->Left);
		Destory(T->Right);
		delete T;
		T = NULL;
	}
}