#ifndef MINIGIT_H
#define MINIGIT_H

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

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
        Master();
        ~Master();
        void init();
        void add(string filename);
        void remove(string fileame);
        void checkout();
        void commit();
};

#endif