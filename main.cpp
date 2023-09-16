#include<iostream>
#include<stack>
#include<fstream>
#include<vector>
using namespace std;

int prec(char c){
    if(c == '/' or c == '*') return 2;
    else if(c == '+' or c == '-') return 1;
    return -1;
}

int solve_postfix(string &str){
    stack<int> s;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/') {
            int y = s.top();
            s.pop();
            int x = s.top();
            s.pop();
            switch(str[i]){
                case '+':
                    s.push(x+y);
                    break;
                case '-':
                    s.push(x-y);
                    break;
                case '*':
                    s.push(x*y);
                    break;
                case '/':
                    s.push(x/y);
                    break;
            }
        }
        else{
            string operand = "";
            while(i < str.length() and str[i] != '$'){
                operand += str[i++];
            }
            s.push(stoi(operand));
        }
    }
    return s.top();
}

void infix_to_postfix(string& str, string &res){
    stack<char> s;
    for(int i = 0; i < str.length(); i++){
        if(isspace(str[i])) continue;
        if(isdigit(str[i])) {
            while (isdigit(str[i])) res += str[i++];
            res += '$';
            i--;
        }
        else if(str[i] == '(') s.push('(');
        else if(str[i] == ')'){
            while(s.top() != '(') {
                res += s.top();
                s.pop();
            }
            s.pop();
        }
        else{
            while(!s.empty() and prec(str[i]) <= prec(s.top())){
                res += s.top();
                s.pop();
            }
            s.push(str[i]);
        }
    }
    while (!s.empty()){
        res += s.top();
        s.pop();
    }
}

int main()
{
    int choice;
    while(true){
        cout << endl;
        cout << "Enter expression for evaluation" << endl;
        cout << "Enter 'h' To watch history" << endl;
        cout << "Enter 'c' To clear history" << endl;
        cout << "Enter ctrl + c To exit" << endl;
        cout << "Enter: ";
        string exp;
        cout << "Enter expreation: ";
        getline(cin, exp);

        // import history data;
        vector<pair<string,string>> history;
        ifstream impot;
        impot.open("history.txt");
        while(!impot.eof()){
            string exp, res;
            getline(impot, exp);
            getline(impot, res);
            history.push_back({exp, res});
        }
        if(!history.empty()) history.pop_back();
        impot.close();

        // to check history
        if(exp == "h"){
            if(history.empty()) {
                cout << "History is empty..!" << endl;
                continue;
            }
            for(int i = 0; i < history.size(); i++){
                cout << "Expresion: " << history[i].first << endl;
                cout << "Result: " << history[i].second << endl;
            }
        }
        // to clear history
        else if(exp == "c"){
            if(history.empty()) {
                cout << "histroy is already empty..!" << endl;
                continue;
            }
            history.clear();
            ofstream expot;
            expot.open("history.txt");
            expot.close();
            cout << "History is cleared...!" << endl;
        }

        // evaluate expreasion
        else{
            string postfix = "";
            infix_to_postfix(exp, postfix);
            int res = solve_postfix(postfix);
            cout << res << endl;
            ofstream expot;
            expot.open("history.txt");
            history.push_back({exp, to_string(res)});
            for(int i = 0; i < history.size(); i++){
                expot << history[i].first << endl;
                expot << history[i].second << endl;
            }
            expot.close();
        }
    }
    return 0;
}