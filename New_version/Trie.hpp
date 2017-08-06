#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <string>

#define DEBUN(x) cout << x << '\n'
#define DEBUG(x) cout << x << ' '

using namespace std;

class Node{
public:
    int max_c = 255, max_p = 1600;
    int point[1600];
    Node* p[255];
    Node();
};

class Trie{
private:
    void Destruct(Node* );
public:
    Node* root;
    int max_c = 255;
    Trie();
    ~Trie();
    void Insert(string &,int);
    void Show_trie(Node*,string,int);
//    void Show_trie();
    int Search(string &,int);
    void Input_file(istream &fin,int);
    void Extract_word(string &,int);
};
