#include "iostream"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class LimitedBufferSize {
    private:
        const char *filename;
        int file;
        int buffer_size;
        char * buffer = (char*) malloc (sizeof(char)*buffer_size);

    public:
        LimitedBufferSize(const char *f, int s) {
            filename = f;
            buffer_size = s;
        }

        void open_file(void) {
            file = open(filename, O_RDONLY);

            if (file < 0) cout << "can't open file" << endl;
        }

        void read_file(void) {
            ssize_t isLastElement = 1;

            while (isLastElement != 0) {
                memset(buffer, '\n', buffer_size);
                for (int i = 0; i < buffer_size; i++){
                    isLastElement = read(file, (void*)&buffer[i], 1);
                    if (isLastElement == 0) break;
                }
                for (int i = 0; i < buffer_size; i++){
                    if (buffer[i] == '\n') break;
                    cout << buffer[i] << endl;
                }
            }

            close_file();
        }

        void create_file() {
            file = open (filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

            if (file < 0) cout << "can't create file" << endl;
        }

        void write_file() {
            int file = open(filename, O_WRONLY | O_APPEND);

            cout << "Enter Elements to enter: " << endl;
            for (int i = 0; i < buffer_size; i++) {
                cin >> buffer[i];
            }

            for (int i = 0; i < buffer_size; i++) {
                ssize_t successfullyWritten = write(file, (void*)&buffer[i], 1);
                if (successfullyWritten == 0) cout << "couldn't be written" << endl;
                else cout << "successfully written " << buffer[i] << endl;
            }
        }

        void close_file(void) {
            close(file);
        }
};
