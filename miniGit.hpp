#ifndef MINIGIT_H
#define MINIGIT_H

#include <iostream>
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

#endif