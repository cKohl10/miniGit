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

};

#endif