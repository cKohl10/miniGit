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
void Master::checkout()
{

}
bool Master::commit()
{

}