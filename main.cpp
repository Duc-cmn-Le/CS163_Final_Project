#include "SE.hpp"
#include "UI.hpp"


int main() {
    Search_Engine New;
    string s;
    getline(cin,s);
    New.Search_exact(s);
    return 0;
}
