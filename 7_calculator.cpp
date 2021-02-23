#include "std_lib_facilities.h"

const char number = '8';
const char prompt = '>';
const char print = ';';
const char quit = 'q';
const char result = '='; // Used to indicate that what follows is a result
const char name = 'a';
const char let = 'L';
const char command = 'C';
const string declkey = "let";
const string printVars = "printVars";

class Variable
{
public:
    string name;
    double value;
};

vector<Variable> var_table;
double get_value(string var)
{
    for (const Variable &v : var_table)
    {
        if (v.name == var)
            return v.value;
    }
    error("Get undefined variable ", var);
}

void set_value(string var, double val)
{
    for (Variable &v : var_table)
    {
        if (v.name == var)
        {
            v.value = val;
            return;
        }
        error("Set undefined variable ", var);
    }
}

bool is_declared(string var)
{
    for (const Variable &v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val)
{
    if (is_declared(var))
        error(var, " is declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

class Token
{
public:
    char kind;
    double value;
    string name;
    Token(char ch) : kind{ch}, value{0} {}
    Token(char ch, double val) : kind{ch}, value{val} {}
    Token(char ch, string n) : kind{ch}, name{n} {}
};

class Token_stream
{
public:
    Token_stream() : full(false), buffer(0){};
    Token get();
    void ignore(char c);
    void putback(Token t);

private:
    bool full{false};
    Token buffer;
};

void Token_stream::putback(Token t)
{
    if (full)
        error("Putback() into a full buffer");
    buffer = t;
    full = true;
}

/**
 * Read character form cin and compose a Token
 */
Token Token_stream::get()
{
    if (full) // Check if we already have a Token ready
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch; // Note that >> skips whitespace
    switch (ch)
    {
    case print:
    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token(ch); // Let each character represent itself
    case '.':             // A floating point literal can start with a dot
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        cin.putback(ch); // Put back intno the input stream
        double val;
        cin >> val; // Read a floating point number
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);
            if (s == declkey)
                return Token{let};
            if (s == printVars)
            {
                for (const Variable &var : var_table)
                {
                    cout << var.name << " " << var.value << endl;
                }
                return Token{command};
            }

            return Token{name, s};
        }
        error("Invalid token", ch);
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (cin >> ch)
        if (ch == c)
            return;
}



Token_stream ts;
double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case number:
        return t.value;
    case name:
		return get_value(t.name);
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected", t.kind);
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                error("divided by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0)
                error("divided by zero");
            left = left - d * int(left / d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    case command:
        return 0.0;
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

void calculate()
{
    while (cin)
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;

            ts.putback(t);
            cout << result << statement() << endl;
        }
        catch (exception &e)
        {
            cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}

int main()
{
    try
    {
        define_name("pi", 3.1415926535);
        define_name("e", 2.7182818284);

        calculate();

        keep_window_open();
        return 0;
    }
    catch (exception &e)
    {
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch (...)
    {
        cerr << "exception\n";
        keep_window_open("~~");
        return 2;
    }
}