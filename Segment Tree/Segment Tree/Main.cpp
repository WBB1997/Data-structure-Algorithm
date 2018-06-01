// 这里利用线段树来举一个进行区间加法的例子
#include <iostream>
#define maxn 10000
using namespace std;
int tree[maxn * 4]; // 开4倍的空间用来模拟树
int lazy[maxn * 4]; // 储存每个节点的懒惰标记
int A[maxn];        // 储存原始数据的数组

// 针对线段树的不同应用应进行不同的节点更新方式
void PushUp(int p) {   // p代表树中的当前节点位置
	// 这里是进行区间加法
	// 确保在更新当前节点值之前，已经将当前节点的懒惰标记下推
	tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

// 下推懒惰标记
void PushDown(int p, int l_num, int r_num) { // p为当前树节点，l_num为左子树的区间长度, r_num为右子树的区间长度
	// 如果当前节点有懒惰标记，则下推
	if (lazy[p]) {
		// 下推标记
		lazy[p * 2] += lazy[p];
		lazy[p * 2 + 1] += lazy[p];
		// 修改左右子树的值
		tree[p * 2] += lazy[p] * l_num;
		tree[p * 2 + 1] += lazy[p] * r_num;
		// 下推完成，清除当前节点的懒惰标记
		lazy[p] = 0;
	}
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
	// 修改之前先下推标记
	PushDown(p, m - l + 1, r - m);

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
	// 查询之前先下推标记
	PushDown(p, m - l + 1, r - m);

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

// 区间修改
void Add(int L, int R, int C, int l, int r, int p) { // 将[L,R] += C, l,r为当前区间,p为当前树节点
	if (L == l && R == r) { // 找到目标区间
		// 先更新懒惰标记
		lazy[p] += C;
		// 再更新当前值
		tree[p] += (R - L + 1) * C;
		return;
	}
	// 到达叶子节点，返回
	if (l == r)
		return;
	int m = (l + r) / 2;
	// 先下推标记
	PushDown(p, m - l + 1, r - m);
	// 再分情况进行区间修改
	//         第一种情况
	//    [l      m][m+1     R]
	// [L     R]
	if (R <= m)
		Add(L, R, C, l, m, p * 2);
	//         第二种情况
	//    [l      m][m+1     R]
	//                   [L     R]
	else if (L >= m + 1)
		Add(L, R, C, m + 1, r, p * 2 + 1);
	//          第三种情况
	//    [l      m][m+1     R]
	//       [L          R]
	//       [L  m][m+1  R]
	else {
		Add(L, m, C, l, m, p * 2);
		Add(m+1, R, C, m + 1, r, p * 2 + 1);
	}
	PushUp(p);
}

int main() {
	for (int i = 0; i <= 12; i++) {
		A[i+1] = i % 4 + 1;
	}
	// A[0,1,2,3,4,1,2,3,4,1,2,3,4,1,...]

	Build(1, 13, 1);
	cout << Query(1, 13, 1, 13, 1) << endl; // 29

	Update(6, 7, 1, 13, 1);  // A[6] += 7;
	cout << Query(1, 13, 1, 13, 1) << endl; // 36

	Add(2, 12, 1, 1, 13, 1); // [2, 12] += 1;
	cout << Query(1, 13, 1, 13, 1) << endl; // 47
	return 0;
}