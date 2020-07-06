#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
void registerService(std::vector<std::string> formats, std::string name, std::string path) {
    const char* destinationName = "org.sdbuscpp.manager";
    const char* objectPath = "/org/sdbuscpp/manager";
    auto managerProxy = sdbus::createProxy(destinationName, objectPath);
    const char* interfaceName = "org.sdbuscpp.Manager";
    managerProxy->finishRegistration();
    try
        {
            managerProxy->callMethod("registerService").onInterface(interfaceName).withArguments(formats, name, path);
            std::cout << "registration done.\n";
        }
        catch(const sdbus::Error& e)
        {
            std::cerr << "Got an error " << e.getName() << " with message " << e.getMessage() << std::endl;
        }
}