#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <map>
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <iostream>
sdbus::IObject* g_manager{};
std::map<std::string, std::vector<std::string>> formats;
std::map<std::string, std::string> addresses; 

void registerService(const std::vector<std::string> formatsToOpen, std::string serviceName, std::string servicePath)
{
    if (formatsToOpen.empty() || serviceName.empty() || servicePath.empty())
        throw sdbus::Error("org.sdbuscpp.Manager.Error", "Wrong arguements");
    if (addresses.find(serviceName) != addresses.end())
        throw sdbus::Error("org.sdbuscpp.Manager.Error", "Service already exists. Delete before reinstalling");

    for (auto format : formatsToOpen) {
        formats[format].push_back(serviceName); //надо ли инициализировать, когда впервые делаешь?
    }
    addresses[serviceName]=servicePath;
}

std::vector<std::string> getServices(std::string format)
{
    if (format.empty())
        throw sdbus::Error("org.sdbuscpp.Manager.Error", "Wrong arguements");
    std::vector<std::string> result = formats[format]; //если ключа нет, всё плохо?
    const char* interfaceName = "org.sdbuscpp.Manager";
    g_manager->emitSignal("sendServices").onInterface(interfaceName).withArguments(result);
    return result;
}

void open(const std::string& filePath, const std::string& serviceName) {
    std::string str = addresses[serviceName];
    char* const args[] = {const_cast<char*> (str.c_str()), const_cast<char*> (filePath.c_str()), NULL}; // Глебас, тут ругаются
    const char* interfaceName = "org.sdbuscpp.Manager";
    std::cout << "1\n";
    g_manager->emitSignal("done").onInterface(interfaceName).withArguments(NULL);
    std::cout << "2\n";
    // execvp(args[0],args);
    std::cout << "3\n";

}

int main(int argc, char *argv[])
{
    // Create D-Bus connection to the system bus and requests name on it.
    const char* serviceName = "org.sdbuscpp.manager";

    auto connection = sdbus::createSystemBusConnection(serviceName);

    // Create manager D-Bus object.
    const char* objectPath = "/org/sdbuscpp/manager";
    auto manager = sdbus::createObject(*connection, objectPath);
    
    g_manager = manager.get();
    
    // Register D-Bus methods and signals on the manager object, and exports the object.
    const char* interfaceName = "org.sdbuscpp.Manager";
    manager->registerMethod("registerService").onInterface(interfaceName).implementedAs(&registerService);
    manager->registerMethod("open").onInterface(interfaceName).implementedAs(&open);
    manager->registerMethod("getServices").onInterface(interfaceName).implementedAs(&getServices);
    manager->registerSignal("sendServices").onInterface(interfaceName).withParameters<std::vector<std::string>>();
    manager->registerSignal("done").onInterface(interfaceName).withParameters();
    manager->finishRegistration();

    // Run the loop on the connection.
    connection->enterEventLoop();
}