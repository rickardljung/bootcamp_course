# include <iostream>
#include <math.h>

using namespace std;

int main()
{
    cout << "Think of a number between 1-128 and then press enter..." << endl;
    cin.ignore();

    int min = 1;
    int max = 128;
    int guess_number;
    bool number_found = false;
    while(!number_found) {
        int a = (round(max - min + 1)) / 2;
        guess_number = min + a;
        cout << "Is the number greater or equal to " << guess_number << "? (y/n)" << endl;
        char user_input;
        cin >> user_input;

        if (user_input == 'y') {
            if ((max - min) == 1) {
                min += 1;
            } else {
            min = guess_number;
            }
        } else {
            max = guess_number - 1;
        }
        if ((max - min) == 0) {
            number_found = true;
            guess_number = min;
        }
    }
    cout << "The number is: " << guess_number <<endl;
}