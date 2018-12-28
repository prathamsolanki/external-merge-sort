#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iostream"

using namespace std;

class BufferedStream {
    public:
        FILE* open_file(const char *filename) {
            return fopen(filename, "rb");
        }

        void read_file(FILE *pFile) {
            fseek (pFile , 0 , SEEK_END);
            long lSize = ftell (pFile);
            rewind (pFile);

            int num_elements = lSize / sizeof(int);

            int *i = (int*)malloc(num_elements * sizeof(int));

            size_t bytes_read = fread (i, sizeof(int), num_elements, pFile);
        }

        FILE* create_file(const char *filename) {
            return fopen(filename, "wb");
        }

        void write_file(FILE *pFile, int N) {
            int *i = (int*)malloc(N * sizeof(int));
            memset(i, rand(), N * sizeof(int));
            fwrite(i, sizeof(int), N, pFile);
        }

        void close_file(FILE *pFile) {
            fclose(pFile);
        }
};
