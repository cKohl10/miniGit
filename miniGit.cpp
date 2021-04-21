#include "miniGit.hpp"

using namespace std;

Master::Master()
{

}
Master::~Master()
{
    
}

void Master::init()
{
    fs::create_directory(".minigit");
    doublyNode * node = new doublyNode;
    commitHead = node;
}
void Master::add()
{

}
void Master::remove()
{

}
void Master::checkout()
{

}
void Master::commit()
{

}