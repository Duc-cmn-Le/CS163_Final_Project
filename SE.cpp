#include "SE.hpp"

Search_Engine::Search_Engine() {
    n = 0;
    system("ls -F CS163-Data |grep -v / | wc -l > file.tmp");
    ifstream fin("file.tmp");
    fin >> n;
    fin.close();
    system("rm file.tmp");
    a = new Trie[n];
    title = new Trie[n];  
    Indexing();
}

void Search_Engine::Indexing() {
    system("ls CS163-Data > file.tmp");
    ifstream tmp_fin("file.tmp"), fin;
    string s, ss;
    int cnt = 0;
    while (tmp_fin) {
        tmp_fin >> s;
        fin.open("CS163-Data/"+s);
        a[cnt].Input_file(fin);
        fin.close();
        fin.open("CS163-Data/"+s);
        getline(fin,s);
        title[cnt].Extract_word(s);
        fin.close();
        cnt++;
    }
    tmp_fin.close();
    system("rm file.tmp");
}
