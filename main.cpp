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
    string title, content;
    for (int i=0;i<number_of_file;++i) {  
        fin >> String;
        strcpy(database[i].filename,String.c_str());
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
    
    // Indexing words in database
    Trie T_title;
    Trie T_content;    
    int is_acceptable_char[256] = {0};
    is_acceptable_char['$'] = is_acceptable_char['#'] = is_acceptable_char['@'] = 1;
    is_acceptable_char['&'] = is_acceptable_char['*'] = is_acceptable_char['%'] = 1;
    for (int i='0';i<='9';++i) is_acceptable_char[i] = 2;
            // - - - - 
            //
        number_of_file equal 1;
    for(int i=0;i<number_of_file;i++) {
        //Title
        int len=strlen(xau);
        string tmp;
        for(int j=0;j<len;j++)
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
        //Content
//        /*
        len=strlen(chuoi);
        for(int j=0;j<len;j++)
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
//        */
    }
    //add stopwords
    Trie T_stop;
    fin.open("stopwords.txt");
    while (getline(fin,String))
        T_stop.Insert(String.c_str(),0,0);
    fin.close();
    T_stop.Show_trie(T_stop.root);
//    freopen("test.out","w",stdout);
//    T_title.Show_trie(T_title.root);
//    T_content.Show_trie(T_content.root);
    // Free memory
    for (int i=0;i<number_of_file;++i) 
        Free_file(database[i].title,database[i].content);
    delete []database;
    return 0;
}
