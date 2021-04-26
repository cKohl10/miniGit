#include "miniGit.hpp"

using namespace std;

Master::Master()
{

}
Master::~Master()
{
    doublyNode * node = new doublyNode;
    commitHead = node;
    node->head = nullptr;
}

void Master::init()
{
    fs::create_directory(".minigit");
}
void Master::add()
{ 

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

bool Master::commit()
{  
    int numChanges = 0;

    //Traverse every SLL node
    singlyNode* currNode = commitHead->head;
    while (currNode){
        //Check if file version exists already
        if (!fs::exists("/.miniGit" + currNode->fileName + currNode->fileVersion)){

            //If it does not exists, make a copy in the correct directory
            if(fs::copy_file(currNode->fileName, "/.miniGit" + currNode->fileName + currNode->fileVersion)){
                cout << "Copied file " << currNode->fileName + currNode->fileVersion << " succesfully" << endl;
            } else {
                cout << "Failed to copy " << currNode->fileName + currNode->fileVersion << endl;
            }
            numChanges++;
        } else {

            //Check if both versions are the same or not
            if (wasChanged(file2string(currNode->fileName), file2string("/.miniGit" + currNode->fileName + currNode->fileVersion))){
                
                //If the file was changed, increment version number
                currNode->fileVersion = to_string(stoi(currNode->fileVersion) + 1);
                if(fs::copy_file(currNode->fileName, "/.miniGit" + currNode->fileName + currNode->fileVersion)){
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