#include<iostream>
#include<stack>
using namespace std;

int prec(char c){
    if(c == '/' or c == '*') return 2;
    else if(c == '+' or c == '-') return 1;
    return -1;
}

void solve_postfix(string &str){
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
    cout << "Result: " << s.top() << endl;
}

void infix_to_postfix(string& str, string &res){
    stack<char> s;
    res = "";
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
    string exp;
    cout << "Enter expresion: ";
    getline(cin, exp);
    string postfix;
    infix_to_postfix(exp, postfix);
    solve_postfix(postfix);
    return 0;
}