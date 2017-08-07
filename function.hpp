#pragma once
#include <ctype.h>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>

#define DEBUG(x) cout << x
#define DEBUN(x) cout << x << '\n'
#define equal =

using namespace std;

struct details {
    int file_id; 
    details *next = NULL;
    vector<int> pos;
};
class Node {
public:
    Node() {for (int i=0;i<256;++i) next[i] = NULL;}
    Node *next[256];
    details *info = NULL; // info is a linkedlist
    int point = 0;
};

struct Trie{
    ~Trie();
    void Destruct(details*);
    void Destruct(Node*);
    Node *root = new Node;
    void Insert(const char*,int,int); // word, file_id, pos_in_content
    Node *Find(char*);
    void Show_trie(Node *cur,string s ="");

};

struct Data {
    char filename[20];
    char *title = NULL;
    char *content = NULL;
};

void Open_file(istream &,string &,string &);
void Free_file(char *&,char*&);
int FILTERING(string file_name);
int Check_all_space(string &s);
int Next_token(string &s,string &target,char c=' ');
