#include "function.hpp"

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
        Openfile(fin_2,title,content);
        database[i].title = new char [title.length()];
        strcpy(database[i].title,title.c_str());
        database[i].content = new char [content.length()];
        strcpy(database[i].content,content.c_str());
        fin_2.close();
    }
    fin.close();
    system("rm file.tmp");
    // - - - - 
    
    


    
    // Free memory
    for (int i=0;i<number_of_file;++i) 
        Closefile(database[i].title,database[i].content);
    delete []database;
    return 0;
}
