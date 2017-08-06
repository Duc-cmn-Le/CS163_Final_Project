#include "trie.hpp"

Node::Node() {
    for (int i=0;i<max_p;++i)
        point[i] = 0;
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
    for (int i=0;i<max_c;++i)
        if (cur->p[i] != NULL) Destruct(cur->p[i]);
    delete cur;
}

// Huu Duc
void Trie::Insert(string &s,int file_id) {
    Node *cur = root;
    int tmp;
    for (string::iterator i=s.begin();i!=s.end();++i)
    {
            tmp = *i;
            if (cur->p[tmp] == NULL)
                    cur->p[tmp] = new Node;
            cur = cur->p[tmp];
    }
    cur->point[file_id]++;
}   

// Cong Duc
void Trie::Show_trie(Node *cur,string s,int file_id) {
    if (cur->point[file_id] > 0)
        for (int i=0;i<cur->point[file_id];++i)
            cout << s << ' ';
    for (int i=0;i<max_c;++i)
        if (cur->p[i] != NULL) Show_trie(cur->p[i],s+(char)i,file_id);
}

// Cong Duc
/*
void Trie::Show_trie() {

}
*/

// Huu Duc
int Trie::Search(string &s,int file_id) {
    Node *cur = root;
    int tmp;
    for (string::iterator i=s.begin();i!=s.end();++i) {
        tmp = *i;
        if (cur->p[tmp] == NULL) return 0;
        cur = cur->p[tmp];
    }
    return cur->point[file_id];
}

// Gia Bao

void Trie::Extract_word(string &s,int file_id)
{
    string tmp;
    for(string::iterator i=s.begin();i!=s.end();i++)
    if (*i!=' ' && *i != ':' && *i != '.' && *i != '?' && *i != ';' && *i != '!' && *i != ',' && *i != '\'')
    {
        tmp=tolower(*i);
        while (i!=s.end()-1)
        if (*(++i)!=' ' && *(i)!=':' &&  *(i)!='.' && *(i)!='?' && *(i)!=';' && *(i)!='!' && *i != ',')
            tmp+=tolower(*i);
        else break;
        Insert(tmp,file_id);
        if (*(tmp.end()-1)=='\'')
        {
            tmp.erase(tmp.end()-1);
            Insert(tmp,file_id);
        }
    }
}
/*
void Trie::Extract_word(string &s)
{
    string tmp;
    for(string::iterator i=s.begin();i!=s.end();i++)
    if (*i!=' ' && *i != ':' && *i != '.' && *i != '?' && *i != ';' && *i != '!' && *i != ',')
    {
        tmp=tolower(*i);
        while (i!=s.end()-1) 
        if (*(++i)!=' ' && *(i)!=':' &&  *(i)!='.' && *(i)!='?' && *(i)!=';' && *(i)!='!' && *i != ',') 
            tmp+=tolower(*i);
        else break;
        Insert(tmp);
    }
}
*/

// Gia Bao
void Trie::Input_file(istream &fin,int file_id) {
    string s;
    while (getline(fin,s)) 
        Extract_word(s,file_id);
}


