/*
Login System

Rules for usernames & passwords
1. names must be greater than 8 characters & less than 32
2. same rule applies to passwords
3. passwords must be multi case & contain at least one special character & number
*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool good_username(string username) {
    if (username.length() < 8 || username.length() > 32) {
        return false;
    }
    return true;
}

bool good_password(string password) {

    bool upper = false;
    bool lower = false;
    bool special = false;
    bool number = false;

    if (password.length() < 8 || password.length() > 32) {
        return false;
    }

    // Use ascii codes to check character;
    for (auto character: password) {
        if (character >= 48 && character <= 57) {
            number = true;
        }
        else if (character >= 65 && character <= 90) {
            upper = true;
        }
        else if (character >= 97 && character <= 122) {
            lower = true;
        }
        else {
            special = true;
        }
    }

    return upper && lower && special && number;
}

bool sign_in(string username, string password) {
    ifstream myfile;
    myfile.open("users.txt");
    string user_pass;

    int index = 7;
    bool sign_in = false;

    while(getline(myfile, user_pass)) {
        string user;
        string pass;
        
        // Custom split function (essentially)
        for (int index = 7; index < user_pass.length(); index++) {
            if (user_pass[index] == ':') {
                user = user_pass.substr(0, index);
                pass = user_pass.substr(index + 2, user_pass.length());
                break;
            }
        }

        if (user.compare(username) == 0 && pass.compare(password) == 0) {
            sign_in = true;
            break;
        }

    }

    myfile.close();
    return sign_in;
}

void register_account(string username, string password) {
    // If account exists, break
    if (sign_in(username, password)) {
        cout << "Account already exists" << endl;
        return;
    }

    ofstream myfile;
    myfile.open("users.txt", ios::app | ios::in);

    // If they don't, write here
    myfile << username << ": " << password << "\n";

    cout << "Successfully made an account" << endl;
    myfile.close();
}


int main() {
    int x;
    cout << "1. Register\n2. Sign in" << endl;
    cin >> x;

    string username;
    string password;
    cout << "Enter Username" << endl;
    cin >> username;
    cout << "Enter Password" << endl;
    cin >> password;

    // checks before we move on

    if (!good_password(password) && !good_username(username)) {
        cout << "Bad credentials" << endl;
        return -1;
    }

    bool foo;

    switch (x) {
        case 1:
            register_account(username, password);
            break;
        case 2:
            foo = sign_in(username, password);
            if (foo) {
                cout << "Sign in successful" << endl;
            } else {
                cout << "Sign in unsuccessful" << endl;
            }
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

    return -1;
}