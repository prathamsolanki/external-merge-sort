#include "iostream"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CppStdFileIO {	
	public:
		void readFile(const char * filename) {
			FILE *pFile = fopen(filename, "r");

			if (pFile == NULL) {
				cout << "can't open file" << endl;
			}
			else {
				fseek (pFile , 0 , SEEK_END);
				long lSize = ftell (pFile);
				rewind (pFile);

				char * buffer = (char*) malloc (sizeof(char)*lSize);
				if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

				size_t result = fread (buffer,1,lSize,pFile);
				if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

				fclose (pFile);

				for (int i = 0; i < result; i++) {
					cout << buffer[i] << endl;
				}

				free (buffer);
			}
		}

		void writeFile(const char * filename) {
			FILE *pFile = fopen(filename, "a");

			if (pFile == NULL) {
				cout << "can't open file" << endl;
			}
			else {
				fclose (pFile);
			}
		}
};
