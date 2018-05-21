#include <iostream>  
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <fstream>
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
	Node * huffTree; // 树
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
	void Huff_Tree(vector<char>& str, vector<int>& w)
	{
		int i;
		for (i = 0; i < 2 * n - 1; i++) {//初始过程
			huffTree[i].parent = -1;
			huffTree[i].lchild = -1;
			huffTree[i].rchild = -1;
			huffTree[i].code = "";
		}
		for (i = 0; i < n; i++) {
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
		char temp;
		string str = "";//保存解码后的字符串
		for (unsigned i = 0; i < s.size(); i++) {
			temp = s[i];
			for (int j = 0; j < n; j++) {
				if (temp == huffTree[j].ch) {
					str = str + huffTree[j].code;
					break;
				}
			}
		}
		return str;
	}
	string Huff_Encode(string s) {
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


void start()
{
	// 重定向与文本文件,这里修改读取文件
	freopen("哈夫曼处理数据文件.txt", "r", stdin);
	//编码过程
	int n;
	cin >> n;
	vector<char> s;
	vector<int> w;
	for (int i = 0; i < n; i++) {
		char c;
		int weight;
		cin >> c >> weight;
		s.push_back(c);
		w.push_back(weight);
	}
	cout << "从默认文件中读出的基础数据如下：" << endl;
	for (int i = 0; i < n; i++)
		cout << s[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << w[i] << " ";
	cout << endl << endl;

	// 开始编码
	HuffMan hf(n);
	hf.Huff_Tree(s, w);
	cout << "各个字符编码为：" << endl;
	hf.Huff_Code();
	cout << endl;

	// 开始文件读入字符串
	ifstream in("1.txt");
	string str;
	getline(in, str);
	cout << "从文本文件中读入的字符串为：" << str << endl;
	in.close();

	// 开始编码字符串，然后存入文件
	ofstream out("2.txt");
	str = hf.Huff_Decode(str);
	cout << "下面进行编码。编码结果为：" << str << endl;
	out << str;
	cout << "本结果已经存入文件！！！" << endl << endl;
	out.close();

	// 开始从文件中读入二进制编码进行解码
	in.open("2.txt");
	getline(in, str);
	cout << "下面从文件中读入二进制编码进行解码。" << endl;
	cout << "数据为:" << str << endl;
	str = hf.Huff_Encode(str);
	cout << "解码后为：" << str << endl;
	cout << "解码完毕，和原数据完全一致！！！" << endl << endl;

}

int main()
{
	system("color f0");
	SetConsoleTitle("哈夫曼编码功能展示"); //设置标题
	start();
	system("pause");
	exit(1);
	return 0;
}
//结束