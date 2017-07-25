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
    header = new string [n];
    for (int i=0;i<n;++i) 
        ranking[i] = i;
    Indexing();
    Storing();
}

// Cong Duc
Search_Engine::~Search_Engine() {
    delete []a;
    delete []title;
    delete []content;
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
    int cnt = 0;
    for (int i=0;i<n;++i) {
        tmp_fin >> header[i];
        fin.open("CS163-Data/"+header[i]);
        a[cnt].Input_file(fin);
        fin.close();
        // In title
        fin.open("CS163-Data/"+header[i]);
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
        fin.open("CS163-Data/"+header[i]);
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
    for (string::iterator i=s.begin();i!=s.end();++i)
        *i = tolower(*i);
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
        while (k >= 0 && tolower(s[k+1]) != tolower(s[i])) k = f[k];
        if (tolower(s[k+1]) == tolower(s[i])) k++;
        f[i] = k;
    }
    for (int _=0;_<n;++_)
        if (exist[_] > 0) {
            exist[_] = 0;
            int nn = content[_].length();
            for (int i=0,k=-1;i<nn;++i) {
                while (k >= 0 && tolower(s[k+1]) != tolower(content[_][i])) k = f[k];
                if (tolower(s[k+1]) == tolower(content[_][i])) k++;
                if (k == m-1) {
                    if (!((content[_][i+1] >= 'a' && content[_][i+1] <= 'z') ||
                        (content[_][i+1] >= '0' && content[_][i+1] <= '9') ||
                        (content[_][i+1] >= 'A' && content[_][i+1] <= 'Z')))
                        exist[_]++; 
//                    printf("%d ",i-k+1);
                    k = f[k];
                }
            }

        }
    delete [] f;
//    bool (Search_Engine::*func)(int,int);
//    func = &Search_Engine::Compare_existence;
//    sort(ranking,ranking+n,*func);
//    sort(ranking,ranking+n,Compare_existence);
    Sort_by_existence();

    int count = 0;
    cout << "\033[1;32m\"" << s << "\"\033[0m"  << " appears in:\n";
    for (int i=0;i<n;++i)
        if (exist[ranking[i]] > 0) {
            cout << header[ranking[i]]<< ' ' << exist[ranking[i]] << " time" << (exist[ranking[i]] > 1 ? 's' : ' ') << '\n';
            count++;
        }
        else break;
    if (count == 0) cout << "Not found\n";
} 

// Cong Duc
void Search_Engine::Search_normal(string &s) {
    string ss = s;
    for (string::iterator i=s.begin();i!=s.end();++i)
        *i = tolower(*i);
    // 
    for (int i=0;i<n;++i) ranking[i] = 0, exist[i] = 0; 
    string cur;
    Next_token(s,cur);
    for (int i=0;i<n;++i) {
        exist[i] = a[i].Search(cur);
        if (exist[i] > 0) ranking[i] = 1;
    }
    int cnt_and = 0, t;
    while (Next_token(s,cur)) {
        if (cur == "and" || cur == "or") {
            if (cur == "and") {
                cnt_and++;
                while (Next_token(s,cur)) {
                    if (cur != "and" && cur != "or") // not stopword
                    {
                        for (int i=0;i<n;++i) {
                            t = a[i].Search(cur);
                            if (t == 0) ranking[i] = 0;
                            else ranking[i]++, exist[i] += t;
                        }
                        break;
                    }
                }
            }
            else {
                while (Next_token(s,cur)) {
                    if (cur != "and" && cur != "or") {
                        for (int i=0;i<n;++i) {
                            t = a[i].Search(cur);
                            if (t != 0) ranking[i]++, exist[i] += t;
                        }
                        break;
                    }
                }
            }
        }
        else if (cur[0] == '-') {
            cur.erase(cur.begin());
            for (int i=0;i<n;++i)
                if (a[i].Search(cur))
                    exist[i] = -123456789;
        }
        else 
            for (int i=0;i<n;++i)
                exist[i] += a[i].Search(cur); 
    }
    for (int i=0;i<n;++i)
        if (ranking[i] < cnt_and+1) ranking[i] = 0;
    for (int i=0;i<n;++i)
        if (ranking[i] == 0 || exist[i]+ranking[i] < 0) exist[i] = 0;
    for (int i=0;i<n;++i) ranking[i] = i;
    Sort_by_existence();

    int count = 0;
    cout << "\033[1;32m" << ss << "\033[0m" << '\n'; 
    for (int i=0;i<n;++i)
        if (exist[ranking[i]] > 0) {
            cout << header[ranking[i]] << ' ' << exist[ranking[i]] << " time" << (exist[ranking[i]] > 1 ? 's' : ' ') << '\n';
            count++;
        }
        else break;
    if (count == 0) cout << "Not found\n";
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

