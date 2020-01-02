
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class lexer {
public:
    vector<string> lex(const char* s) {
        // in word we save every time the word we want to push into the vector.
        string word = "";
        ifstream file;
        string line;
        vector <string> linesVector;
        vector <string> token;

        freopen(s, "rb", stdin);
        // split the code into lines - for its will be easy to work with
        while (getline(cin, line)) {
            linesVector.push_back(line);

        }
        // we iterate every line and then every char in line.
        for (int i = 0; i < linesVector.size(); i++) {
            for (int j = 0; j < linesVector[i].length(); j++) {
                //if the wors id tab - delete it. and restart the word.
                if (word == "\t") {
                    word = "";
                }
                // if the words contains += / -= we split the word different-
                size_t found = word.find("+=");
                size_t found2 = word.find("-=");
                // if the word contain +=
                if ((found != string::npos)) {
                    // cut the word until the +=
                    string sub = word.substr(0, found);
                    // push it into the vector.
                    token.push_back(sub);
                    // put into sub - +=
                    sub = word[found];
                    sub +=word[found + 1];
                    // and push it into the vector
                    token.push_back(sub);
                    // cut the expression after +=
                    sub = linesVector[i].substr(j, linesVector[i].length());
                    // if there is space
                    if (sub[0]==' '){
                        sub=sub.substr(1, sub.length());
                    }
                    token.push_back(sub);
                    // move to the next line.
                    j = -1;
                    i++;
                    word = "";
                }
                    // if the word contains -=
                else if ((found2 != string::npos)) {
                    // cut the word until +=
                    string sub = word.substr(0, found2);
                    // push it into the vector.
                    token.push_back(sub);
                    // cut the -=
                    sub = word[found2];
                    sub +=word[found2 + 1];
                    // push -= into the vector
                    token.push_back(sub);
                    // cut the expression after -=
                    sub = linesVector[i].substr(j, linesVector[i].length());
                    // cut space
                    if (sub[0]==' '){
                        sub=sub.substr(1, sub.length());
                    }
                    token.push_back(sub);
                    // move to the next line.
                    j = -1;
                    i++;
                    word = "";
                } else {
                    // if the next char is ( or )
                    if ((linesVector[i][j] == '(') || (linesVector[i][j] == ')')) {
                        // push the word until now.
                        token.push_back(word);
                        int k = linesVector[i].length();
                        // if after the ( there is {we want to cut different.
                        size_t found = linesVector[i].find("{");
                        if (found != string::npos){
                            word=sub_last_tub(linesVector[i], j+1, found-2);
                            token.push_back(word);
                            word=linesVector[i][found];
                        }
                        else {
                            // we want to save the all expression inside the () as one token
                            word = sub_last_tub(linesVector[i], j + 1, linesVector[i].length() - 1);
                        }
                        // sometimes inside the () there is , so we need to cut it between the ,.
                        if (word[word.length()-1]!='"') {
                            for (int t = 0; t < word.length(); t++) {
                                if (word[t] == ',') {
                                    string subWord = sub_last_tub(word, 1, t - 1);
                                    token.push_back(subWord);
                                    subWord = sub_last_tub(word, t + 1, word.length());
                                    token.push_back(subWord);
                                    word = "";
                                }
                            }
                        }
                        // if there is "
                        if (word[0]=='"'){
                            int size = token.size();
                            // if we have print we need ro dave the all print as one token.
                            if (token[size-1]!="Print") {
                                word = sub_last_tub(word, 1, word.length() - 1);
                            }
                        }
                        token.push_back(word);
                        // move to the next line.

                        j = -1;
                        i++;
                        word = "";
                    } else {
                        // -> <- we want to save the -> -< as one token.
                        if (((linesVector[i][j] == '-') && (linesVector[i][j + 1] == '>')) ||
                            (((linesVector[i][j] == '<') && (linesVector[i][j + 1] == '-')))) {
                            // push the word until the -> -<
                            token.push_back(word);
                            word = "";
                            // push the -> -<
                            word += linesVector[i][j];
                            word += linesVector[i][j + 1];
                            j = j + 1;
                            token.push_back(word);
                            word = "";
                        } else {
                            // if the word has = (only =) not != += -=....
                            if ((linesVector[i][j] == '=')&&(linesVector[i][j-1]!='+')&&(linesVector[i][j-1]!='-')
                                &&(linesVector[i][j-1]!='<')&&((linesVector[i][j-1]!='>'))&&(linesVector[i][j-1]!='!')&&(linesVector[i][j-1]!='=')&&(linesVector[i][j+1]!='=')) {
                                // push the word until =
                                token.push_back(word);
                                // push the =
                                word = linesVector[i][j];
                                token.push_back(word);
                                // if there is space
                                if (linesVector[i][j+1]==' '){
                                    word = linesVector[i].substr(j + 2, linesVector[i].length());
                                }
                                else {
                                    word = linesVector[i].substr(j + 1, linesVector[i].length());
                                }
                                token.push_back(word);
                                word = "";
                                j = linesVector[i].length();
                                // if there is {} we cut only them in one toke.
                            } else if ((linesVector[i][j] == '{') || (linesVector[i][j] == '}')) {
                                token.push_back(word);
                                word = "";
                                word = linesVector[i][j];
                                j = j + 1;
                                token.push_back(word);
                                word = "";
                                // if there is space-
                            } else if (linesVector[i][j] == ' ') {
                                // dont push empty word.
                                if (word!="") {
                                    token.push_back(word);
                                }
                                word = "";
                            } else {
                                word += linesVector[i][j];
                            }
                        }
                    }
                }
            }
        }
        // remove all the empty token from the vector.
        for (int i=0; i<token.size(); i++){
            if ((token[i]=="")||(token[i]==" ")||(token[i]=="\t")){
                token.erase(token.begin()+i);
            }
        }
        file.close();
        return token;
}

string sub_last_tub(string s, int start, int end) {
        string word="";
        for (int i=start; i< end; i++){
            word+=s[i];
        }
        return word;
}
};
