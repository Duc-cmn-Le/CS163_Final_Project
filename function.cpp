#include "function.hpp"

Trie::~Trie() {

}

// Cong Duc
void Trie::Destruct(details *cur) {
    if (cur == NULL) return;
    Destruct(cur->next);
    delete cur;
}

// Cong Duc
void Trie::Destruct(Node *cur) {
    if (cur == NULL) return;
    Destruct(cur->info);
    for (int i=0;i<256;++i)
        Destruct(cur->next[i]);
    delete cur;
}

// Cong Duc
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

// Cong Duc
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

// Cong Duc
int Trie::iFind(char *s) {
    Node *cur = root;
    for (int i=0;i<strlen(s);++i) {
        if (cur->next[s[i]] == NULL)
            return false;
        cur = cur->next[s[i]];
    }
    return cur->point > 0;
}

// Cong Duc
Node* Trie::Find(char *s) {
    Node *cur = root;
    for (int i=0;i<strlen(s);++i) {
        if (cur->next[s[i]] == NULL)
            return NULL;
        cur = cur->next[s[i]];
    }
    return cur;
}

// Cong Duc
int Query(int flag,Trie T,char *word,int *rating,int &number_of_file) {
    // flag
    // OR - 0
    // AND - 1
    // -united - -oo
    // +and - 2
    // 
    Node *_find = T.Find(word);
    if (flag == -oo && _find->point == 0) return true;
    int *cnt = new int [number_of_file];
    ZERO(cnt);
    if (_find != NULL && _find->point > 0) {
        details *info = _find->info;
        while (info != NULL) {
            cnt[info->file_id] += info->pos.size();
            info = info->next;
        }
    }
    if (flag == -oo) { 
        for (int i=0;i<number_of_file;++i)
            if (cnt[i] > 0) rating[i] -= oo;
    }
    else if (flag == 0 || flag == 2) {
        for (int i=0;i<number_of_file;++i)
            if (rating[i] > 0) rating[i] += cnt[i];
    }
    else if (flag == 1) {
        for (int i=0;i<number_of_file;++i)
            if (cnt[i] == 0) rating = 0;
            else if (rating[i] > 0) rating[i] += cnt[i];
    }
    delete []cnt;
    return 0;
}

// Cong Duc
void Open_file(istream &fin,string &title,string &content) {
    content = "";
    string s;
    getline(fin,title);
    while (getline(fin,s)) {
        content += ' ';
        content += s;
    }
}


// Cong Duc
void Free_file(char*& title, char*& content) {
    delete []title;
    delete []content;
}

// Cong Duc
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

int Check_all_space(string &s) {
    for (string::iterator i=s.begin();i!=s.end();++i)
        if (*i != ' ' && *i != '\n') return false;
    return true;
}


// Cong Duc
int Next_token(string &s,string &target,char c) {
    if (s.length() == 0) return false;
    target = "";
    int cnt = 0;
    for (string::iterator i=s.begin();i!=s.end();++i,++cnt) {
        if (*i == c) {
            target.insert(target.begin(),s.begin(),i);
            s.erase(0,cnt+1);
            return true;
        }
    }
    target = s;
    s = "";
    return true;
}
