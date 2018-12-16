#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

class MemoryMappedFileIO {
    public:
        void read_file(const char *filename, int file_size) {
            int fd = open(filename, O_RDONLY, S_IRUSR);

            char *file_in_memory = static_cast<char*>(mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0));

            munmap(file_in_memory, file_size);
            close(fd);
        }

        void write_file(const char *filename, int file_size) {
            int fd = open(filename, O_RDWR, S_IRUSR);

            char *file_in_memory = static_cast<char*>(mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

            munmap(file_in_memory, file_size);
            close(fd);
        }
};
