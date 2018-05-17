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
	// 递归释放内存
	for (int i = 0; i < 26; i++) {
		if (t->next[i] != nullptr)
			destructor(t->next[i]);
	}
	delete t;
	return;
}

Trie::trie_node* Trie::search_node(string word) {
	// 假设要查找的字符串为word，Trie树的根结点为root，i=0，node=root
	// 取word[i]，判断判断node->next[word[i]-'a']是否为空，若为空，则返回nullptr；若不为空，则node=node->next[word[i]-'a']，继续取字符。
	// 重复1)中的操作直到字符串结束，若当前结点node不为空并且word_num不为0，则返回nullptr;
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
	// 假设存在字符串word，Trie树的根结点为root。i=0，node=root。
	// 取word[i]，判断node->next[word[i]-'a']是否为空，若为空，则申请空间。
	// 若不为空，则node = node->next[wrod[i]-'a']；
	// i++，继续取word[i]，循环1)中的操作，直到遇到字符串结尾，此时将当前结点node中的word_num++。
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


