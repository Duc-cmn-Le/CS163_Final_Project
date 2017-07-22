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

void Trie::Insert(string &s) {

}   

int Trie::Search(string &s) {

    return 0;
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

