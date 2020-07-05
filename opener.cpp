#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

void gotServices(std::vector<std::string> services, std::unique_ptr<sdbus::IProxy>& proxy, const std::string& filePath, const std::string& interfaceName)
{
    // вывод и выбор нужного для открытия сервиса
    std::cout << "Select service to open (type number):\n";
    for (int i = 0; i < services.size(); i++) {
        std::cout << i << ". " << services[i] << "\n";
    }
    int serviceNum;
    std::cin >> serviceNum;
    while (serviceNum >= services.size() || serviceNum < 0) {
        std::cout << "No such service.\nTry again:\n";
        std::cin >> serviceNum;
    }
    proxy->callMethod("open").onInterface(interfaceName).withArguments(filePath, services[serviceNum]);
}

int main(int argc, char *argv[])
{
    // Create proxy object for the manager object on the server side
    const char* destinationName = "org.sdbuscpp.manager";
    const char* objectPath = "/org/sdbuscpp/manager";
    const char* filePath = "./file.json"; // file to open
    const char* extension = "json"; // автоматизировать
    auto managerProxy = sdbus::createProxy(destinationName, objectPath);
    const char* interfaceName = "org.sdbuscpp.Manager";
    managerProxy->uponSignal("sendServices").onInterface(interfaceName).call([&managerProxy, &filePath, &interfaceName](std::vector<std::string> services){ gotServices(services, managerProxy, filePath, interfaceName); }); 
    managerProxy->uponSignal("done").onInterface(interfaceName).call([](){}); 
    managerProxy->finishRegistration();
    {
        try
        {
            managerProxy->callMethod("getServices").onInterface(interfaceName).withArguments(extension);
        }
        catch(const sdbus::Error& e)
        {
            std::cerr << "Got an error " << e.getName() << " with message " << e.getMessage() << std::endl;
        }
    }
    
    sleep(1);
    
    return 0;
}