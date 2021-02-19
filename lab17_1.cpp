#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string &filename,vector<string> &names,vector<int> &scores,vector<char> &grade){
    ifstream source("name_score.txt");
    string text;
    char format[] = "%[^:]: %d %d %d";
    char name[100];
    int a,b,c;
    while(getline(source,text)){    
        int j = 0;
        sscanf(text.c_str(),format,name,&a,&b,&c);
        string txt = "";
        while(name[j] != '\0'){
        txt += name[j];
        j++;
        }
        names.push_back(name);
        scores.push_back(a+b+c);
        grade.push_back(score2grade(a+b+c)); 
    }
    source.close();
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string text;
    getline(cin,text);
    int z = text.find_first_of(' ');
    command = text.substr(0,z);
    key = text.erase(0,z+1);

}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades,string &key){
    cout << "---------------------------------" << endl;
    bool status = false;
    for(unsigned int i = 0;i < names.size();i++){
        if(key == toUpperStr(names[i])){
            status = true;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if(!status){
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------" << endl;    
}

void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string &key){
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0;i < names.size();i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")"<< endl;
        }
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
