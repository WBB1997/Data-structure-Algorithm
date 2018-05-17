#ifndef AvlTree_H
#define AvlTree_H

#ifndef AVLNODE
#define AVLNODE
struct AvlNode
{
	int Element;
	AvlNode *Left;
	AvlNode *Right;
	int Height;
};
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
#endif // !1

AvlTree MakeEmpty(AvlTree T);
Position Find(int X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(int X, AvlTree T);
AvlTree Remove(int X, AvlTree T);
void Destory(AvlTree T);
void PreOrder(AvlTree T);
void InOrder(AvlTree T);
void PostOrder(AvlTree T);

#endif // !AvlTree_H

