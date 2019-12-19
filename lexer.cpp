//
// Created by noa on 12/12/2019.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class lexer {
public:

    vector<string> lex() {
        string word = "";
        ifstream file;
        string line;
        vector <string> linesVector;
        vector <string> token;

        freopen("text.txt", "rb", stdin);
        while (getline(cin, line)) {
            linesVector.push_back(line);

        }
        for (int i = 0; i < linesVector.size(); i++) {
            for (int j = 0; j < linesVector[i].length(); j++) {
                //tabs
                if (word == "\t") {
                    word = "";
                }
                size_t found = word.find("+=");
                size_t found2 = word.find("-=");
                if ((found != string::npos)) {
                        string sub = word.substr(0, found);
                        token.push_back(sub);
                        sub = word[found];
                        sub +=word[found + 1];
                        token.push_back(sub);
                        sub = linesVector[i].substr(j, linesVector[i].length());
                        if (sub[0]==' '){
                            sub=sub.substr(1, sub.length());
                        }
                        token.push_back(sub);
                        j = -1;
                        i++;
                        word = "";
                    }
                   else if ((found2 != string::npos)) {
                    string sub = word.substr(0, found2);
                    token.push_back(sub);
                    sub = word[found2];
                    sub +=word[found2 + 1];
                    token.push_back(sub);
                    sub = linesVector[i].substr(j, linesVector[i].length());
                    if (sub[0]==' '){
                        sub=sub.substr(1, sub.length());
                    }
                    token.push_back(sub);
                    j = -1;
                    i++;
                    word = "";
                }else {
                    if ((linesVector[i][j] == '(') || (linesVector[i][j] == ')')) {
                        token.push_back(word);
                        int k = linesVector[i].length();
                       // string word2 = linesVector[i]
                        word=sub_last_tub(linesVector[i], j+1, linesVector[i].length()-1);
                        for (int t = 0; t < word.length(); t++) {
                            if (word[t] == ',') {
                                string subWord =sub_last_tub(word,1,t-1);
                                token.push_back(subWord);
                                subWord = sub_last_tub(word,t + 1, word.length());
                                token.push_back(subWord);
                                word = "";
                            }
                        }
                        token.push_back(word);

                        j = -1;
                        i++;
                        word = "";
                    } else {
                        //-> <-
                        if (((linesVector[i][j] == '-') && (linesVector[i][j + 1] == '>')) ||
                            (((linesVector[i][j] == '<') && (linesVector[i][j + 1] == '-')))) {
                            token.push_back(word);
                            word = "";
                            word += linesVector[i][j];
                            word += linesVector[i][j + 1];
                            j = j + 1;
                            token.push_back(word);
                            word = "";

                        } else {
                            //=
                            if ((linesVector[i][j] == '=')&&(linesVector[i][j-1]!='+')&&(linesVector[i][j-1]!='-')
                            &&(linesVector[i][j-1]!='<')&&((linesVector[i][j-1]!='>'))&&(linesVector[i][j-1]!='!')) {
                                token.push_back(word);
                                word = linesVector[i][j];
                                token.push_back(word);
                                if (linesVector[i][j+1]==' '){
                                    word = linesVector[i].substr(j + 2, linesVector[i].length());
                                }
                                else {
                                    word = linesVector[i].substr(j + 1, linesVector[i].length());
                                }
                                token.push_back(word);
                                word = "";
                                j = linesVector[i].length();
                            } else if ((linesVector[i][j] == '{') || (linesVector[i][j] == '}')) {
                                token.push_back(word);
                                word = "";
                                word = linesVector[i][j];
                                j = j + 1;
                                token.push_back(word);
                                word = "";
                            } else if (linesVector[i][j] == ' ') {
                                token.push_back(word);
                                word = "";
                            } else if (linesVector[i][j] == ',') {
                                token.push_back(word);
                                word = "";
                                j++;
                            } else {
                                word += linesVector[i][j];
                            }
                        }
                    }
                }
            }
            }

        for (auto k = token.begin(); k != token.end(); ++k) {
            if ((*k == "") || (*k == " ")) {
                token.erase(k);
            }
        }
        for (int t = 0; t < token.size(); t++) {
            cout << token[t] << endl;
        }

        file.close();
        return token;
    }
    string sub_last_tub(string s, int start, int end){
        string word="";
        for (int i=start; i< end; i++){
            word+=s[i];
        }
        return word;
    }
};