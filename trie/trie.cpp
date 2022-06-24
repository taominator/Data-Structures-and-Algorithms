#include<iostream>
#include<cstring>	// memset
#include <vector>

class trie {
private:
	static const int MAX_CHAR = 26;
	trie* child[MAX_CHAR];
	bool isLeaf{ };

public:
	trie() {
		// set an array to 0s. Here pointers to null
		memset(child, 0, sizeof(child));
	}

	void insert(std::string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = tolower(str[idx]) - 'a';
			if (child[cur] == 0)
				child[cur] = new trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool word_exist(std::string str, int idx = 0) {
		if (idx == (int)str.size())
			return isLeaf;	// there is a string marked here

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->word_exist(str, idx + 1);
	}

	bool prefix_exist(std::string str, int idx = 0) {
		if (idx == (int)str.size())
			return true;	// all subword covered

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;	// such path don't exist

		return child[cur]->prefix_exist(str, idx + 1);
	}

	void insert_iterative(std::string str) {
		trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = tolower(str[idx]) - 'a';
			if (!cur->child[ch])
				cur->child[ch] = new trie();
			cur = cur->child[ch];
		}
		cur->isLeaf = true;
	}

	bool word_exist_iterative(std::string str) {
		trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = tolower(str[idx]) - 'a';
			if (!cur->child[ch])
				return false;	// such path don't exist
			cur = cur->child[ch];
		}
		return cur->isLeaf;
	}

	std::string first_word_prefix(const std::string& str) {
		trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = tolower(str[idx]) - 'a';
			if (!cur->child[ch])
				break;

			// Does this child marked as word? we forund a prefix that is a word
			if (cur->child[ch]->isLeaf)
				return str.substr(0, idx + 1);
			cur = cur->child[ch];
		}
		return str;
	}

	bool suffix_exist(std::string str) {
		std::reverse(str.begin(), str.end());
		trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = tolower(str[idx]) - 'a';
			if (!cur->child[ch])
				return false;	// such path don't exist
			cur = cur->child[ch];
		}
		return true;
	}

	// O(NL) where N number of words and L is word length.
	void get_all_strings(std::vector<std::string>&res, std::string cur_str = "") {
		if (isLeaf)
			res.push_back(cur_str);

		for (int i = 0; i < MAX_CHAR; ++i)
			if (child[i])
				child[i]->get_all_strings(res, cur_str + (char)(i + 'a'));
	}

	void auto_complete(const std::string& str, std::vector<std::string>& res) {
		trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = tolower(str[idx]) - 'a';
			if (!cur->child[ch])
				return;
			cur = cur->child[ch];
		}
		cur->get_all_strings(res, str);
	}

	bool word_exist_with_1_change(std::string str) {
		// Brute force all possible 1-char change and search for it
		// O(L * 26 * L)
		for (int i = 0; i < (int)str.size(); ++i) {
			char cpy = str[i];
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch == cpy)	// Must do a change
					continue;
				str[i] = ch;
				if (word_exist(str))
					return true;
			}
			str[i] = cpy;	// copy back
		}
		return false;
	}

};

int main() {
	trie root;

	root.insert("abcd");
	root.insert("xyz");
	root.insert("abf");
	root.insert("xn");
	root.insert("ab");
	root.insert("bcd");

	std::cout << root.word_exist("xyz") << "\n";
	std::cout << root.word_exist("xy") << "\n";
	std::cout << root.prefix_exist("xy") << "\n";

	return 0;
}
