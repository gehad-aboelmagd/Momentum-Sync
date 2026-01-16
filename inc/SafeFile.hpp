#include <iostream>
#include <string>
#include <optional>
#include <fcntl.h>
#include <unistd.h>

class SafeFile
{
private:
    int fd = -1;
public:
    // SafeFile() = delete;
    SafeFile(const std::string &path);
    
    SafeFile(const SafeFile &ref) = delete;
    
    SafeFile & operator=(const SafeFile &ref) = delete; 

    SafeFile(SafeFile &&ref);
    
    SafeFile & operator=(SafeFile &&ref);

    std::optional<std::string> readFile();

    int getState();
    
    ~SafeFile();
};