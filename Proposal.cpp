#include<cctype> ///for tolower function

void Trie::Extract_word(string &s)
{
    string tmp;
    for(string::iterator i=s.begin();i!=s.end();i++)
    if (*i!=' ')
    {
        tmp=tolower(*i);
        while (i!=s.end()-1)
        if (*(++i)!=' ') tmp+=tolower(*i);
        else break;
        Insert(tmp);
    }
}

void Trie::Input_file(const string file_name)
{
    ifstream f(file_name);
    string s;
    while (getline(f,s))
        Extract_word(s);
    f.close();
}



