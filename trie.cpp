#include "trie.hpp"

Node::Node() {
    point = 0;
    for (int i=0;i<40;++i)
        p[i] = NULL;
}

// Trie = = = = = = = = = = = =
Trie::Trie() {
    root = new Node;
    max_c = 40;
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
void Trie::Insert(string &s) {
    Node *cur = root;
    int tmp;
    for (string::iterator i=s.begin();i!=s.end();++i)
    {
            if (*i >= 'a' && *i <= 'z') tmp = *i - 'a' + 10;
            else if (*i >= 'A' && *i <= 'Z') tmp = *i - 'A' + 10;
            else if (*i >= '0' && *i <= '9') tmp = *i - '0';
            else if (*i >= '\'') tmp = 36;
            else if (*i >= '-') tmp = 37;
            else if (*i >= '%') tmp = 38;
            else if (*i >= '@') tmp = 39;
            else continue;
            if (cur->p[tmp] == NULL)
                    cur->p[tmp] = new Node;
            cur = cur->p[tmp];
    }
    cur->point++;
}   

// Cong Duc
void Trie::Show_trie(Node* cur,string s) {
    if (cur->point > 0)
        for (int i=0;i<cur->point;++i)
            cout << s << ' ';
    for (int i=0;i<10;++i)
        if (cur->p[i] != NULL) Show_trie(cur->p[i],s+(char)(i+'0'));
    for (int i=10;i<36;++i)
        if (cur->p[i] != NULL) 
            Show_trie(cur->p[i],s+(char)(i+'a'-10));
    if (cur->p[36] != NULL)
        Show_trie(cur->p[36],s+'\'');
    if (cur->p[37] != NULL)
        Show_trie(cur->p[37],s+'-');
}

void Trie::Show_trie() {
    Show_trie(root,"");
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
            else if (*i >= '-') tmp = 37;
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

// Gia Bao
void Trie::Input_file(istream &fin) {
    string s;
    while (getline(fin,s))
        Extract_word(s);
}

