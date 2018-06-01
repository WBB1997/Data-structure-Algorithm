// 这里利用线段树来举一个进行区间加法的例子
#include <iostream>
#define maxn 10000
using namespace std;
int tree[maxn * 4]; // 开4倍的空间用来模拟树
int A[maxn];        // 储存原始数据的数组

// 针对线段树的不同应用应进行不同的节点更新方式
void PushUp(int p) {   // p代表树中的当前节点位置
	// 这里是进行区间加法
	tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

// 递归建立线段树
void Build(int l, int r, int p) { // [l,r]为当前节点代表的区间,p代表树中的当前节点位置，tree[p]也就是[l,r]区间所代表的值
	if (l == r) { // 到达叶子节点，递归建立完成
		tree[p] = A[l];
		return;
	}
	int m = (l + r) / 2; // 将区间一分为2，然后分别递归建立左右子树
	Build(l, m, p * 2);
	Build(m + 1, r, p * 2 + 1);
	// 左右子树建立完后更新当前节点的值
	PushUp(p);
}

// 节点修改 如A[T] += C
void Update(int T, int C, int l, int r, int p) { // [l,r]表示当前节点代表的区间,p代表树中的当前节点位置，tree[p]也就是[l,r]区间所代表的值
	if (l == r) { // 到达叶子节点，递归修改完成
		tree[p] += C;
		return;
	}
	int m = (l + r) / 2; // 将区间一分为2，然后分情况修改左子树或右子树 [l,m],[m+1,r]
	if (T <= m)
		Update(T, C, l, m, p * 2);
	else
		Update(T, C, m + 1, r, p * 2 + 1);
	// 左右子树修改完后更新当前节点的值
	PushUp(p);
}

// 区间查询 如查询A[L] - A[R]之间的和
int Query(int L, int R, int l, int r, int p) { // L,R 代表需要查询的区间，[l,r]表示当前节点代表的区间,p代表树中的当前节点位置，tree[p]也就是[l,r]区间所代表的值
	if (L <= l && r <= R) { // 当前区间[l,r] <= [L,R] 那么就直接返回区间[l,r]的值
		return tree[p];
	}
	int m = (l + r) / 2;// 将区间一分为2 [l,m],[m+1,r]
	// 然后进行分别求和，最后相加
	// 存在重叠的区间，则递归求和
	int ans = 0;
	// 第一种情况
	//    [L          R]
	// [......m]
	if (L <= m)
		ans += Query(L, R, l, m, p * 2);
	// 第二种情况
	// [L          R]
	//         [m+1....]
	if (R >= m + 1)
		ans += Query(L, R, m + 1, r, p * 2 + 1);
	return ans;
}

int main() {
	for (int i = 0; i <= 12; i++) {
		A[i+1] = i % 4 + 1;
	}
	// A[0,1,2,3,4,1,2,3,4,1,2,3,4,1,...]
	Build(1, 13, 1);
	cout << Query(2, 12, 1, 13, 1) << endl; // 29
	Update(6, 7, 1, 13, 1);
	cout << Query(2, 12, 1, 13, 1) << endl; // 36
}