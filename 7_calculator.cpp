#include "std_lib_facilities.h"

const char number = '8';
const char prompt = '>';
const char print = ';';
const char quit = 'q';
const char result = '='; // Used to indicate that what follows is a result

class Token
{
public:
    char kind;
    double value;
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, double val) : kind(ch), value(val) {}
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
        error("Invalid token");
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

class Variable {
    public:
        string name;
        double value;
};

vector<Variable> var_table;
double get_value(string s)
{
    for(const Variable& v: var_table)
    {
        if(v.name == s) return v.value;
        error("Get undefined variable ", s);
    }
}

void set_value(string s, double v)
{
    for(Variable& v: var_table)
    {
        if(v.name == s)
        {
            v.value = v;
            return;
        }
        error("Set undefined variable ", s)
    }
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
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
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



double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();    
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
            {
                t = ts.get();
            }
            if (t.kind == quit)
                return;
            ts.putback(t);
            cout << result << statement() << '\n';
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