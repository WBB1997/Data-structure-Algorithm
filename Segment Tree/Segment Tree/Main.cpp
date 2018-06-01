// ���������߶�������һ����������ӷ�������
#include <iostream>
#define maxn 10000
using namespace std;
int tree[maxn * 4]; // ��4���Ŀռ�����ģ����
int A[maxn];        // ����ԭʼ���ݵ�����

// ����߶����Ĳ�ͬӦ��Ӧ���в�ͬ�Ľڵ���·�ʽ
void PushUp(int p) {   // p�������еĵ�ǰ�ڵ�λ��
	// �����ǽ�������ӷ�
	tree[p] = tree[p * 2] + tree[p * 2 + 1];
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