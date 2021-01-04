#include "./std_lib_facilities.h"


vector<char> generateNumber(){

    vector<char> number {};
    int length {4};

    srand (time(NULL));

    for(int i = 0; i < length; ++i)
    {   
        bool validNumber = false;
        while(!validNumber)
        {
            int randN = rand() % 10;
            char randNC = (char) randN + '0';
            if(number.size() == 0 || find(number.begin(), number.end(), randNC) == number.end()){
                number.push_back(randNC);
                validNumber = true;
            }
        }
    }

    return number;
}

bool validateGuess(string guess)
{
    vector<char> validChars{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Check length
    if (guess.size() != 4)
    {
        cout << "Guess needs to be 4 digits long." << endl;
        return false;
    }

    // Check if string contains only valid characters
    for (char &g : guess)
    {
        if (find(validChars.begin(), validChars.end(), g) == validChars.end())
        {
            cout << "Only numbers are allowed" << endl;
            return false;
        }
    }

    return true;
}

void game()
{

    int tries{0};
    bool found{false};
    vector<char> number = generateNumber();

    cout << "#############################" << endl;
    cout << "### Guess the number!!!!! ###" << endl;
    cout << "#############################" << endl
         << endl;

    while (!found)
    {

        string guess{};
        bool validGuess{false};
        int bulls = 0;
        int cows = 0;

        while (!validGuess)
        {
            cout << "Your guess: ";
            cin >> guess;
            if(guess == "SHOWMETHEMONEY"){
                cout << number[0] << number[1] << number[2] << number[3] << endl;
            }
            validGuess = validateGuess(guess);
        }

        cout << "- - - - - - - - - - - - - - -" << endl;

        ++tries;

        for (int i = 0; i < guess.size(); ++i)
        {
            if (guess[i] == number[i])
            {
                ++bulls;
            }
            else if (find(number.begin(), number.end(), guess[i]) != number.end())
            {
                ++cows;
            }
        }

        if (bulls == 4)
        {
            found = true;
            cout << "You found the number in " << tries << " tries" << endl
                 << endl;
            cout << "Play again? (y/n): ";
            char option {'y'};
            cin >> option;
            if(option == 'n'){
                exit(0);
            }
        }
        else
        {

            for (int i = 0; i < bulls; ++i)
            {
                cout << "Bull ";
            }

            for (int i = 0; i < cows; ++i)
            {
                cout << "Cow ";
            }

            cout << endl;
        }

        cout << "- - - - - - - - - - - - - - -" << endl
             << endl;
    }
}

int main()
{

    while (true)
    {
        game();
    }

    return 0;
}