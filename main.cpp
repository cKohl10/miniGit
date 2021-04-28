#include "miniGit.hpp"
#include <iostream>

void menu();

int main()
{
    string filename;
    string beginOption;
    int commitNum;
    int commitNumOut;

    //Option changed to char to fix an infinit loop error
    char option = '0';

    //Initialize repository
    Master master;

    //Will ask if the user wants to create a new repostory in current directory
    cout << "Create an new repository in the current directory? (y/n)" << endl;
    cin >> beginOption;
    if (beginOption == "y" || beginOption == "Y") master.init(); //creates new directory


    while(option != 5)
    {
        menu();

        cin >> option;
        if (!isdigit(option)) option = '6';
        switch (option){
        case '1':
            cout << "Enter filename to be committed: ";
            cin >> filename;
            // call function to add file to repository
            master.add(filename);
            break;

        case '2':
            cout << "Enter filename to be removed from current commit: ";
            cin >> filename;
            if (master.remove(filename)) cout << "File successfully removed" << endl;
            else cout << "File was not found" << endl;
            break;

        case '3':
            //function to commit changes
            commitNumOut = master.commit();
            if (commitNumOut >= 0){
                cout << "Changes successfully committed: Commit #" << commitNumOut << endl;
            } else cout << "Commit unsuccessful - Commit may be identical to previous commit" << endl;
            // probably need to print out commit number 
            break;

        case '4':
            cout << "Enter commit number: ";
            cin >> commitNum;
            master.checkout(commitNum); //returns to previous DL node with commit number parameter
            break;

        case '5':
            // probably need to make sure all changes are commited before quitting.
            cout << "Goodbye!" << endl;
            fs::remove_all(".minigit");
            return 0;
            break;
        
        default:
            cout << "Invalid option entered, please try again." << endl;
            break;
        }
        cout << endl << endl;
    }
    return 0;
}

void menu()
{
    cout << "Please select one of the following numerical options:" << endl;
    cout << "1. Add file to the current commit." << endl;
    cout << "2. Remove file from the current commit." << endl;
    cout << "3. Commit changes." << endl;
    cout << "4. Checkout previous version of repository" << endl;
    cout << "5. Quit" << endl;
    cout << "Select option : ";
}
