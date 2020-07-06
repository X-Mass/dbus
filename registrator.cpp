#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include "register.cpp"

int main(int argc, char *argv[]) {
    std::vector<std::vector<std::string>> formatsArr = {{"json", "pdf"}, {"txt","json"}, {"json", "doc"}};
    std::vector<std::string> serviceNames = {"Citius", "Altius", "Fortius"};
    std::vector<std::string> servicePaths = {"services/Citius", "services/Altius", "services/Fortius"};
    for (int i = 0; i < serviceNames.size(); i++)
    {
        registerService(formatsArr[i], serviceNames[i], servicePaths[i]);
    }

    return 0;
}