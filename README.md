# dbus
dbus first steps using sdbus-cpp (high-level library working with systemd)  
# requirements
git  
cmake  
g++  
pkg-config  
libsystemd-dev  
sdbus-cpp  
You can install all of these using apt-get  
# How to use an example
Install all requirements  
Copy org.sdbuscpp.manager.service to ${datadir}/dbus-1/services  
cmake .  
make  
./server (to run server which can register apps, tell what apps can open given extension and open file with this app)  
./registrator (to register some example services)  
./opener (to make a request on available apps to open an example file "file.json" and select prefered app)  
# API USAGE
start ./server\
include register.cpp\
now you can use register(std::vector<std::string> formats, std::string name, std::string path)\
@param formats contains formats to add.\
@param name contains name of application.\
@param path contains application path to future use with exec.\
@return nothing.\
\
include open.cpp\
now you can use open(std::string filePath)\
@param filePath contains path to file you want to open.\
@return nothing.\
# Comments
I heve never seen such a lack of examples of full projects. Just isoleted parts of code given in different sources.  
I think, that this service is totally irrational and could be much better with correct use of dbus, however examples are needed.
