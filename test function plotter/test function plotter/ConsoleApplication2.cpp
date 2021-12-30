#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <string>
using namespace std;
#include <assert.h>
typedef struct{
    string op;
    double num;
}Token;

vector<Token> tokens;
bool compare(const string& top, const string &current)
{
    //return false if current is greater that top
    if (current == "(")
        return false;
    else if (current == "+" || current == "-")
    {
        if (top == "(")
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if (current == "*" || current == "/")
    {
        if (top == "+" || top == "-" || top == "(")
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return (top == "^");
    }
}
vector<string> get_tokens(const string &equ)
{
    vector<string> tokens;
    string buff;
    bool flag =true;
    for (int i = 0; i < equ.size(); i++)
    {

        if( isdigit(equ[i]) || (flag && equ[i] == '-') )
        {
            flag = false;
            buff += equ[i];
        }
        else if (buff == "")
        {
            buff += equ[i];
            tokens.push_back(buff);
            buff = "";
        }
        else
        {
            tokens.push_back(buff);
            buff = equ[i];
            tokens.push_back(buff);
            buff = "";
        }

    }
    if (buff != "")tokens.push_back(buff);
    return tokens;
}

bool check_for_error(const vector<string>& tokens)
{
    stack<char>s;
    for (auto i : tokens)
    {
        if (i == "(")
        {
            s.push('(');
        }
        else if (i == ")")
        {
            if (s.empty())
                return true;
            else
                s.pop();
        }
    }
    return !s.empty();
}
bool check_for_error2(const vector<string>& tokens)
{
    for (int i =0 ;i<tokens.size()-1 ;i++)
    {
        if (tokens[i] == "*" || tokens[i] == "^" || tokens[i] == "/" || tokens[i] == "+" || tokens[i] == "-")
        {
            if (tokens[i + 1] == "*" || tokens[i + 1] == "^" || tokens[i + 1] == "/" || tokens[i + 1] == "+" || tokens[i + 1] == "-")
            {
                return true;
            }
        }
    }
    return false;
}

vector<Token> infix_to_postfix(const vector<string> &tokens)
{
    vector<Token> postfix;
    stack<string> op;
    for (auto token : tokens)
    {
        if (token == "*" || token == "^" || token == "/" || token == "(" || token == ")" || token == "+" || token == "-")
        {

            if (!op.empty())
            {
                if (token == ")")
                {
                    while (op.top() != "(")
                    {
                        postfix.push_back(Token{op.top(),0});
                        op.pop();
                    }
                    op.pop();
                }
                else if (compare(op.top(), token))
                {
                    do {
                        postfix.push_back(Token{ op.top(),0 });
                        op.pop();
                        if (op.empty())break;
                    } while (compare(op.top(), token));
                    op.push(token);
                }
                else
                {
                    op.push(token);
                }
            }
            else
            {
                op.push(token);
            }
        }
        else
        {
            if(token=="x")
                postfix.push_back(Token{ "x",0 });
            else
                postfix.push_back(Token{ "",stod(token)});;
        }
    }
    while (!op.empty())
    {
        postfix.push_back(Token{ op.top(),0 });
        op.pop();
    }
    return postfix;
}

double evaluate_eq(double x, const vector<Token> &postfix)
{
    stack<double> s;
    double temp1, temp2;
    for (auto token : postfix)
    {
        if (token.op == "*" || token.op == "/" || token.op == "^" || token.op == "+" || token.op == "-")
        {
            temp2 = s.top();
            s.pop();
            temp1 = s.top();
            s.pop();
            switch (token.op[0])
            {
            case '*':
                temp1 *= temp2;
                break;
            case '/':
                temp1 /= temp2;
                break;
            case '+':
                temp1 += temp2;
                break;
            case '-':
                temp1 -= temp2;
                break;
            case '^':
                temp1 = powl(temp1, temp2);
                break;
            }
            s.push(temp1);
        }
        else
        {
            if (token.op == "x")
                s.push(x);
            else
                s.push(token.num);
        }
    }
    return s.top();
}

bool test_get_tokens(string input ,vector<string> correct_output)
{
    vector<string> t=get_tokens(input);
    if (t == correct_output)
    {
        return true;
    }
    else
    {
        return false; 
    }
}
bool test_evaluate_eq(double correct_output, vector<Token> input)
{
    double t = evaluate_eq(3, input);
    if(t== correct_output)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void test()
{
    assert(test_get_tokens("x+5+2*x", vector<string>{"x", "+", "5", "+", "2", "*", "x", "^", "2"}));
    cout << "test_get_tokens output is correct \n";
    assert(test_evaluate_eq(26, infix_to_postfix(get_tokens("x+5+2*x^2"))));
    cout << "test_evaluate_eq output is correct \n";
}
int main()
{
    test();
}
