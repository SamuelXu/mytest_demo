#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>

using namespace std;

uint64_t filesize(const string& path)
{
    uint64_t size;
    uint32_t fd;

    fd = open(path.c_str(), O_RDONLY);
    size = lseek(fd, 0, SEEK_END);
    close(fd);

    return size;
}

int main(int argc, char* argv[])
{
    uint64_t size = 0;
    string path(argv[1]);

    size = filesize(path);
    cout << "filesize: " << size << endl;

    return 0;
}
