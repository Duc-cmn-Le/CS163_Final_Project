#include "trie.hpp"

Node::Node() {
    point = 0;
    for (int i=0;i<40;++i)
        p[i] = NULL;
}

// Trie = = = = = = = =  = = = =
Trie::Trie() {
    root = new Node;
}

Trie::~Trie() {
    Destruct(root);
}

void Trie::Destruct(Node* cur) {
    if (cur == NULL) return;
    for (int i=0;i<40;++i)
        if (cur->p[i] != NULL) Destruct(cur->p[i]);
    delete cur;
}
// Huu Duc
void Trie::Insert(string &s/*,bool intitle*/) {
    Node *cur = root;
	for (auto i : encodeKeyWord(s))
	{
		if (cur->p[*i] == NULL)
			cur->p[*i] = new Node;
		cur = cur->p[*i];
	}
	/*if (intitle == true) cur->intitle = true;*/
    cur->point++;
}   
// Huu Duc
vector<int> Trie::encodeKeyWord(string key) 
{
	vector<int> result;
	for (string::iterator i = key.begin();i < key.end();i++)
	{
		if (*i >= 97 && *i <= 122) result.push_back(*i - 87);
		else if (*i >= 65 && *i <= 90) result.push_back(*i - 55);
		else if (*i >= 48 && *i <= 57) result.push_back(*i - '0');
		else if (*i == '\'') result.push_back(36);
		else if (*i == '.') result.push_back(37);
		else if (*i == '%') result.push_back(38);
		else if (*i == '@') result.push_back(39);
	}
	return result;
}
// Huu Duc
int Trie::Search(string &s) {
	Node *cur = root;
	for (auto i : encodeKeyWord(s))
	{
		if (cur->p[*i] == NULL) break;
		cur = cur->p[*i];
	}
	return cur->point; 
}

// Gia Bao
void Trie::Extract_word(string &s)
{
    string tmp;
    for(string::iterator i=s.begin();i!=s.end();i++)
    if (*i!=' ')
    {
        tmp=tolower(*i);
        while (i!=s.end()-1)
        if (*(++i)!=' ') tmp+=tolower(*i);
        else break;
        Insert(tmp);
    }
}

// Gia Bao
void Trie::Input_file(istream &fin) {
    string s;
    while (getline(fin,s))
        Extract_word(s);
}

