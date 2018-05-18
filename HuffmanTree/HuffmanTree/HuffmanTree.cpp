#include <iostream>  
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

struct Node
{
	double weight;
	char ch;
	string code;
	int lchild, rchild, parent;
};

class HuffMan {
private:
	Node* huffTree; // 树
	int n;  // 字符数
	int* w; // 权值
public:
	HuffMan(int n) {
		huffTree = new Node[2 * n + 1];
		w = new int[n];
		this->n = n;
	}
	~HuffMan() {
		delete[] huffTree;
		delete[] w;
	}
	void select(int *a, int *b, int n)//找权值最小的两个a和b  
	{
		int i;
		double weight = 0; //找最小的数
		for (i = 0; i < n; i++)
		{
			if (huffTree[i].parent != -1)     //判断节点是否已经选过
				continue;
			else
			{
				if (weight == 0)
				{
					weight = huffTree[i].weight;
					*a = i;
				}
				else
				{
					if (huffTree[i].weight < weight)
					{
						weight = huffTree[i].weight;
						*a = i;
					}
				}
			}
		}
		weight = 0; //找第二小的数
		for (i = 0; i < n; i++)
		{
			if (huffTree[i].parent != -1 || (i == *a))//排除已选过的数
				continue;
			else
			{
				if (weight == 0)
				{
					weight = huffTree[i].weight;
					*b = i;
				}
				else
				{
					if (huffTree[i].weight < weight)
					{
						weight = huffTree[i].weight;
						*b = i;
					}
				}
			}
		}
		int temp;
		if (huffTree[*a].lchild < huffTree[*b].lchild)  //小的数放左边
		{
			temp = *a;
			*a = *b;
			*b = temp;
		}
	}
	void Huff_Tree(string str, vector<int>& w)
	{
		for (int i = 0; i < 2 * n - 1; i++) {//初始过程
			huffTree[i].parent = -1;
			huffTree[i].lchild = -1;
			huffTree[i].rchild = -1;
			huffTree[i].code = "";
		}
		for (int i = 0; i < n; i++) {
			huffTree[i].weight = w[i];
			huffTree[i].ch = str[i];
		}
		for (int k = n; k < 2 * n - 1; k++) {
			int i1 = 0;
			int i2 = 0;
			select(&i1, &i2, k); //将i1，i2节点合成节点k
			huffTree[i1].parent = k;
			huffTree[i2].parent = k;
			huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
			huffTree[k].lchild = i1;
			huffTree[k].rchild = i2;
		}
	}
	void Huff_Code()
	{
		int i, j, k;
		string s = "";
		for (i = 0; i < n; i++) {
			s = "";
			j = i;
			while (huffTree[j].parent != -1) { //从叶子往上找到根节点
				k = huffTree[j].parent;
				if (j == huffTree[k].lchild) //如果是根的左孩子，则记为0
					s = s + "0";
				else
					s = s + "1";
				j = huffTree[j].parent;
			}
			cout << "字符 " << huffTree[i].ch << " 的编码：";
			for (int l = s.size() - 1; l >= 0; l--) {
				cout << s[l];
				huffTree[i].code += s[l]; //保存编码
			}
			cout << endl;
		}
	}
	string Huff_Decode(string s) {
		cout << "解码后为：";
		string temp = "", str = "";//保存解码后的字符串
		for (unsigned i = 0; i < s.size(); i++) {
			temp = temp + s[i];
			for (int j = 0; j < n; j++) {
				if (temp == huffTree[j].code) {
					str = str + huffTree[j].ch;
					temp = "";
					break;
				}
				else if (i == s.size() - 1 && j == n - 1 && temp != "") {//全部遍历后没有
					str = "解码错误！";
				}
			}
		}
		return str;
	}
};

int main()
{
	// 重定向与文本文件,这里修改读取文件
	freopen("1.txt", "r", stdin);
	//编码过程
	int n;
	cin >> n;
	string s("");
	vector<int> w;
	for (unsigned i = 0; i < n; i++) {
		char c;
		int weight;
		cin >> c >> weight;
		s.push_back(c);
		w.push_back(weight);
	}
	HuffMan hf(n);
	hf.Huff_Tree(s, w);
	cout << "各个字符编码为：" << endl;
	hf.Huff_Code();
	//解码过程
	string s1("01010101");
	cout << hf.Huff_Decode(s1) << endl;
	return 0;
}