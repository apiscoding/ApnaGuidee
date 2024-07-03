#include <iostream> 
using namespace std;

int main() 
{
    double num1, num2;
    char operation;

    cout << "Simple Calculator\n";
    cout << "Enter an operation in the form: a + b\n";
    cout << "Supported operations: +, -, *, /\n";
    cout << "Example: 3.5 * 2\n";

    cout << "Enter calculation: ";
    cin >> num1 >> operation >> num2;

    switch (operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0)
                cout << "Result: " << num1 / num2 << endl;
            else
                cout << "Error: Division by zero" << endl;
            break;
        default:
            cout << "Error: Invalid operator" << endl;
    }

    return 0;
}