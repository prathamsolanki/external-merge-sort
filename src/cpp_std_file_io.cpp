#include "iostream"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CppStdFileIO {
    private:
        const char *filename;
        FILE *pFile;

    public:
        CppStdFileIO(const char *f) {
            filename = f;
        }

        void open_file(void) {
            pFile = fopen(filename, "r");

            if (pFile == NULL) {
                cout << "can't open file" << endl;
            }
        }

        void read_file(void) {
            fseek (pFile , 0 , SEEK_END);
            long lSize = ftell (pFile);
            rewind (pFile);

            char * buffer = (char*) malloc (sizeof(char)*lSize);
            if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

            size_t result = fread (buffer,1,lSize,pFile);
            if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

            close_file();

            for (int i = 0; i < result; i++) {
                cout << buffer[i] << endl;
            }

            free (buffer);
        }

        void create_file(void) {
            pFile = fopen(filename, "wb");

            if (pFile == NULL) {
                cout << "can't open file" << endl;
            }}

        void write_file(void) {
            char buffer[] = {'2', '5'};
            fwrite(buffer, sizeof(char), sizeof(buffer), pFile);
            close_file();
        }

        void close_file() {
            fclose(pFile);
        }
};
