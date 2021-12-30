#include "function_plotter.h"
/**
 * constractor of Function_plotter class that initailize gui with input and plot graph
 * @brief function_plotter::function_plotter
 * @param parent
 */
function_plotter::function_plotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::function_plotter)
{
    ui->setupUi(this);
    pushButton->setText("Plot");
    line_edit2->setPlaceholderText("enter min value of x");
    line_edit3->setPlaceholderText("enter max value of x");
    line_edit->setPlaceholderText("enter f(x)");
    horizontal_layout ->addWidget(line_edit);
    horizontal_layout ->addWidget(line_edit2);
    horizontal_layout ->addWidget(line_edit3);
    horizontal_layout ->addWidget(pushButton);
    vertical_layout->addWidget(custom_plot);
    vertical_layout->addLayout(vertical_layout2);
    vertical_layout->addLayout(horizontal_layout);
    main_layout->addLayout(vertical_layout);
    widget->setLayout(main_layout);
    setCentralWidget(widget);
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
}

typedef struct{
    string op;
    double num;
}Token;
vector<Token> tokens;


/**
 * compares different operators priority
 * @brief compare
 * @param stack top operator
 * @param current operator
 * @return true if top of stack has higer priorty
 */
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

/**
 * converts string to set of token for easy arangement of operations
 * @brief get_tokens
 * @param equ
 * @return vector<string> that has string representation of each token
 */
vector<string> get_tokens(const string &equ)
{
    vector<string> tokens;
    string buff;
    bool flag =true;
    for (int i = 0; i < equ.size(); i++)
    {
        if(equ[i]==' ')continue;
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
//checks for unmatched ()
/**
 * checks for unmatched ()
 * @brief check_for_error
 * @param vector of tokens
 * @return true if ther is error
 */
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
/**
 * checks if two operators comes after each other
 *
 * @brief check_for_error2
 * @param vector tokens
 * @return true if error
 */
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

/**
 * convert form infix notaion to postfix notation for easy arangement of operation pirorties
 * @brief infix_to_postfix
 * @param vector tokens
 * @return true if error
 */
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

/**
 * calculate f(x) for a given x
* @brief evaluate_eq
* @param x
* @param vecotr of tokens postfix
* @return double -> value of y
*/
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

/**
 * plot graph
 * @brief function_plotter::on_push_button_clicked
 */
void function_plotter::on_push_button_clicked()
{

    string equ_string =line_edit->displayText().toStdString();
    double x1=line_edit2->displayText().toDouble();
    double x2=line_edit3->displayText().toDouble();
    if(x1>x2)
    {
        double tmp =x2;
        x2=x1;
        x1=tmp;
    }
    vector<string> t = get_tokens(equ_string);
    for(auto i: t)
    {
        if(isalpha(i[0])&&i[0]!='x')
        {
            QMessageBox::critical(this,tr("wrong input"),tr("f(x) connot have varibles other than x"));
            return;
        }
    }
    if (check_for_error2(t))
    {
        QMessageBox::critical(this,tr("wrong input"),tr("enter a valid math expression"));
        return;
    }
    if (check_for_error(t))
    {
        QMessageBox::critical(this,tr("wrong input"),tr("parentheses are not properly closed"));
        return;
    }
    vector<Token> equ =infix_to_postfix(t);
    QVector<double> x(101) ,y(101);
    for(int i=0;i<=100;i++)
    {
        double z= (x1+((x2-x1)/100)*i);
        x[i]=(z);
        y[i]=(evaluate_eq(z,equ));
    }
    custom_plot->addGraph();
    custom_plot->graph(0)->setData(x,y);
    custom_plot->xAxis->setLabel("x");
    custom_plot->yAxis->setLabel("y");
    double min=y[0] ,max=y[0];
    for(auto j:y)
    {
        if(min>j)
        {
            min=j;
        }
        if(max<j)
        {
            max=j;
        }
    }
    if(min>0)min=0;
    else min-=5;
    int min_x=0;
    if(x1<0)min_x=x1-5;
    custom_plot->xAxis->setRange(min_x,x2+2);
    custom_plot->yAxis->setRange(min,max+2);
    custom_plot->replot();
}

function_plotter::~function_plotter()
{
    delete ui;
}

