#include "iostream"
#include <stdlib.h>
#include <fstream>
#include <string.h>

using namespace std;

class LimitedBufferSize {
    private:
        int buffer_size;
        char * buffer = (char*) malloc (sizeof(char)*buffer_size);

    public:
        LimitedBufferSize(int s) {
            buffer_size = s;
        }

        void read_file(const char *filename) {
            ifstream inFile(filename);

            while (inFile) {
                inFile.read(buffer, buffer_size);
            }

            inFile.close();
        }

        void write_file(const char *filename) {
            fstream outFile;
            outFile.open(filename, fstream::out | fstream::app);

            memset(buffer, '4', sizeof(buffer));

            outFile.write(buffer, buffer_size);

            outFile.close();
        }
};
