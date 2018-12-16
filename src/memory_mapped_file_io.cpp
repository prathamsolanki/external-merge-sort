#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

class MemoryMappedFileIO {
    public:
        void read_file(const char *filename, int file_size, int buffer_size) {
            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            int fd = open(filename, O_RDONLY, S_IRUSR);

            char *file_in_memory;

            for (int n = 0; n < number_of_passes; n++) {
                file_in_memory = static_cast<char*>(mmap(NULL, buffer_size, PROT_READ, MAP_PRIVATE, fd, buffer_size*n));
                munmap(file_in_memory, file_size);
            }

            close(fd);
        }

        void write_file(const char *filename, int file_size, int buffer_size) {
            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            int fd = open(filename, O_RDWR, S_IRUSR);

            char *file_in_memory;

            for (int n = 0; n < number_of_passes; n++) {
                file_in_memory = static_cast<char*>(mmap(NULL, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buffer_size*n));
                munmap(file_in_memory, file_size);
            }

            close(fd);
        }
};
