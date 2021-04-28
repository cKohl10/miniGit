#include "miniGit.hpp"

using namespace std;


// Issues : add file, then delete file, then add it back and it says its already been added, not sure if there is way to fix that
// adding files then deleting them then trying to commit changes
// checkout to go to different file version then removing file is seg fault
// checkout doesnt do very much either, should probably have an option to print out file names after you switch commit 
// and dont know how to have doubly nodes stay between times you run it so it seems like we might only have one doublyNode.
// for add seems like the version history needs to update and not alwasy be "0"

string file2string(string filename);
bool wasChanged(string f1, string f2);
string filenameConvert(string header, string filename, string fileVersion, bool showHeader);
bool fileCopy(string source, string dest);

Master::Master()
{
    doublyNode* commitInit = new doublyNode;
    commitHead = commitInit;
    commitInit->commitNumber = 1;
    commitInit->head = NULL;
    commitInit->next = NULL;
    commitInit->previous = NULL;
}
Master::~Master()
{
    doublyNode* curr = commitHead;
    doublyNode* temp = NULL;

    while(curr != NULL)
    {
        if(curr->head != NULL)
        {
            singlyNode* currSingly = curr->head;
            singlyNode* tempSingly = NULL;

            while(currSingly != NULL)
            {
                currSingly->next = tempSingly;
                delete currSingly;

                currSingly = tempSingly;
            }
        }
        curr->previous = temp;
        delete curr;
        curr = temp;
    }
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
    //--------------------------------------------------------------------------------
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
        if(prev != NULL)
        {
            prev->next = ptrToDelete->next;
        }

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
        ptrToCommit = ptrToCommit->previous;
    }
    if (ptrToCommit == NULL)
    {
        cout << "Commit number not found" << endl;
        return;
    }
    cout << "WARNING: you will loose your local changes if you checkout to different version before making a commit with your current local changes." << endl;
    cout << "Would you like to continue with commit number " << ptrToCommit->commitNumber << " (y/n): ";
    char option;
    cin >> option;
    cout << endl;

    //NOR gate that will return if not 'y' or 'Y'
    if (!(option == 'y' || option == 'Y')) return;

    commitHead->next = ptrToCommit; //makes the top point to the checkout commit
    ptrToCommit->previous = commitHead; //doubly links it
    ptrToCommit->next = NULL;
    commitHead = ptrToCommit; //make the new commit head our checkout commit

    //Traverse every SLL node
    singlyNode* currNode = commitHead->head;
    while (currNode != NULL){
        //Construct the fileName to find
        string file2Copy = filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, true);

        //Copy what is in the commit verion of the file into the original file
        if(fileCopy(file2Copy, currNode->fileName)){
            cout << "Copied file " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << " to " << currNode->fileName << " succesfully" << endl;
            currNode->fileVersion = to_string(stoi(currNode->fileVersion) + 1);
        } else {
            cout << "Failed to copy " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << " to " << currNode->fileName << endl;
        }
        currNode = currNode->next;

    }

    cout << "You have successfully checked out to commit number " << ptrToCommit->commitNumber << endl;

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

string filenameConvert(string header, string filename, string fileVersion, bool showHeader){
    //This function constructs the correct filename to search for

    string filenameHead = "";
    string filenameFoot = "";
    bool dotFound = false;

    //Splits the filename and type up to correctly make the name
    for (int i = 0; i < filename.size(); i++){
        if(filename[i] == '.') dotFound = true;
        else if(!dotFound) filenameHead += filename[i];
        else filenameFoot += filename[i];
    }

    if (showHeader) return header + filenameHead + "_" + fileVersion + "." + filenameFoot;
    else return filenameHead + "_" + fileVersion + "." + filenameFoot;
}

bool fileCopy(string source, string dest){
    //Create a new write-to file and duplicate the contents of source to this new file
    //This is created using buffers

    ifstream file_in(source);
    //Check if source file is open
    if (!file_in.is_open()){
        cout << "Could not open file: " << source << endl;
        return false;
    }
    ofstream file_out(dest);
    if (!file_out.is_open()){
        cout << "Could not open file: " << dest << endl;
        return false;
    }
    filebuf* inbuf  = file_in.rdbuf();
    filebuf* outbuf = file_out.rdbuf();

    //Start current pointer to char on the first value of the file
    char currentChar = inbuf->sbumpc();

    //This code works by incrementing a pointer at each character up in both files until fully copied
    int endOfFile = EOF;
    while (currentChar != endOfFile)
    {
        outbuf->sputc(currentChar);
        currentChar = inbuf->sbumpc();
    }

    file_in.close();
    file_out.close();
    return true;
}

int Master::commit()
{  
    int numChanges = 0;

    //Traverse every SLL node
    singlyNode* currNode = commitHead->head;
    while (currNode != NULL){
        //Construct the fileName to find
        string file2find = filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, true);
        string originalFile = filenameConvert(".minigit/", currNode->fileName, "0", true);

        //Check if file version exists already
        if (!fs::exists(originalFile)){

            //If it does not exists, make a copy in the correct directory
            if(fileCopy(currNode->fileName, file2find)){
                cout << "Copied file " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << " succesfully" << endl;
                //currNode->fileVersion = to_string(stoi(currNode->fileVersion) + 1);
            } else {
                cout << "Failed to copy " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << endl;
            }
            numChanges++;
        } else {

            //Check if both versions are the same or not
            if (wasChanged(file2string(currNode->fileName), file2string(file2find))){
                
                //If the file was changed, increment version number
                currNode->fileVersion = to_string(stoi(currNode->fileVersion) + 1);
                file2find = filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, true);
                if(fileCopy(currNode->fileName, file2find)){
                    cout << "Created file " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << " succesfully" << endl;
                } else {
                    cout << "Failed to create new version " << filenameConvert(".minigit/", currNode->fileName, currNode->fileVersion, false) << endl;
                }
                numChanges++;

            }
        }
        currNode = currNode->next;

    }

    cout << "Enter a description of the changes made. (Maximum of 100 Characters)" << endl;

    string description;

    bool goodLength = false;

    while(!goodLength)
    {
        cout << "Description: ";
        cin.ignore();
        getline(cin, description);

        if(description.length() <= 100) goodLength = true;
    }

    commitHead->message = description;

    //Create new DLL node and copy SLL nodes to the new node
    doublyNode* newCommit = new doublyNode;
    newCommit->commitNumber = commitHead->commitNumber + 1;
    commitHead->next = newCommit;
    newCommit->previous = commitHead;
    commitHead = newCommit;

    //Start SLL node list at prevCommit head
    singlyNode* oldNode = commitHead->previous->head;
    singlyNode* prev = NULL;

    //Copy every node into new commit node
    while (oldNode != NULL){
        singlyNode* nn = new singlyNode;
        nn->fileName = oldNode->fileName;
        nn->fileVersion = oldNode->fileVersion;

        //Check if it's the first SLL node in the commit
        if (prev == NULL) commitHead->head = nn;
        else prev->next = nn;
        prev = nn;
        oldNode = oldNode->next;
    }

    if (!numChanges) return -1;
    return commitHead->previous->commitNumber;
}
