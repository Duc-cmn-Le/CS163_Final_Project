#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <string>

using namespace std;

class Node{
public:
   int point;
   Node* p[40];
   Node();
};

class Trie{
private:
    void Destruct(Node* );
public:
    Node* root;
    int max_c;
    Trie();
    ~Trie();
    void Insert(string &);
    void Show_trie(Node*,string);
    void Show_trie();
    int Search(string &);
    void Input_file(istream &fin);
    void Extract_word(string &);
};
