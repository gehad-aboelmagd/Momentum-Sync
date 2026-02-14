#include "SafeFile.hpp"

SafeFile::SafeFile(const std::string &path)
{
    fd = open(path.c_str(), O_RDONLY);
    if(fd == -1)
    {
        std::cerr << "Unable to open the file\n";
    }
}

SafeFile::SafeFile(SafeFile &&ref)
{
    fd = ref.fd;
    ref.fd = -1;
}

SafeFile & SafeFile::operator=(SafeFile &&ref)
{
    this->~SafeFile();
    fd = ref.fd;
    ref.fd = -1;

    return *this;
}

std::optional<std::string> SafeFile::readFile()
{    
    if(fd == -1)
    {
        return std::nullopt;
    }

    std::string buff;

    char c = '\0';
    while(c != '\n')
    {
        if(read(fd, (void *)&c, 1) == -1)
        {
            return std::nullopt;
        }
        
        buff.append(std::initializer_list<char>{c});
    }

    return buff;
}

int SafeFile::getState()
{
    return fd;
}

SafeFile::~SafeFile()
{
    if(fd == -1)
    {
        return;
    }

    if(close(fd) == -1)
    {
        std::cerr << "Unable to clsoe the file\n";
    }
}