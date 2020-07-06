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
std::string getFileExt(const std::string& s) {

   size_t i = s.rfind('.', s.length());
   if (i != std::string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}

void open(std::string filePath) {
    const char* destinationName = "org.sdbuscpp.manager";
    const char* objectPath = "/org/sdbuscpp/manager";
    std::string extension = getFileExt(filePath); // автоматизировать
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
}