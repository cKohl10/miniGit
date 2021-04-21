#ifndef MINIGIT_H
#define MINIGIT_H

#include <iostream>
#include <filesystem>
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
        doublyNode* commitHead;

    public: 
        //The folowing functions are just shells
        //They may need more arguments or change of type from void
        void init();
        void add();
        void remove();
        void checkout();
        void commit();
};

#endif