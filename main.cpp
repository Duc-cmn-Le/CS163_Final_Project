#include "function.hpp"
#define xau database[i].title
#define chuoi database[i].content


int main() {
    int number_of_file;
    string String;
    system("ls -F CS163-Data |grep -v / | wc -l > file.tmp");
    ifstream fin("file.tmp"), fin_2;
    fin >> number_of_file;
    fin.close();
    system("rm file.tmp");
    Data *database = new Data[number_of_file];
    system("ls CS163-Data > file.tmp");
    fin.open("file.tmp");
    // Storing database
    cout << "\033[31mLoading data \033[34mPlease wait\n\033[0m";
    string title, content;
    for (int i=0;i<number_of_file;++i) {  
        fin >> String;
        strcpy(database[i].filename,String.c_str());
        FILTERING(String);
        fin_2.open("CS163-Data/"+String);
        Open_file(fin_2,title,content);
        database[i].title = new char [title.length()];
        strcpy(database[i].title,title.c_str());
        database[i].content = new char [content.length()];
        strcpy(database[i].content,content.c_str());
        fin_2.close();
    }
    fin.close();
    system("rm file.tmp");
    // - - - - End


    
    // INDEXING WORDS TO DATABASE
    // - - - - -
    Trie T_title; Trie T_content;    
    int is_acceptable_char[256] = {0};
    is_acceptable_char['$'] = is_acceptable_char['#'] = is_acceptable_char['@'] = 1;
    is_acceptable_char['&'] = is_acceptable_char['*'] = is_acceptable_char['%'] = 1;
    for (int i='0';i<='9';++i) is_acceptable_char[i] = 2;
            // - - - - 
            //
//    /*
    for(int i=0;i<number_of_file;i++) {
        //Title
        int len=strlen(xau);
        string tmp;
        for(int j=0;j<len;j++) 
        if (isascii(xau[j]))
        {
            if (is_acceptable_char[xau[j]] == 1) {
                tmp="^";
                tmp[0]=xau[j];
                T_title.Insert(tmp.c_str(),i,j);
            }
            else if (isalnum(xau[j])) {
                tmp=tolower(xau[j]);
                int k=j;
                while (j<len-1)
                if (isalnum(xau[++j]) || xau[j]=='\'' || xau[j]=='-')
                    tmp+=tolower(xau[j]);
                else break;
                if (is_acceptable_char[xau[j]] == 1) {
                    string temp="^";
                    temp[0]=xau[j];
                    T_title.Insert(temp.c_str(),i,j);
                }
                T_title.Insert(tmp.c_str(),i,k);
                if (!isalnum(tmp[tmp.size()-1])) {
                    tmp.erase(tmp.end()-1);
                    T_title.Insert(tmp.c_str(),i,k);
                }
            }
        }
        //Content
        len=strlen(chuoi);
        for(int j=0;j<len;j++) 
        if (isascii(chuoi[j]))
        {
            if (is_acceptable_char[chuoi[j]] == 1) {
                tmp="^";
                tmp[0]=chuoi[j];
                T_content.Insert(tmp.c_str(),i,j);
            }
            else if (isalnum(chuoi[j])) {
                tmp=tolower(chuoi[j]);
                int k=j;
                while (j<len-1)
                if (isalnum(chuoi[++j]) || chuoi[j]=='\'' || chuoi[j]=='-')
                    tmp+=tolower(chuoi[j]);
                else break;
                if (is_acceptable_char[chuoi[j]] == 1) {
                    string temp="^";
                    temp[0]=chuoi[j];
                    T_content.Insert(temp.c_str(),i,j);
                }
                T_content.Insert(tmp.c_str(),i,k);
                if (!isalnum(tmp[tmp.size()-1])) {
                    tmp.erase(tmp.end()-1);
                    T_content.Insert(tmp.c_str(),i,k);
                }
            }
        }
    }
//    */
    //add stopwords
    Trie T_stop;
    fin.open("stopwords.txt");
    while (getline(fin,String))
        T_stop.Insert(String.c_str(),0,0);
    fin.close();
    // ---- end

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /****/ cout << setw(50) << "\033[1;4;34mSEARCH ENGINE\033[0m\n"; // ||
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    int *file_list = new int [number_of_file];
//    for (int i=0;i<number_of_file;++i) file_list[i] = i;
    int *rating = new int [number_of_file];
    int *ranking = new int [number_of_file];
        for (int i=0;i<number_of_file;++i) ranking[i] = i;
    int *good = new int [number_of_file]; // -1 means not good
    String = "";
    /* This program will support these queries
     * AND 
     * OR 
     * Manchester -united
     * intitle:hammer nails
     * Peanut Butter +and Jam
     * filetype:txt
     * $400
     * $throwbackthursday
     * "tallest building"
     *
     *
     *
     *
     *
     *
     */
//    /*
    string s;
    while ((cout << "> ") && (getline(cin,String)) && (String != "quit_")) {
        if (String == "\n" || String == "" || Check_all_space(String)) continue;
        ZERO(rating); 
         


    }
    cout << "Exiting\n";
//    */

    ///  FREE MEMORY
    // - - -
    for (int i=0;i<number_of_file;++i) 
        Free_file(database[i].title,database[i].content);
    delete []database;
//    delete []file_list;
    delete []rating;
    delete []ranking;
    delete []good;
    return 0;
}
