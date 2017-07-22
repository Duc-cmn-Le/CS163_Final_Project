#include "SE.hpp"

Search_Engine::Search_Engine() {
    n = 0;
    system("ls -F CS163-Data |grep -v / | wc -l > file.tmp");
    ifstream fin("file.tmp");
    fin >> n;
    fin.close();
    system("rm file.tmp");
    a = new Trie[n];
}

void Search_Engine::Indexing() {
    
}
