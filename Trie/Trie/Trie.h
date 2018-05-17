#ifndef TRIE_H
#define TRIE_H
using std::string;

class Trie {
private:
	struct trie_node
	{
		int pre_num;
		trie_node* next[26];
		int word_num;
	};
	trie_node* root;
	trie_node* createTrieNode();
	void destructor(trie_node* t);
	trie_node* search_node(string word);
public:
	Trie();
	~Trie();
	Trie(const Trie& t);
	void operator=(const Trie& t);
	bool insert_word(string word);
	int search_word(string word);
	void delete_word(string word);
	bool insert_word(char* word) {
		return this->insert_word(string(word));
	}
	int search_word(char* word) {
		return this->search_word(string(word));
	}
	void delete_word(char* word) {
		delete_word(string(word));
	}
};

Trie::Trie() {
	this->root = new trie_node;
	root->pre_num = 0;
	root->word_num = 0;
	memset(root->next, 0, sizeof(root->next));
}

Trie::Trie(const Trie& t) {
	this->root = t.root;
}

void Trie::destructor(Trie::trie_node* t) {
	// �ݹ��ͷ��ڴ�
	for (int i = 0; i < 26; i++) {
		if (t->next[i] != nullptr)
			destructor(t->next[i]);
	}
	delete t;
	return;
}

Trie::trie_node* Trie::search_node(string word) {
	// ����Ҫ���ҵ��ַ���Ϊword��Trie���ĸ����Ϊroot��i=0��node=root
	// ȡword[i]���ж��ж�node->next[word[i]-'a']�Ƿ�Ϊ�գ���Ϊ�գ��򷵻�nullptr������Ϊ�գ���node=node->next[word[i]-'a']������ȡ�ַ���
	// �ظ�1)�еĲ���ֱ���ַ�������������ǰ���node��Ϊ�ղ���word_num��Ϊ0���򷵻�nullptr;
	trie_node* node = this->root;
	int cur_id;
	for (unsigned i = 0; i < word.length(); i++) {
		cur_id = word[i] - 'a';
		node = node->next[cur_id];
		if (node == nullptr)
			return nullptr;
	}
	return node;
}

Trie::~Trie() {
	destructor(this->root);
	root = nullptr;
}

Trie::trie_node* Trie::createTrieNode() {
	trie_node *node = new trie_node;
	node->pre_num = 0;
	node->word_num = 0;
	memset(node->next, 0, sizeof(node->next));
	return node;
}

void Trie::operator=(const Trie& t) {
	this->root = t.root;
}

void Trie::delete_word(string word) {
	if (search_node(word) != nullptr) {
		trie_node* node = this->root;
		int cur;
		for (unsigned i = 0; i < word.length(); i++) {
			cur = word[i] - 'a';
			node = node->next[cur];
			node->pre_num--;
		}
		node->word_num--;
	}
}

bool Trie::insert_word(string word) {
	// ��������ַ���word��Trie���ĸ����Ϊroot��i=0��node=root��
	// ȡword[i]���ж�node->next[word[i]-'a']�Ƿ�Ϊ�գ���Ϊ�գ�������ռ䡣
	// ����Ϊ�գ���node = node->next[wrod[i]-'a']��
	// i++������ȡword[i]��ѭ��1)�еĲ�����ֱ�������ַ�����β����ʱ����ǰ���node�е�word_num++��
	trie_node* node = this->root;
	int cur_id;
	for (unsigned i = 0; i < word.length(); i++) {
		cur_id = word[i] - 'a';
		if (cur_id < 0 || cur_id > 25)
			return false;
		if (node->next[cur_id] == NULL)
			node->next[cur_id] = createTrieNode();
		node = node->next[cur_id];
		node->pre_num++;
	}
	node->word_num++;
	return true;
}

int Trie::search_word(string word) {
	trie_node* node = search_node(word);
	if (node == nullptr)
		return 0;
	else
		return node->word_num;
}
#endif // !TRIE_H


