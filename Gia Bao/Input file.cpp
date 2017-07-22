#include "trie.hpp"

void Trie::Input_file(istream &fin)
{
    string s;
    while (getline(fin,s))
        Extract_word(s);
}
