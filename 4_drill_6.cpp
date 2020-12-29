#include "./std_lib_facilities.h"

constexpr double CM_TO_M{0.01};
constexpr double IN_TO_M{2.54 * CM_TO_M};
constexpr double FT_TO_M{12 * IN_TO_M};

double convertToM(double number, string unit)
{

    double cv{0.0};

    if (unit == "m")
    {
        cv = number;
    }
    else if (unit == "cm")
    {
        cv = number * CM_TO_M;
    }
    else if (unit == "in")
    {
        cv = number * IN_TO_M;
    }
    else if (unit == "ft")
    {
        cv = number * FT_TO_M;
    }

    return cv;
}

bool checkIfUnitValid(string unit)
{
    vector<string> validUnits{"cm", "m", "in", "ft"};
    return !(find(validUnits.begin(), validUnits.end(), unit) != validUnits.end());
}

double getSum(vector<double> values)
{

    double sum{0.0};

    for (int i = 0; i < values.size(); i++)
    {
        sum += values[i];
    }

    return sum;
}

int main()
{

    double value{0};
    string unit{""};

    double smallest{0};
    double largest{0};

    vector<double> values{};

    while (cin >> value >> unit)
    {

        if (checkIfUnitValid(unit))
        {
            cout << "Invalid unit enterd. Please use cm, m, in or ft." << endl;
            continue;
        }

        double convertedValue = convertToM(value, unit);

        cout << convertedValue << "m" << endl;

        if (values.size() == 0)
        {
            smallest = convertedValue;
            largest = convertedValue;
        }

        if (convertedValue < smallest)
        {
            smallest = convertedValue;
            cout << " the smallest so far" << endl;
        }

        if (convertedValue > largest)
        {
            largest = convertedValue;
            cout << " the largest so far" << endl;
        }

        values.push_back(convertedValue);
    }

    cout << "Smallest value is: " << smallest << "m" << endl;
    cout << "Largest value is: " << largest << "m" << endl;
    cout << "Sum of all values is: " << getSum(values) << "m" << endl;
    cout << "Number of values: " << values.size() << endl;

    sort(values);
    cout << "Values: ";
    for(int i = 0; i < values.size(); i++){
        cout << values[i] << "m ";
    }

    return 0;
}