#include <iostream>
#include <queue>
#include <string>
using namespace std;
// Trie���ڵ�
struct node {
	int cnt; //����ڵ�ĵ�����
	node* next[26]; // �ӽڵ�����
	node* fail;     // ʧ��ָ��
	node() {
		cnt = 0;
		fail = NULL;
		memset(next, NULL, sizeof(next));
	}
};
node* root = new node;

// ��ͨ�Ĳ���
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

// failָ���ʼ�����ù�����ȱ���(BFS)
void build() {
	root->fail = NULL;
	queue<node*> q;
	q.push(root);
	while (!q.empty()) {
		// ��ǰָ��
		node* cur = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			//�ҵ�ʵ�ʴ��ڵ��ַ���� 
			if (cur->next[i] != NULL) {
				// �����ǰ���Ϊroot��㣬���⻯����
				if (cur == root)
					cur->next[i]->fail = root;
				// �����Ϊroot���
				else {
					// �����ҵ�һ��ǰ׺���ڶ���ǰ׺...ֱ���ﵽroot
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
	// ��kmp����
	node* cur = root;
	int position;
	int count = 0;
	for (unsigned i = 0; i < text.length(); i++) {
		position = text[i] - 'a';
		// �ҵ���һ��ƥ���
		while (cur->next[position] == NULL && cur != root)
			cur = cur->fail;
		cur = cur->next[position];
		if (cur == NULL)
			cur = root;
		node* temp = cur;
		// ����ǰ�Ӵ������к�׺ȫ������һ�飬ֱ��root
		while (temp != root) {
			// �����ֻ��Ҫ�鿴ģʽ�����ֵ����࣬���Լ�һ����ǣ�����ٴη��ʵ�����Բ�����
			// һ������¾Ͳ���Ҫ�Ķ���ͳ�Ƶ���ģʽ�����ֵĸ���
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