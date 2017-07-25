#include "UI.hpp"

int User_interface::Check_all_space(string &s) {
    for (string::iterator i=s.begin();i!=s.end();++i)
        if (*i != ' ' && *i != '\n') return false;
    return true;
}
void User_interface::Program() {
    cout << "\033[31mLoading data \033[34mPlease wait\n\033[0m";
    Search_Engine New;
    cout << setw(50) << "\033[1;4;34mSEARCH ENGINE\033[0m\n";     
    string s;
    while ((cout << "\033[35mEnter what you want to search or enter 'quit' to exit\nEnter here: \n\033[0m") && getline(cin,s)) {
        if (s == "quit") {
            cout << "Exiting\n";
            return;
        }
        if (s == "\n" || s == "" || Check_all_space(s)) continue;
        if (s.length() > 2 && *s.begin() == '"' && *(s.end()-1) == '"') {        
            s.erase(s.begin());
            s.erase(s.end()-1);
            New.Search_exact(s);
        }
        else New.Search_normal(s);
    }
}   

//    User_interface::Query_processing(string &s) {

//}

