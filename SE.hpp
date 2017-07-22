#pragma once
#include "trie.hpp"
#include <iostream>
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
    int n;
    Search_Engine();  
    void Indexing();
};
