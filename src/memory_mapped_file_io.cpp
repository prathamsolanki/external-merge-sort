#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "iostream"

using namespace std;

class MemoryMappedFileIO {
    public:
        void read_file(const char *filename, int file_size, int buffer_size) {
            int fd = open(filename, O_RDONLY, S_IRUSR | S_IWUSR);
            int *map;

            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            int size_to_read;

            for (int n = 0; n < number_of_passes; n++) {
                if (n == number_of_passes - 1) {
                    size_to_read = file_size - (buffer_size * n);
                } else {
                    size_to_read = buffer_size;
                }

                map = (int*)(mmap(NULL, size_to_read * sizeof(int), PROT_READ, MAP_PRIVATE, fd, buffer_size * sizeof(int) * n));

                munmap(map, size_to_read * sizeof(int));
            }

            close(fd);
        }

        void write_file(const char *filename, int file_size, int buffer_size) {
            int fd = open(filename, O_RDWR, S_IRUSR | S_IWUSR);
            int *map;

            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            int size_to_write;

            for (int n = 0; n < number_of_passes; n++) {
                if (n == number_of_passes - 1) {
                    size_to_write = file_size - (buffer_size * n);
                } else {
                    size_to_write = buffer_size;
                }

                map = (int*)(mmap(NULL, size_to_write * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, buffer_size * sizeof(int) * n));

                for (int i = 0; i < size_to_write; i++) {
                    map[i] = rand();
                }

                munmap(map, size_to_write * sizeof(int));
            }

            close(fd);
        }
};
