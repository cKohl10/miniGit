#include "miniGit.hpp"
#include <iostream>

void menu();

int main()
{
    int vari;
    string filename;
    string beginOption;
    int commitNum;
    int option = 0;

    //Initialize repository
    Master master;

    //Will ask if the user wants to create a new repostory in current directory
    cout << "Create an new repository in the current directory? (y/n)" << endl;
    cin >> beginOption;
    if (beginOption == "y" || beginOption == "Y") master.init();


    while(option != 5)
    {
        menu();

        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Enter filename to be committed: ";
            cin >> filename;
            // call function to add file to repository
            master.add(filename);
            break;

        case 2:
            cout << "Enter filename to be removed from current commit: ";
            cin >> filename;
            master.remove(filename);
            break;

        case 3:
            //function to commit changes
            if (master.commit()){
                cout << "Changes successfully committed" << endl;
            } else cout << "Commit unsuccessful" << endl;
            // probably need to print out commit number 
            break;

        case 4:
            cout << "Enter commit number: ";
            cin >> commitNum;
            //call function to view version for specific commit number
            break;

        case 5:
            // probably need to make sure all changes are commited before quitting.
            cout << "Goodbye!" << endl;
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