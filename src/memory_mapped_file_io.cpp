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
            int fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            int *map;

            struct stat sb;
            fstat(fd, &sb);
            cout << "file size: " << sb.st_size << endl;

            cout << "buffer size: " << buffer_size * sizeof(int) << endl;

            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            cout << "number of passes: " << number_of_passes << endl;

            //int *map = (int*)(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));

            for (int n = 0; n < number_of_passes; n++) {
                map = (int*)(mmap(NULL, buffer_size * sizeof(int), PROT_READ, MAP_PRIVATE, fd, buffer_size * sizeof(int) * n));
                //for (int i = 0; i < file_size; i++) {
                //    cout << map[i];
                //}
                munmap(map, buffer_size * sizeof(int));
            }

            close(fd);
        }

        void write_file(const char *filename, int file_size, int buffer_size) {
            int fd = open(filename, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
            int *map;

            int number_of_passes = ceil((float)file_size / (float)buffer_size);

            for (int n = 0; n < number_of_passes; n++) {
                map = (int*)(mmap(NULL, buffer_size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, buffer_size * sizeof(int) * n));
                for (int i = 0; i < buffer_size; i++) {
                    map[i] = rand();
                }
                munmap(map, buffer_size * sizeof(int));
            }

            close(fd);
        }
};
