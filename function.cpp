#include "function.hpp"

// Cong Duc
void Trie::Destruct() {
    Destruct(root);
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
int Trie::iFind(const char *s) {
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
Node* Trie::Find(const char *s) {
    Node *cur = root;
    for (int i=0;i<strlen(s);++i) {
        if (cur->next[s[i]] == NULL)
            return NULL;
        cur = cur->next[s[i]];
    }
    return cur;
}

// Huu Duc
Node* Trie::Find(char c,const char* word,Data *&database,int intitle)
{
    Node *tmp = Find(word);
    details *info = tmp->info;
    if (tmp == NULL) return NULL;
    Node *res = NULL;
    details *res_info;
    char *s = new char [105000];
    vector<int> pos;
    while (info) {
        pos.clear();
        if (intitle) strcpy(s,database[info->file_id].title);
        else strcpy(s,database[info->file_id].content);
        for (vector<int>::iterator i=info->pos.begin();i!=info->pos.end();++i) 
            if (s[*i-1] == c) pos.push_back(*i-1);
        if (pos.size() > 0) {
            if (res == NULL) {
                res = new Node;
                res->info = new details;
                res_info = res->info;
                res_info->file_id = info->file_id;
                res_info->pos = pos;
                res->point = pos.size();
            }
            else {
                res_info->next = new details;
                res_info = res_info->next;
                res_info->file_id = info->file_id;
                res_info->pos = pos;
                res->point += pos.size();
            }
        }
        info = info->next;
    }

    delete []s;
    return res;
}


// Cong Duc
int Query(int flag,Trie T,const char *word,int *rating,int &number_of_file,Data *&database,int intitle) {
    // flag
    // OR - 0
    // AND - 1
    // -united - -oo
    // +and - 2
    // intitle 5
    Node *_find;
    if (word[0] == '"' && word[strlen(word)-1] == '"') {
        string s = "";
        for (int i=1;i<strlen(word)-1;++i)
            s += word[i];
        char *ss = new char [s.length()];
        strcpy(ss,s.c_str());
        _find = KMP(ss,database,number_of_file,(flag == 5));
        delete []ss;
    }
    else 
    if (word[0] == '#' || word[0] == '$') {
        string s = "";
        for (int i=1;i<strlen(word);++i)
            s += word[i];
        if (word[0] == '#') _find = T.Find('#',s.c_str(),database,(flag == 5));
        if (word[0] == '$') _find = T.Find('$',s.c_str(),database,(flag == 5));
    }
    else _find = T.Find(word);
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
    else if (flag == 0 || flag >= 2) {
        for (int i=0;i<number_of_file;++i)
            if (rating[i] >= 0)
                rating[i] += cnt[i];
    }
    else if (flag == 1) {
        for (int i=0;i<number_of_file;++i)
            if (cnt[i] == 0) rating[i] = -oo;
            else if (rating[i] >= 0) rating[i] += cnt[i];
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
    if (Check_all_space(s)) {s = ""; return false;}
    target = "";
    string res;
    int cnt = 0, start = -1, exact = 0; string::iterator st;
    for (string::iterator i=s.begin();i!=s.end();++i,++cnt) {
        if (start == -1 && *i != c) start = cnt, st = i;
        if ((*i == c) && start != -1) { 
            if (exact == 0) {
                target.insert(target.begin(),st,i);
                for (int j=0;j<=cnt;++j)
                    if (s[j] == '"') exact++;
                if (exact == 2) {
                    s.erase(0,cnt+1); 
                    return true;
                }
                if (exact == 1) {
                    c = '"'; res = target + ' '; 
                    continue;
                }
                else {
                    s.erase(0,cnt+1);
                    return true;
                }
            }
            else {
                target = "";
                target.insert(target.begin(),st,i+1);
                s.erase(0,cnt+1);
                return true;
            }
        }
    }
    target = s;
    s = "";
    while (target[0] == c) target.erase(0,1);
    if (exact) {
        res += target;
        target = res+'"';
    }
    return true;
}

void ToLower(string &s) {
    for (int i=0;i<s.length();++i)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i]-'A'+'a';
}   

// Cong Duc
void Sort_by_rating(int *ranking,int *rating,int number_of_file) {
    Partition(ranking,rating,0,number_of_file-1);
}

// Cong Duc
void Partition(int *ranking,int *rating,int L,int H) {
    if (L >= H) return;
    int k = ranking[(L+H)/2];
    int i = L, j = H;
    do {
        while (rating[ranking[i]] > rating[k]) i++;
        while (rating[ranking[j]] < rating[k]) j--;
        if (i <= j) {
            if (i < j)
                swap(ranking[i], ranking[j]);
            i++; j--;
        }
    } 
    while (i <= j);
    Partition(ranking,rating,L,j); Partition(ranking,rating,i,H);
}


void Show(int n,char *s) {
    int Min = (n < strlen(s)) ? n : strlen(s);
    for (int i=0;i<Min;++i)
        cout << s[i];
}

Node* KMP(char *s,Data *&data,int number_of_file,int intitle) {
    for (int j=0;j<strlen(s);++j)
        s[j] = tolower(s[j]);
    string first_token = "";
    for (int j=0;j<strlen(s);++j)
        if (s[j] != ' ') first_token += s[j];
        else break;
    int m = strlen(s), *f = new int [m];
    f[0] = -1;
    for (int i=1,k=-1;i<m;++i) {
        while (k >= 0 && tolower(s[k+1]) != tolower(s[i])) k = f[k];
        if (tolower(s[k+1]) == tolower(s[i])) k++;
        f[i] = k;
    } 
    int *point = new int [number_of_file];
    ZERO(point);
    char *p = new char [105000];
    for (int _=0;_<number_of_file;++_) {
        if (intitle) strcpy(p,data[_].title);
        else strcpy(p,data[_].content);
        int nn = strlen(p);
        for (int i=0,k=-1;i<nn;++i) {
            while (k >= 0 && tolower(s[k+1]) != tolower(p[i])) k = f[k];
            if (tolower(s[k+1]) == tolower(p[i])) k++;
            if (k == m-1) {
                if (!((p[i+1] >= 'a' && p[i+1] <= 'z') ||
                        (p[i+1] >= '0' && p[i+1] <= '9') ||
                        (p[i+1] >= 'A' && p[i+1] <= 'Z') ))
                    point[_]++;
                k = f[k];
            }
        }
    }
    Node *res = new Node;
    res->point = 0;
    details *cur;
    for (int i=0;i<number_of_file;++i) 
        if (point[i] > 0) {
            if (res->info == NULL) {
                res->info = new details;
                res->info->file_id = i;
                for (int j=0;j<point[i];++j)
                    res->info->pos.push_back(1);
                cur = res->info;
            }
            else {
                cur->next = new details;
                cur = cur->next;
                for (int j=0;j<point[i];++j)
                    cur->pos.push_back(1);
                cur->file_id = i;
            }
            res->point += point[i];
        }
    delete []p;
    delete []point;
    return res;
}
