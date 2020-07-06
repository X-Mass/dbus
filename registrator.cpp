#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

void main(int argc, char *argv[]) {
    // Create proxy object for the manager object on the server side
    const char* destinationName = "org.sdbuscpp.manager";
    const char* objectPath = "/org/sdbuscpp/manager";
    auto managerProxy = sdbus::createProxy(destinationName, objectPath);
    const char* interfaceName = "org.sdbuscpp.Manager";
    managerProxy->finishRegistration();
    std::vector<std::vector<std::string>> formatsArr = {{"json", "pdf"}, {"txt","json"}, {"json", "doc"}};
    std::vector<std::string> serviceNames = {"Citius", "Altius", "Fortius"};
    std::vector<std::string> servicePaths = {"services/Citius", "services/Altius", "services/Fortius"};
    for (int i = 0; i < serviceNames.size(); i++)
    {
        try
        {
            managerProxy->callMethod("registerService").onInterface(interfaceName).withArguments(formatsArr[i], serviceNames[i], servicePaths[i]);
            std::cout << "registration " << i << " done. " << formatsArr[i][0]<<"\n";
        }
        catch(const sdbus::Error& e)
        {
            std::cerr << "Got an error " << e.getName() << " with message " << e.getMessage() << std::endl;
        }
    }

    return 0;
}