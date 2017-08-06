#include "SE.hpp"

// Cong Duc
Search_Engine::Search_Engine() {
    n = 0;
    system("ls -F CS163-Data |grep -v / | wc -l > file.tmp");
    ifstream fin("file.tmp");
    fin >> n;
    fin.close();
    system("rm file.tmp");
    a = new Trie[n];
    title = new Trie[n];  
    exist = new int [n];
    ranking = new int [n];
    header = new string[n];
    for (int i=0;i<n;++i) 
        ranking[i] = i;
    Indexing();
}

// Cong Duc
Search_Engine::~Search_Engine() {
    delete []a;
    delete []title;
    delete []exist;
    delete []ranking;
    delete []header;
}

// Cong Duc
bool Search_Engine::Compare_existence(int i,int j) {
    return exist[i] > exist[j];
}

// Cong Duc
void Search_Engine::Indexing() {
    system("ls CS163-Data > file.tmp");
    ifstream tmp_fin("file.tmp"), fin;
    string s, ss;
    for (int i=0;i<n;++i) {
        tmp_fin >> header[i];
        fin.open("CS163-Data/"+header[i]);
        a[i].Input_file(fin,i);
        fin.close();
        // In title
        fin.open("CS163-Data/"+header[i]);
        getline(fin,ss);
        title[i].Extract_word(ss,i);
        fin.close();
    }
    tmp_fin.close();
    system("rm file.tmp");
}

// Cong Duc
void Search_Engine::Sort_by_existence() {
    Partition(0,n-1);
}

// Cong Duc
void Search_Engine::Partition(int L,int H) {
    if (L >= H) return;
    int k = ranking[(L+H)/2];
    int i = L, j = H;
    do {
        while (exist[ranking[i]] > exist[k]) i++;
        while (exist[ranking[j]] < exist[k]) j--;
        if (i <= j) {
            if (i < j)
                swap(ranking[i], ranking[j]);
            i++; j--;
        }
    } 
    while (i <= j);
    Partition(L,j); Partition(i,H);
}

int Search_Engine::Next_token(string &s,string &target,char c){
    if (s.length() == 0) return false;
    target = "";
    int ok = 0, cnt = 0;
    for (string::iterator i=s.begin();i!=s.end();++i,++cnt) {
        if (*i == c) {
            target.insert(target.begin(),s.begin(),i);
            s.erase(0,cnt+1);
            return true;
        }
        /*
        if (*i != c) 
            target += *i, ok = 1;
        else if (ok) return true;
        s.erase(i);
        */
    }
//    return s.length() > 0;
    target = s;
    s = "";
    return true;
}
