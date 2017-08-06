#include "function.hpp"

void Openfile(istream &fin,string &title,string &content) {
    content = "";
    string s;
    getline(fin,title);
    while (getline(fin,s))
        content += s;
}

void Closefile(char*& title, char*& content) {
    delete []title;
    delete []content;
}
