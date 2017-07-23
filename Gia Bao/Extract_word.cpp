void Trie::Extract_word(string &s)
{
    string tmp;
    for(string::iterator i=s.begin();i!=s.end();i++)
    if (*i!=' ' && *i != ':' && *i != '.' && *i != '?' && *i != ';' && *i != '!' && *i != ',' && *i != '\'')
    {
        tmp=tolower(*i);
        while (i!=s.end()-1)
        if (*(++i)!=' ' && *(i)!=':' &&  *(i)!='.' && *(i)!='?' && *(i)!=';' && *(i)!='!' && *i != ',')
            tmp+=tolower(*i);
        else break;
        Insert(tmp);
        if (*(tmp.end()-1)=='\'')
        {
            tmp.erase(tmp.end()-1);
            Insert(tmp);
        }
    }
}
