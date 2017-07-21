#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<direct.h>
#include<Windows.h>
using namespace std;

class Node
{
public:
	bool inTitle; // is it a complete word and in title or not
	int point;// to ranking the relevant-index, times it appears , 0 for not a complete word 
	Node* p[40]; // number(10), letter(26),  
					 // @,.,%,$(4)
	Node();
};

class Trie {
private:
	void Destruct(Node*);	
public:
	Trie *nextTrie;
	Node* root;
	Trie();
	~Trie();
	void InsertTitle(string &);
	void InsertContent(string &);
	Node* Search(string &);
	void iniStopwordsTRIE();
};
void getFilenameList(string folder = "\\Data");

//void allFileToTRIE(vector<string> list)
//{
//	ifstream fin;
//	string tmp;
//	for (auto i : list)
//	{
//		fin.open(i);
//		while (fin.good())
//		{
//		
//		}
//	}
//}
//int checkOperator(string query) {
//	stringstream ss(query);
//	string tmp;
//	while (ss >> tmp) {
//		string get; get = tmp.substr(0, 8);
//		if (get == "intitle:") return 1;
//		if (tmp == "AND") return 2;
//		if (tmp == "OR") return 3;
//		if (tmp == "-") return 4;
//		if (tmp == "*") return 5;
//		if (tmp == "~") return 6;
//		if (tmp == "\"") return 7;
//		int length = tmp.length();
//		for (int i = 0; i <= length - 3; ++i) {
//			if (tmp[i] == '.'&&tmp[i + 1] == '.') return false;
//		}
//	}
//	return true;
//}