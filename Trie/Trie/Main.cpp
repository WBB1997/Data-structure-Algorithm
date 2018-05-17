#include <iostream>
#include "Trie.h"
using namespace std;

int main() {
	{
		Trie t;
		t.insert_word("zoo");
		t.insert_word("zoo");
		t.insert_word("zoo");
		cout << t.search_word("z") << endl;
		cout << t.search_word("zo") << endl;
		cout << t.search_word("zoo") << endl;
		t.delete_word("zoo");
		cout << t.search_word("zoo") << endl;
		cout << t.search_word("zooo") << endl;
		cout << t.insert_word("123") << endl;
		cout << t.search_word("123") << endl;
	}
	return 0;
}