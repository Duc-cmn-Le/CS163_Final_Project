#include "UI.hpp"

void User_interface::Program() {
    cout << setw(50) << "\033[1;4;32mSEARCH ENGINE\033[0m\n";     
}   

//    User_interface::Query_processing(string &s,Search_Engine New) {
int* User_interface::Query_processing(string &s,Search) {
	
	string tmp = "\0";int type = 0;
	vector<string> group;
	if (s.find("\"") != -1) // string s contain " (quotion mark)
	{
		int m = -1, count = 0;
		while (m != s.size() - 1) {
			m = s.substr(m + 1).find("\"");
			if (m != -1)
				count++;
			else break;
		}
		if (count == 2) {
			type = 7;
			s = s.substr(s.size() - 2);
			group.push_back(s);
		}
		else if (count == 4)
		{
			type = 8;
			int count = 4;
			for (int m = 0;count >= 0, s != "\0";s = s.substr(m)) {
				while  (s.find(" ") == 0) s = s.substr(1);
				if (s.find("\"") == 0) {
					tmp += "\"";
					tmp += s.substr(0, s.substr(1).find("\""));
				}
				tmp = s.substr(0, s.find("\""));
				while (tmp.find(" ") == 0) tmp = tmp.substr(1);
				if (tmp != "\0") {
					count--;
					group.push_back(tmp);
					tmp = "\0";
				}
				m = s.find("\"") + 1;
			}
		}
	} else group.push_back(s);
	int where1 = -1, where2 = -1;
	vector<string> keyword; keyword.reserve(15);
	if (group.size() == 1) {
		string a = group[1];
		for (int i = 0;i < a.length();i++) {
			if (a[i] == '"' || a[i] == '/' || a[i] == '\\') {
				if (tmp == " ") tmp = "\0";
				if (tmp != "\0") {
					keyword.push_back(tmp);
					tmp = "\0";
				}
			}
			else if (a[i] == ' ' || a[i] == '\0') {
				if (tmp == " ") tmp = "\0";
				if (tmp != "\0") {
					keyword.push_back(tmp);
					tmp = "\0";
				}
			}
			if (tmp == " ") tmp = "\0";
			tmp += a[i];
		}
		if (tmp == " ") tmp = "\0";
		if (tmp != "\0") keyword.push_back(tmp);
		tmp = "\0";
		where1 = 0;
		for (vector<string>::iterator i = keyword.begin(); i != keyword.end() && type == 0;i++, where1++)
		{
			if (*i == "AND") type = 1;
			else if (*i == "OR") type = 2;
			else if (i[0] == "-") type = 3;
			else if (i->substr(0, 8) == "intitle:") type = 4;
			else if (*i == "+")  type = 5;
			else if (i->substr(0, 9) == "filetype:" || i->substr(0, 4) == "ext:") type = 6;
			else if (i[0] == "\"" && *--i->end() == '\"') type = 7;
		}

	} else
	if (type == 8) {
		where2 = 0;
		for (vector<string>::iterator p = group.begin(); p != group.end() && type == 0;p++, where2++){
			if (*p == "AND") type = 1;
			else if (*p == "OR") type = 2;
			else if (p[0] == "-") type = 3;
			else if (p->substr(0, 8) == "intitle:") type = 4;
			else if (*p == "+")  type = 5;
			else if (p->substr(0, 9) == "filetype:" || p->substr(0, 4) == "ext:") type = 6;
			else if (p[0] == "\"" && *--p->end() == '\"') type = 7;
		}
	}
	
	int where;
	if (where1 != -1) where = where1;
	if (where2 != -1) where = where2;
	int *grade = new int[New.n];
	int *gradeTemp = new int[New.n];
	for (int i = 0;i < New.n;i++) {
		grade[i] = 0;
		gradeTemp[i] = 0;
	}
	switch (type)
	{
	case 0:
		for (int m = 0;m < New.n;m++)
			for (int h=0;h<keyword.size();h++)
				grade[m] += New.a[m].Search(keyword[h]);
		break;
	case 1:
		for (int m = 0;m < New.n;m++)
			for (int h = 0; h < where;h++)
				grade[m] += New.a[m].Search(keyword[h]);
		for (int m = 0;m < New.n;m++)
			for (int h = where + 1;h < keyword.size();h++)
				gradeTemp[m]+= New.a[m].Search(keyword[h]);
		for (int i = 0;i < New.n;i++)
		{
			if (grade[i] > 0 && gradeTemp[i] > 0)
				grade[i] += gradeTemp[i];
			else grade[i] = 0;
		}
		break;
	case 2:
		break;
	case 3:
		for (int m = 0;m < New.n;m++)
			for (int h = 0; h < where;h++)
				grade[m] += New.a[m].Search(keyword[h]);
		for (int m = 0;m < New.n;m++)
				gradeTemp[m] += New.a[m].Search(keyword[where].substr(1));
		for (int i = 0;i < New.n;i++)
			if (gradeTemp[i] > 0)
				grade[i] = 0;
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		for (int m = 0;m < New.n;m++)
			for (int h = 0;h < keyword.size();h++)
				if (New.a[m].Search(keyword[h]) > 0)
					grade[m]++;
		for (int i = 0;i < New.n;i++)
			if (grade[i] != keyword.size())
				grade[i] = 0;
		break;
	case 8:
	default: break;
	}
	delete[]gradeTemp;
	return grade;
}
//}

