#include <iostream>
#include <queue>
#include <string>
using namespace std;
// Trie树节点
struct node {
	int cnt; //这个节点的单词数
	node* next[26]; // 子节点数组
	node* fail;     // 失配指针
	node() {
		cnt = 0;
		fail = NULL;
		memset(next, NULL, sizeof(next));
	}
};
node* root = new node;

// 普通的插入
void insert(string str) {
	node* p = root;
	for (unsigned i = 0; i < str.length(); i++) {
		int now = str[i] - 'a';
		if (p->next[now] == NULL)
			p->next[now] = new node;
		p = p->next[now];
	}
	p->cnt++;
}

// fail指针初始化，用广度优先遍历(BFS)
void build() {
	root->fail = NULL;
	queue<node*> q;
	q.push(root);
	while (!q.empty()) {
		// 当前指针
		node* cur = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			//找到实际存在的字符结点 
			if (cur->next[i] != NULL) {
				// 如果当前结点为root结点，特殊化处理
				if (cur == root)
					cur->next[i]->fail = root;
				// 如果不为root结点
				else {
					// 依次找第一长前缀，第二长前缀...直到达到root
					node* p = cur->fail;
					while (p != NULL) {
						if (p->next[i] != NULL) {
							cur->next[i]->fail = p->next[i];
							break;
						}
						else
							p = p->fail;
					}
					if (p == NULL)
						cur->next[i]->fail = root;
				}
				q.push(cur->next[i]);
			}
		}
	}
}

int query(string text){
	// 与kmp类似
	node* cur = root;
	int position;
	int count = 0;
	for (unsigned i = 0; i < text.length(); i++) {
		position = text[i] - 'a';
		// 找到第一个匹配的
		while (cur->next[position] == NULL && cur != root)
			cur = cur->fail;
		cur = cur->next[position];
		if (cur == NULL)
			cur = root;
		node* temp = cur;
		// 将当前子串的所有后缀全部遍历一遍，直到root
		while (temp != root) {
			// 如果是只需要查看模式串出现的种类，可以加一个标记，如果再次访问到则可以不计算
			// 一般情况下就不需要改动，统计的是模式串出现的个数
			count += temp->cnt;
			temp = temp->fail;
		}
	}
	return count;
}

int main() {
	insert("she");
	insert("he");
	insert("say");
	insert("shr");
	insert("her");
	build();
	cout << query("yasherhes");
}