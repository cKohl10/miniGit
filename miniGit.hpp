#ifndef MINIGIT_H
#define MINIGIT_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;
namespace fs = filesystem;

struct singlyNode{
    string fileName;
    string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};

struct doublyNode
{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};

class Master{
    private:
        doublyNode* commitHead; //current directory

    public: 
        //The folowing functions are just shells
        //They may need more arguments or change of type from void
        Master();
        ~Master();
        void init();
        void remove(string filename);
        void checkout(int commitNumber);
        int commit();
        void add(string filename);
        void status();
};

#endif