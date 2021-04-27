#include "miniGit.hpp"

using namespace std;

/*
Current version uses fs::copy_file() which is appearantly not allowed.
The plan is to finish the code with this function and implement it 
in our own funciton afterwards.
*/

Master::Master()
{
    doublyNode* commitInit = new doublyNode;
    commitHead = commitInit;
    commitInit->head = NULL;
    commitInit->next = NULL;
    commitInit->previous = NULL;
}
Master::~Master()
{
    
}
void Master::init()
{
    fs::create_directory(".minigit");
}

void Master::add(string filename) //need to add a pointer to 
{   
    //-------------------- This section has been tested and works --------------------
    if(!fs::exists(filename)) // checks to see if the file is in the current directory
    {
        while(!fs::exists(filename)) // if the file isnt in the current respository makes user enter valid filename 
        {
            cout << "Invalid file name, please try again." << endl;
            cout <<"Filename: ";
            cin >> filename;
        }
    }
    //--------------------------------------------------------------------------------

    singlyNode* temp = commitHead->head;
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

    if (prev) prev->next = newFile;
    else commitHead->head = newFile;
    newFile->fileName = filename;
    newFile->next = NULL;
    newFile->fileVersion = "0";
    cout << "File has been added" << endl;
    
    return;
}
void Master::remove(string filename)
{
    singlyNode* ptrToDelete = commitHead->head; //pointer to traverse is equal to the head of the singly linked list
    singlyNode* prev = NULL;
    bool found = false;
    while (ptrToDelete != NULL)
    {
        if (ptrToDelete->fileName == filename)
        {
            found = true;
            break;
        }
        prev = ptrToDelete;
        ptrToDelete = ptrToDelete->next;
    }
    if (found == true) //if the file has been found
    {
        prev->next = ptrToDelete->next;
        delete ptrToDelete;
    }
    
}
void Master::checkout(int commitNumber)
{
    doublyNode* ptrToCommit = commitHead;
    while (ptrToCommit != NULL) //while loop to find the commit
    {
        if(ptrToCommit->commitNumber == commitNumber)
        {
            cout << "Found commit" << endl;
            break;
        }
        ptrToCommit = ptrToCommit->next;
    }
    if (ptrToCommit == NULL)
    {
        cout << "Commit number not found" << endl;
        return;
    }
    cout << "WARNING: you will loose your local changes if you checkout a different version beforemaking a commit with your current local changes." << endl;
    cout << "Would you like to continue (y/n)";
    char option = getchar();
    if (option == 'y' || 'Y')
    {
        commitHead->next = ptrToCommit; //makes the top point to the checkout commit
        ptrToCommit->previous = commitHead; //doubly links it
        ptrToCommit->next = NULL;
        commitHead = ptrToCommit; //make the new commit head our checkout commit
    }
    else
    {
        return; //if they don't want to continue then return
    }

}

string file2string(string filename){
    string word;
    string line = "";
    ifstream file_r(filename);

    while (file_r >> word){
        line = line + word;
    }
    return line;
}

bool wasChanged(string f1, string f2){
    if (f1 == f2) return false;
    return true;
}

string filenameConvert(string header, string filename, string fileVersion){
    //This function constructs the correct filename to search for

    string filenameHead = "";
    string filenameFoot = "";
    bool dotFound = false;
    for (int i = 0; i < filename.size(), i++){
        if(filename[i] == '.') dotFound = true;
        else if(!dotFound) filenameHead += filename[i];
        else filenameFoot += filename[i];
    }

    return header + filenameHead + fileVersion + "." + filenameFoot;
}

bool Master::commit()
{  
    int numChanges = 0;

    //Traverse every SLL node
    singlyNode* currNode = commitHead->head;
    while (currNode){
        //Construct the fileName to find
        string file2find = filenameConvert("/.minigit/", currNode->fileName, currNode->fileVersion);

        //Check if file version exists already
        if (!fs::exists(file2find)){

            //If it does not exists, make a copy in the correct directory
            if(fs::copy_file(currNode->fileName, file2find)){
                cout << "Copied file " << currNode->fileName + currNode->fileVersion << " succesfully" << endl;
            } else {
                cout << "Failed to copy " << currNode->fileName + currNode->fileVersion << endl;
            }
            numChanges++;
        } else {

            //Check if both versions are the same or not
            if (wasChanged(file2string(currNode->fileName), file2string(file2find))){
                
                //If the file was changed, increment version number
                currNode->fileVersion = to_string(stoi(currNode->fileVersion) + 1);
                if(fs::copy_file(currNode->fileName, file2find)){
                    cout << "Created file " << currNode->fileName + currNode->fileVersion << " succesfully" << endl;
                } else {
                    cout << "Failed to create new version " << currNode->fileName + currNode->fileVersion << endl;
                }
                numChanges++;

            }
        }

    }

    //Create new DLL node and copy SLL nodes to the new node
    doublyNode* newCommit = new doublyNode;
    commitHead->next = newCommit;
    newCommit->previous = commitHead;
    commitHead = newCommit;
    
    //Start SLL node list at prevCommit head
    singlyNode* oldNode = commitHead->previous->head;
    singlyNode* prev;

    //Copy every node into new commit node
    while (oldNode){
        singlyNode* nn = new singlyNode;
        nn->fileName = oldNode->fileName;
        nn->fileVersion = oldNode->fileVersion;

        //Check if it's the first SLL node in the commit
        if (!prev) commitHead->head = nn;
        else prev->next = nn;
        prev = nn;
        oldNode = oldNode->next;
    }

    if (!numChanges) return false;
    return true;
}