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
public:
    Trie* a;
    Trie* title;
    string* content;
    int n;
    Search_Engine();  
    void Indexing();
    void Storing();
};
