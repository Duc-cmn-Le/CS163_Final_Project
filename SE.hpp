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
    Trie* a;
    Trie* title;
    string* content;
    int n, *exist, *ranking;
    Search_Engine();  
    ~Search_Engine();
    void Indexing();
    void Storing();
    void Search_exact(string &s);
};
