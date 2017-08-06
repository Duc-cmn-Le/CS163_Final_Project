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
        number_of_file = 1;
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
    Trie T_title, T_content;    
    for(int i=0;i<number_of_file;i++) {
        //Title
        int len=strlen(xau);
        string tmp;
        for(int j=0;j<len;j++)
        if (xau[j]=='$' || xau[j]=='#' || xau[j]=='@' || xau[j]=='&' || xau[j]=='*')
            T_title.Insert(xau+j,i,j);
        else if (isalnum(xau[j])) {
            tmp=tolower(xau[j]);
            int k=j;
            while (j<len-1)
            if (isalnum(xau[++j]) || xau[j]=='\'')
                tmp+=tolower(xau[j]);
            else break;
            if (xau[j]=='$' || xau[j]=='#' || xau[j]=='@' || xau[j]=='&' || xau[j]=='*')
                T_title.Insert(xau+j,i,j);
            T_title.Insert(tmp.c_str(),i,k);
            if (*(tmp.end()-1)=='\'') {
                tmp.erase(tmp.end()-1);
                T_title.Insert(tmp.c_str(),i,k);
            }
        }
        //Content
        len=strlen(chuoi);
        for(int j=0;j<len;j++)
        if (chuoi[j]=='$' || chuoi[j]=='#' || chuoi[j]=='@' || chuoi[j]=='&' || chuoi[j]=='*')
            T_content.Insert(chuoi+j,i,j);
        else if (isalnum(chuoi[j])) {
            tmp=tolower(chuoi[j]);
            int k=j;
            while (j<len-1)
            if (isalnum(chuoi[++j]) || chuoi[j]=='\'')
                tmp+=tolower(chuoi[j]);
            else break;
            if (chuoi[j]=='$' || chuoi[j]=='#' || chuoi[j]=='@' || chuoi[j]=='&' || chuoi[j]=='*')
                T_content.Insert(chuoi+j,i,j);
            T_content.Insert(tmp.c_str(),i,k);
            if (*(tmp.end()-1)=='\'') {
                tmp.erase(tmp.end()-1);
                T_content.Insert(tmp.c_str(),i,k);
            }
        }
    }


    
    // Free memory
    for (int i=0;i<number_of_file;++i) 
        Free_file(database[i].title,database[i].content);
    delete []database;
    return 0;
}
