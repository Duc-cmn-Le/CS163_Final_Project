#pragma once
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

using namespace std;

struct details {
    int x;
    details *next = NULL;
    vector<int> pos;
};
class Node {
public:
    Node *next[256] = {NULL};
    details *info = NULL;
};

struct Trie{
    Node *root = new Node;

};

struct Data {
    char filename[20];
    char *title = NULL;
    char *content = NULL;
};

void Openfile(istream &,string &,string &);
void Closefile(char *&,char*&);
