#include "trie.hpp"

Node::Node() {
    point = 0;
    for (int i=0;i<40;++i)
        p[i] = NULL;
}

// Trie = = = = = = = = = = = =
Trie::Trie() {
    root = new Node;
}

Trie::~Trie() {
    Destruct(root);
}

// Cong Duc
void Trie::Destruct(Node* cur) {
    if (cur == NULL) return;
    for (int i=0;i<40;++i)
        if (cur->p[i] != NULL) Destruct(cur->p[i]);
    delete cur;
}

// Huu Duc
void Trie::Insert(string &s) {
    Node *cur = root;
    int tmp;
    for (string::iterator i=s.begin();i!=s.end();++i)
    {
            if (*i >= 'a' && *i <= 'z') tmp = *i - 'a' + 10;
            else if (*i >= 'A' && *i <= 'Z') tmp = *i - 'A' + 10;
            else if (*i >= '0' && *i <= '9') tmp = *i - '0';
            else if (*i >= '\'') tmp = 36;
            else if (*i >= '.') tmp = 37;
            else if (*i >= '%') tmp = 38;
            else if (*i >= '@') tmp = 39;
            if (cur->p[tmp] == NULL)
                    cur->p[tmp] = new Node;
            cur = cur->p[tmp];
    }
    cur->point++;
}   

// Huu Duc
int Trie::Search(string &s) {
    Node *cur = root;
    int tmp;
    for (string::iterator i=s.begin();i!=s.end();++i)
    {
            if (*i >= 'a' && *i <= 'z') tmp = *i - 'a' + 10;
            else if (*i >= 'A' && *i <= 'Z') tmp = *i - 'A' + 10;
            else if (*i >= '0' && *i <= '9') tmp = *i - '0';
            else if (*i >= '\'') tmp = 36;
            else if (*i >= '.') tmp = 37;
            else if (*i >= '%') tmp = 38;
            else if (*i >= '@') tmp = 39;
            if (cur->p[tmp] == NULL) return 0;
            cur = cur->p[tmp];
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

