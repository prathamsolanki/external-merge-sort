#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iostream"

using namespace std;

class LimitedBufferSize {
    public:
        FILE* open_file(const char *filename) {
            return fopen(filename, "rb");
        }

        void read_file(FILE *pFile, int buffer_size) {
            int *buffer = (int*)malloc(buffer_size * sizeof(int));

            fread (buffer, sizeof(int), buffer_size, pFile);
        }

        FILE* create_file(const char *filename) {
            return fopen(filename, "wb");
        }

        void write_file(FILE *pFile, int buffer_size) {
            int *i = (int*)malloc(buffer_size * sizeof(int));
            memset(i, rand(), buffer_size * sizeof(int));
            fwrite(i, sizeof(int), buffer_size, pFile);
        }

        void close_file(FILE *pFile) {
            fclose(pFile);
        }
};
