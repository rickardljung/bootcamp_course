#include <iostream>
#include <string>
using namespace std;

string caesar_decrypt (int key, string cipher)
{
    for(int i = 0; i < cipher.size(); i++) {
        int c = (static_cast<int> (cipher[i])) - key;
        int ascii_a = static_cast<int>('A');
        int ascii_z = static_cast<int>('Z');
        if(c < ascii_a) {
            c = ascii_z - (ascii_a - c) + 1;
        }
        cipher[i] = static_cast<char> (c);
    }
    return cipher;
}

int main()
{
    int key;
    cout << "Specify the caesar key (value between 0-26)" << endl;
    cin >> key;
    string cipher;
    cout << "Input the caesar cipher text" << endl;
    //flush input buffer
    cin.ignore();
    getline(cin, cipher);

    string decoded_message = caesar_decrypt(key, cipher);
    cout << endl << "Decoded message: " << decoded_message << endl;
}

