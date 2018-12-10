#include "iostream"
#include <stdlib.h>
#include <fstream>
#include <string.h>

using namespace std;

class LimitedBufferSize {
    public:
        void read_file(const char *filename, int buffer_size) {
            char *buffer = (char*) malloc (sizeof(char)*buffer_size);

            ifstream inFile(filename);

            while (inFile) {
                inFile.read(buffer, buffer_size);
            }

            inFile.close();
            free(buffer);
        }

        void write_file(const char *filename, int buffer_size) {
            char *buffer = (char*) malloc (sizeof(char)*buffer_size);
            memset(buffer, '4', sizeof(char)*buffer_size);

            fstream outFile;
            outFile.open(filename, fstream::out | fstream::app);

            outFile.write(buffer, buffer_size);

            outFile.close();
            free(buffer);
        }
};
