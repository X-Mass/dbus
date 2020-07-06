#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include "./serveropen.cpp"
int main(int argc, char *argv[])
{
    open("file.json");
    
    return 0;
}