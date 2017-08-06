#pragma once
#include "trie.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <string>

using namespace std;

class Search_Engine{
protected:
    bool Compare_existence(int,int);
    void Sort_by_existence();
    void Partition(int L,int H);
public:
    int Next_token(string &s,string &target,char c=' ');
//public:
    Trie* a;
    Trie* title;
    int n, *exist, *ranking;
    string *header;
    Search_Engine();  
    ~Search_Engine();
    void Indexing();
    void Search_exact(string &s);
    void Search_normal(string &s);
};
