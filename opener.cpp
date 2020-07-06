#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include "open.cpp"
int main(int argc, char *argv[])
{
    open("file.json");
    
    sleep(1);
    
    return 0;
}