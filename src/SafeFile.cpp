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

    int size = lseek(fd, 0, SEEK_END);
    if(size == -1)
    {
        return std::nullopt;
    }

    if(lseek(fd, 0, SEEK_SET) == -1)
    {
        return std::nullopt;
    }

    std::string buff;
    buff.resize(size);
    if(read(fd, (void *)buff.c_str(), size) == -1)
    {
        return std::nullopt;
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