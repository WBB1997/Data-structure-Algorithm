// ���������߶�������һ����������ӷ�������
#include <iostream>
#define maxn 10000
using namespace std;
int tree[maxn * 4]; // ��4���Ŀռ�����ģ����
int lazy[maxn * 4]; // ����ÿ���ڵ��������
int A[maxn];        // ����ԭʼ���ݵ�����

// ����߶����Ĳ�ͬӦ��Ӧ���в�ͬ�Ľڵ���·�ʽ
void PushUp(int p) {   // p�������еĵ�ǰ�ڵ�λ��
	// �����ǽ�������ӷ�
	// ȷ���ڸ��µ�ǰ�ڵ�ֵ֮ǰ���Ѿ�����ǰ�ڵ������������
	tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

// ����������
void PushDown(int p, int l_num, int r_num) { // pΪ��ǰ���ڵ㣬l_numΪ�����������䳤��, r_numΪ�����������䳤��
	// �����ǰ�ڵ��������ǣ�������
	if (lazy[p]) {
		// ���Ʊ��
		lazy[p * 2] += lazy[p];
		lazy[p * 2 + 1] += lazy[p];
		// �޸�����������ֵ
		tree[p * 2] += lazy[p] * l_num;
		tree[p * 2 + 1] += lazy[p] * r_num;
		// ������ɣ������ǰ�ڵ��������
		lazy[p] = 0;
	}
}

// �ݹ齨���߶���
void Build(int l, int r, int p) { // [l,r]Ϊ��ǰ�ڵ���������,p�������еĵ�ǰ�ڵ�λ�ã�tree[p]Ҳ����[l,r]�����������ֵ
	if (l == r) { // ����Ҷ�ӽڵ㣬�ݹ齨�����
		tree[p] = A[l];
		return;
	}
	int m = (l + r) / 2; // ������һ��Ϊ2��Ȼ��ֱ�ݹ齨����������
	Build(l, m, p * 2);
	Build(m + 1, r, p * 2 + 1);
	// �����������������µ�ǰ�ڵ��ֵ
	PushUp(p);
}

// �ڵ��޸� ��A[T] += C
void Update(int T, int C, int l, int r, int p) { // [l,r]��ʾ��ǰ�ڵ���������,p�������еĵ�ǰ�ڵ�λ�ã�tree[p]Ҳ����[l,r]�����������ֵ
	if (l == r) { // ����Ҷ�ӽڵ㣬�ݹ��޸����
		tree[p] += C;
		return;
	}
	int m = (l + r) / 2; // ������һ��Ϊ2��Ȼ�������޸��������������� [l,m],[m+1,r]
	// �޸�֮ǰ�����Ʊ��
	PushDown(p, m - l + 1, r - m);

	if (T <= m)
		Update(T, C, l, m, p * 2);
	else
		Update(T, C, m + 1, r, p * 2 + 1);
	// ���������޸������µ�ǰ�ڵ��ֵ
	PushUp(p);
}

// �����ѯ ���ѯA[L] - A[R]֮��ĺ�
int Query(int L, int R, int l, int r, int p) { // L,R ������Ҫ��ѯ�����䣬[l,r]��ʾ��ǰ�ڵ���������,p�������еĵ�ǰ�ڵ�λ�ã�tree[p]Ҳ����[l,r]�����������ֵ
	if (L <= l && r <= R) { // ��ǰ����[l,r] <= [L,R] ��ô��ֱ�ӷ�������[l,r]��ֵ
		return tree[p];
	}
	int m = (l + r) / 2;// ������һ��Ϊ2 [l,m],[m+1,r]
	// ��ѯ֮ǰ�����Ʊ��
	PushDown(p, m - l + 1, r - m);

	// Ȼ����зֱ���ͣ�������
	// �����ص������䣬��ݹ����
	int ans = 0;
	// ��һ�����
	//    [L          R]
	// [......m]
	if (L <= m)
		ans += Query(L, R, l, m, p * 2);
	// �ڶ������
	// [L          R]
	//         [m+1....]
	if (R >= m + 1)
		ans += Query(L, R, m + 1, r, p * 2 + 1);
	return ans;
}

// �����޸�
void Add(int L, int R, int C, int l, int r, int p) { // ��[L,R] += C, l,rΪ��ǰ����,pΪ��ǰ���ڵ�
	if (L == l && R == r) { // �ҵ�Ŀ������
		// �ȸ���������
		lazy[p] += C;
		// �ٸ��µ�ǰֵ
		tree[p] += (R - L + 1) * C;
		return;
	}
	// ����Ҷ�ӽڵ㣬����
	if (l == r)
		return;
	int m = (l + r) / 2;
	// �����Ʊ��
	PushDown(p, m - l + 1, r - m);
	// �ٷ�������������޸�
	//         ��һ�����
	//    [l      m][m+1     R]
	// [L     R]
	if (R <= m)
		Add(L, R, C, l, m, p * 2);
	//         �ڶ������
	//    [l      m][m+1     R]
	//                   [L     R]
	else if (L >= m + 1)
		Add(L, R, C, m + 1, r, p * 2 + 1);
	//          ���������
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