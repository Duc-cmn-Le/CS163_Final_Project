#include"function.h"

Trie *TRIE; // a linked list of tries (1 txt/ 1 tree)
Trie stopword;

Node::Node()
{
	point = 0;
	inTitle = false;
	for (int i = 0;i<40;i++)
		p[i] = NULL;
};
Trie::Trie() {
	root = new Node;
}
// Destructor
Trie::~Trie() {
	Destruct(root);
	root = NULL;
}
void Trie::Destruct(Node *cur) {
	for (int i = 0;i<40;++i)
		if (cur->p[i] != NULL) Destruct(cur->p[i]);
	delete cur;
}
vector<string> names; // contain name of files txt we have
// Insert a string to trie
void Trie::InsertTitle(string &s) {
	Node *cur = root;
	for (string::iterator i = s.begin();i != s.end();++i) {
		if (cur->p[*i] == NULL)
			cur->p[*i] = new Node;
		cur = cur->p[*i];
	}
	cur->point++;
	cur->inTitle = true;
}
void Trie::InsertContent(string &s) {
	Node *cur = root;
	for (string::iterator i = s.begin();i != s.end();++i) {
		if (cur->p[*i] == NULL)
			cur->p[*i] = new Node;
		cur = cur->p[*i];
	}
	cur->point++;
}
// Return a Node-address if a string is found in trie,NULL is not
Node* Trie::Search(string &s) {
	Node *cur = root;
	for (string::iterator i = s.begin();i != s.end();++i) {
		if (cur->p[*i] == NULL) return NULL;
		cur = cur->p[*i];
	}
	return cur;
}
void getFilenameList(string folder)
{
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}
void Trie::iniStopwordsTRIE()
{
	ifstream fin;
	string tmp;
	fin.open("stopword.txt");
	while (fin.good())
	{
		fin >> tmp;
		InsertContent(tmp);
	}
	fin.close();
}