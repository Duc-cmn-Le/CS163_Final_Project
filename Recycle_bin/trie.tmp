#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Node{
public:
    int point;
    Node* p[256];
    Node() {
        point = 0;
        for (int i=1;i<256;++i)
            p[0] = NULL;
    }
};

class Trie{
private:
    void Destruct(Node*);
public:
    Node* root; 
    Trie();
    ~Trie();
    void Insert(string &);
    void Show_trie(Node*,string);
    int Search(string &);
    void Extract_word(string);
    void Input_file(const string file_name);
};

// Constructor
Trie::Trie() {
    root = new Node;
}   

// Destructor
Trie::~Trie() {
    Destruct(root);
    root = NULL;
}

void Trie::Destruct(Node *cur) {
    for (int i=0;i<256;++i)
        if (cur->p[i] != NULL) Destruct(cur->p[i]);
    delete cur;
}

// Insert a string to trie
void Trie::Insert(string &s) {
    Node *cur = root;
    for (string::iterator i=s.begin();i!=s.end();++i) {
        if (cur->p[*i] == NULL)
            cur->p[*i] = new Node;
        cur = cur->p[*i];
    }
    cur->point++;
}

// Show all strings in trie
void Trie::Show_trie(Node* cur,string s) {
    if (cur->point > 0)
        for (int i=0;i<cur->point;++i)
            cout << s << '\n';
    for (int i=0;i<256;++i)
        if (cur->p[i] != 0)
            Show_trie(cur->p[i],s+(char)i);
}

// Return true if a string is found in trie
int Trie::Search(string &s) {
    Node *cur = root;
    for (string::iterator i=s.begin();i!=s.end();++i) {
        if (cur->p[*i] == NULL) return false;
        cur = cur->p[*i];
    }
    return true;
}

int main() {
    /*
    string s;
    Trie T;
    int n;
    cin >> n;
    for (int i=0;i<n;++i)
    {
        cin >> s;
        T.Insert(s);
    }
    s = "";
    T.Show_trie(T.root,s);
    cin >> s;
    cout << T.Search(s) << '\n';
    cin >> s;
    cout << T.Search(s) << '\n';
    */
    cout << "\033[33m" << "bold red text\033[0m\n";
    return 0;
}
