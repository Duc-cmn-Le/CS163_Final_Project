#include "function.hpp"
#define xau database[i].title
#define chuoi database[i].content

Data *database;

int main() {
    int number_of_file;
    string String;
    system("ls -F CS163-Data |grep -v / | wc -l > file.tmp");
    ifstream fin("file.tmp"), fin_2;
    fin >> number_of_file;
    fin.close();
    system("rm file.tmp");
    database = new Data[number_of_file];
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
        database[i].title = new char [title.length()+1];
        strcpy(database[i].title,title.c_str());
        title += ' ';
        content = title + content;
        database[i].content = new char [content.length()+1];
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
    cout << "\033[1;37mType :quit_ to exit\033[0m\n";
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /****/ cout << setw(50) << "\033[1;4;34mSEARCH ENGINE\033[0m\n"; // ||
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
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
   - * filetype:txt
     * $400 
     * #throwbackthursday
     * "tallest building"
     *
     *
     *
     *
     *
     *
     */
//    freopen("test.out","w",stdout);

    string s, s2, ss; int flag, first, n_input, intitle = 0;
    char *TITLE = new char [10];
    strcpy(TITLE,"intitle:");
    Trie* TT;
    vector<string> input;
    while ((cout << "> ") && (getline(cin,String)) && (String != ":quit_")) {
        if (String == "\n" || String == "" || Check_all_space(String)) continue;
        TT = &T_content; intitle = 0;
        ss = String;
        input.clear();
        ZERO(rating); 
        while (Next_token(String,s)) input.push_back(s);
        for (vector<string>::iterator i=input.begin();i!=input.end();++i)
            ToLower(*i);
        //
        first = true; flag = -2;
        n_input = input.size();
        for (int i=0;i<input.size();++i) {
            if (flag == -1) {
                if (input[i] == "and") flag = 1;
                if (input[i] == "or") flag = 0;
            }
            if (T_stop.iFind(input[i].c_str())) continue;
            // intitle:
            if (input[i].length() > 7) {
                int is_ok = 1;
                for (int j=0;j<8;++j)
                    if (input[i][j] != TITLE[j]) is_ok = 0;
                if (is_ok) {
                    intitle = 1, TT = &T_title;
                    Next_token(input[i],s2,':');
                }
            }
            if (first) {
                if (n_input > 1 && input[i+1] == "and") flag = 1;
                else flag = 0;
                Query(flag,*TT,input[i].c_str(),rating,number_of_file,database,intitle);
                first = 0;
                flag = -1;
            }
            else {
                if (flag == 0 || flag == 1)  
                    Query(flag,*TT,input[i].c_str(),rating,number_of_file,database,intitle);
                else {
                    if (input[i][0] == '-') {
                        input[i].erase(0,1);
                        flag = -oo;
                    }
                    else if (input[i][0] == '+') {
                        input[i].erase(0,1);
                        flag = 2;
                    }
                    else flag = 0;
                    Query(flag,*TT,input[i].c_str(),rating,number_of_file,database,intitle);
                }
                flag = -1;
            }

        }
        // hello algorithm and trump or duc -united 
        Sort_by_rating(ranking,rating,number_of_file);
        int count = 0;
        cout << "\033[1;32m" << ss << "\033[0m" << '\n'; 
        cout << left  << setw(27) << "\033[1;31m Rank (Score)\033[0m";
        cout << left << setw(28) << "\033[1;36mFilename\033[0m";
        cout << "\033[33mTitle\033[0m\n";
        for (int i=0;i<number_of_file;++i) {
            if (rating[ranking[i]] > 0) {
                cout << "\033[1;31m";
                cout.width(4); cout << right << i+1; cout << "). ";
                cout << setw(8) << left << rating[ranking[i]] << " \033[0m";
                cout << "\033[1;36m" << setw(17) << left << database[ranking[i]].filename;
                cout << "\033[33m";
                Show(100,database[ranking[i]].title);
                if (strlen(database[ranking[i]].title) > 100) cout << "...";
                cout << "\033[0m\n";
                count++;
            }
        }
        if (count == 0) cout << "Not found!\n";
    }
    cout << "Exiting\n";

    ///  FREE MEMORY
    // - - -
    for (int i=0;i<number_of_file;++i) 
        Free_file(database[i].title,database[i].content);
    delete []database;
    delete []rating;
    delete []ranking;
    delete []good;
    delete []TITLE;
    T_stop.Destruct();
    T_content.Destruct();
    T_title.Destruct();
    return 0;
}
