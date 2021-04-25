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
bool Master::commit()
{
    return false;
}