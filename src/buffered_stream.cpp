#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class BufferedStream {
    public:
        FILE* open_file(const char *filename) {
            return fopen(filename, "r");
        }

        void read_file(FILE *pFile) {
            fseek (pFile , 0 , SEEK_END);
            long lSize = ftell (pFile);
            rewind (pFile);

            char *buffer = (char*) malloc (sizeof(char)*lSize);

            size_t bytes_read = fread (buffer,1,lSize,pFile);

            free(buffer);
        }

        FILE* create_file(const char *filename) {
            return fopen(filename, "wb");
        }

        void write_file(FILE *pFile, int N) {
            char *buffer = (char*) malloc (sizeof(char)*N);
            memset(buffer, '4', sizeof(char)*N);
            fwrite(buffer, sizeof(char), sizeof(char)*N, pFile);
        }

        void close_file(FILE *pFile) {
            fclose(pFile);
        }
};
