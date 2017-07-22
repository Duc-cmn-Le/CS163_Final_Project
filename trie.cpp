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
    Node *cur = root;
    for (string::iterator i=s.begin();i!=s.end();++i) {
        int c;
        if (*i >= '0' && *i <= '9') c = 26+*i-'0';
        if (*i >= 'a' && *i <= 'z') c = *i-'a';
        if (*i >= 'A' && *i <= 'Z') c = *i-'A';
    }   
    cur->point++;
}   

int Search(string &s) {

}

// Giao cho Gia Bao
void Input_file(istream &fin) {
    
}

