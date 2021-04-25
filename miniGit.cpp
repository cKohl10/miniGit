#include "miniGit.hpp"

using namespace std;

Master::Master()
{

}
Master::~Master()
{
    
}
void Master::init()
{

}
void Master::add(string filename) //need to add a pointer to 
{   
    if(!fs::exists(filename)) // checks to see if the file is in the current directory
    {
        while(!fs::exists(filename)) // if the file isnt in the current respository makes user enter valid filename 
        {
            cout << "Invalid file name, please try again." << endl;
            cout <<"Filename: ";
            cin >> filename;
        }
    }

    singlyNode* temp;
    singlyNode* prev = NULL;

    while(temp != NULL)
    {
        if(temp->fileName == filename)
        {
            cout << "File has already been added" << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    singlyNode* newFile = new singlyNode;

    prev->next = newFile;
    newFile->fileName = filename;
    newFile->next = NULL;

    string versionNum;

    cout << "Enter file version number: ";
    cin >> versionNum;

    string versionBase = filename.substr(0, filename.length() - 6);
    string fileType = filename.substr(filename.length()-3, 3);

    newFile->fileVersion = versionBase + versionNum + "." + fileType;
    
    return;
}
void Master::remove()
{

}
void Master::checkout()
{

}
void Master::commit()
{

}