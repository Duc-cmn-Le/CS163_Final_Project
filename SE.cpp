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
    content = new string[n];
    exist = new int [n];
    ranking = new int [n];
    for (int i=0;i<n;++i) 
        ranking[i] = i;
    Indexing();
    Storing();
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
    int cnt = 0;
    for (int i=0;i<n;++i) {
        tmp_fin >> s;
        fin.open("CS163-Data/"+s);
        a[cnt].Input_file(fin);
        fin.close();
        // In title
        fin.open("CS163-Data/"+s);
        getline(fin,ss);
        title[cnt].Extract_word(ss);
        fin.close();
        cnt++;
    }
    tmp_fin.close();
    system("rm file.tmp");
}

// Cong Duc
void Search_Engine::Storing() {
    system("ls CS163-Data > file.tmp");
    ifstream tmp_fin("file.tmp"), fin;
    string s, ss;
    for (int i=0;i<n;++i) {
        tmp_fin >> s;
        fin.open("CS163-Data/"+s);
        content[i] = "";
        while (getline(fin,ss)) {
            content[i] += ss;
        }
        fin.close();
    }
    tmp_fin.close();
    system("rm file.tmp");
}

// Cong Duc
void Search_Engine::Search_exact(string &s) {
    // Get the first token
    string first_token = "";
    for (string::iterator i=s.begin();i!=s.end();++i)
        if ((*i>='0'&&*i<='9')||(*i>='a'&&*i<='z')) {
            first_token += *i;
        }
        else break;
    //
    for (int i=0;i<n;++i) 
        exist[i] = a[i].Search(first_token); 
    // KMP
    int m = s.length(), *f = new int [m];
    f[0] = -1;
    for (int i=1,k=-1;i<m;++i) {
        while (k >= 0 && s[k+1] != s[i]) k = f[k];
        if (s[k+1] == s[i]) k++;
        f[i] = k;
    }
    for (int _=0;_<n;++_)
        if (exist[_] > 0) {
            exist[_] = 0;
            int n = content[_].length();
            for (int i=0,k=-1;i<n;++i) {
                while (k >= 0 && s[k+1] != content[i][i]) k = f[k];
                if (s[k+1] == content[i][i]) k++;
                if (k == m-1) {
                    exist[_]++; 
//                    printf("%d ",i-k+1);
                    k = f[k];
                }
            }
        }
//    bool (Search_Engine::*func)(int,int);
//    func = &Search_Engine::Compare_existence;
//    sort(ranking,ranking+n,*func);
    sort(ranking,ranking+n,Compare_existence);
}
