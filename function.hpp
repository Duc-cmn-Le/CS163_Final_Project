#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <algorithm>

#define equal =
#define oo 10000000
#define DEBUG(x) cout << x
#define DEBUN(x) cout << x << '\n'
#define ZERO(x) for (int i=0;i<number_of_file;++i) *(x+i) = 0;

using namespace std;

struct details {
    int file_id; 
    details *next = NULL;
    vector<int> pos;
};
class Node {
public:
    Node *next[256];
    details *info = NULL; // info is a linkedlist
    int point = 0;
    Node() {for (int i=0;i<256;++i) next[i] = NULL;}
};

struct Trie{
    Node *root = new Node;
    ~Trie();
    void Destruct(details*);
    void Destruct(Node*);
    void Insert(const char*,int,int); // word, file_id, pos_in_content
    void Show_trie(Node *cur,string s ="");
    int iFind(char*);
    Node *Find(char*);
};

struct Data {
    char filename[20];
    char *title = NULL;
    char *content = NULL;
};

int Query(int flag,Trie T,char *word,int *rating,int &number_of_file); 
void Open_file(istream &,string &,string &);
void Free_file(char *&,char*&);
int FILTERING(string file_name);
int Check_all_space(string &s);
int Next_token(string &s,string &target,char c=' ');
