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
    Trie();
    ~Trie();
    void Insert(string &);
    void Show_trie(Node*,string);
    int Search(string &);
    void Extract_word(string);
    void Input_file(const string file_name);
};


class Search_Engine{
public:
    Trie* a;

};
