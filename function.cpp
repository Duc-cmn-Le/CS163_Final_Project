#include "function.hpp"

Trie::~Trie() {

}

void Trie::Destruct(details *cur) {
    if (cur == NULL) return;
    Destruct(cur->next);
    delete cur;
}

void Trie::Destruct(Node *cur) {
    if (cur == NULL) return;
    Destruct(cur->info);
    for (int i=0;i<256;++i)
        Destruct(cur->next[i]);
    delete cur;
}

void Trie::Insert(const char* s,int file_id,int pos) {
    Node *cur = root;
    for (int i=0;i<strlen(s);++i) {
        if (cur->next[s[i]] == NULL)
            cur->next[s[i]] = new Node;
        cur = cur->next[s[i]];
    }
    cur->point++;
    if (cur->info == NULL) {
        cur->info = new details;
        cur->info->file_id = file_id;
        cur->info->pos.push_back(pos);
    }
    else {
        details *info_cur = cur->info, *info_prev;
        while (info_cur != NULL && info_cur->file_id != file_id)
            info_prev = info_cur, info_cur = info_cur->next;
        if (info_cur == NULL) {
            info_prev->next = new details;
            info_cur = info_prev->next;   
            info_cur->file_id = file_id;
        }
        info_cur->pos.push_back(pos);
    }
}

Node* Trie::Find(char *s) {
    Node *cur = root;
    for (int i=0;i<strlen(s);++i) {
        if (cur->next[s[i]] == NULL)
            return NULL;
        cur = cur->next[s[i]];
    }
    return cur;
}

void Trie::Show_trie(Node *cur,string s) {
    if (cur->point > 0) {
        details *info_cur = cur->info;
        while (info_cur != NULL) {
            for (vector<int>::iterator i=info_cur->pos.begin();i!=info_cur->pos.end();++i)
                cout << info_cur->file_id << ' ' << s << ' ' << *i << '\n';
            info_cur = info_cur->next;
        }
    }
    for (int i=0;i<256;++i)
        if (cur->next[i] != NULL) Show_trie(cur->next[i],s+(char)i);
}

void Open_file(istream &fin,string &title,string &content) {
    content = "";
    string s;
    getline(fin,title);
    while (getline(fin,s)) {
        content += ' ';
        content += s;
    }
}

void Free_file(char*& title, char*& content) {
    delete []title;
    delete []content;
}

int FILTERING(string file_name) { 
    ifstream fin("CS163-Data/"+file_name);
    ofstream fout("tmpfileout.txt",ofstream::out);
    char c; int res = 0;
    while (fin.get(c)) 
        if (isascii(c)) fout << c;
        else res = 1;
    fin.close();
    fout.close();
    system(("mv tmpfileout.txt CS163-Data/"+file_name).c_str());
    return res;
}
