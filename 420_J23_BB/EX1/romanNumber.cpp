#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int nbEntered = 1946;
    char prevLowSymbol = 'M';

    cout << "Please enter a number between 1 and 4999: ";
    cin >> nbEntered;

    for (int i = 3; i >= 0; i--)
    {
        char highSymbol = 'M';
        char lowSymbol = 'M';

        int lowValue = pow(10, i); 
        int numberWorkingOn = (nbEntered / lowValue % 10);

        switch (i)
        {
        case 2:
            highSymbol = 'D';
            lowSymbol = 'C';
            break;
        case 1:
            highSymbol = 'L';
            lowSymbol = 'X';
            break;
        case 0:
            highSymbol = 'V';
            lowSymbol = 'I';
            break;
        }

        while (numberWorkingOn > 0)
        {
            switch (numberWorkingOn)
            {
            case 9:
                if (i != 3) 
                {
                    cout << lowSymbol << prevLowSymbol;
                    numberWorkingOn -= 9;
                    break;
                }
            case 8:
            case 7:
            case 6:
            case 5:
                if (i != 3)
                {
                    cout << highSymbol;
                    numberWorkingOn -= 5;
                    break;
                }
            case 4:
                if (i != 3)
                {
                    cout << lowSymbol << highSymbol;
                    numberWorkingOn -= 4;
                    break;
                }
            default:
                cout << lowSymbol;
                numberWorkingOn -= 1;
                break;
            }
        }

        prevLowSymbol = lowSymbol;
    }

    return 0;
}
