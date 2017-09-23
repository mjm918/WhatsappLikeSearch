#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <memory.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>

#define SIZE 10000
#define NOT_FOUND "Not found"
using namespace std;

char* clean_char(char *var) {
    int i = 0;
    while(var[i] != '\0') {
        var[i] = '\0';
        i++;
    }
    return var;
}
char* upper_string(char* s) {
    int c = 0;

    while (s[c] != '\0') {
        if (s[c] >= 'a' && s[c] <= 'z') {
            s[c] = (char) (s[c] - 32);
        }
        c++;
    }
    return s;
}
char* remove_spacing(char* str){

    char *write = str, *read = str;
    do {
        if (*read != ' ')
            *write++ = *read;
    } while (*read++);

    return str;
}
string searchOnlyKeywords(string txt,string key,int line){

    string array[SIZE];
    string tmp,show;
    int index = 0,keySize = 0;

    show = txt;

    char *cstr = new char[txt.size()+1];
    copy(txt.begin(),txt.end(),cstr);
    cstr[txt.size()] = '\0';
    txt = upper_string(remove_spacing(cstr));
    cstr = clean_char(cstr);
    copy(key.begin(),key.end(),cstr);
    key = upper_string(cstr);

    istringstream oss(key);
    while(oss >> tmp){
        array[index] = tmp;
        index++;
    }
    keySize = index;
    index = 0;
    for (int i = 0; i < array->size(); i++){
        if(txt.find(array[i]) != string::npos){
            index++;
        }else{
            index--;
        }
    }
    delete[]cstr;
    ostringstream iss;
    iss << line;

    if(index >= keySize){
        return iss.str()+"  "+show+" <- suggested result";
    }

    return iss.str();
}
int main() {

    clock_t clicks;
    float secs;
    int index = 0;

    string test[SIZE];
    string line;

    ifstream infile("test.txt");

    if(!infile){
        cout << "file error" << endl;
        return 0;
    }

    while (getline(infile,line)){
        test[index] = line;
        index++;
    }

    for (int i = 0; i < index; i++){
        cout << searchOnlyKeywords(test[i],"ip 7",i+1) << endl;
    }

    clicks = clock();
    secs   = ((float)clicks)/CLOCKS_PER_SEC;
    cout << "Operation took " << " (" << secs << " seconds)\n";
    return 0;
}

