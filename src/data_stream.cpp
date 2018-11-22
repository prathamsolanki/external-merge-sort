#include "iostream"
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class DataStream {
    private:
        const char *filename;
        int file;

    public:
        DataStream(const char *f) {
            filename = f;
        }

        void open_file(void) {
            file = open(filename, O_RDONLY);

            if (file < 0) cout << "can't open file" << endl;
        }

        void read_file(void) {
            char c;
            ssize_t isLastElement = 1;
            while (isLastElement != 0) {
                isLastElement = read(file, (void*)&c, 1);
                cout << c;
            }
            cout << endl;
        }

        void create_file() {
            file = open (filename, O_WRONLY | O_CREAT | O_TRUNC, O_RDWR);

            if (file < 0) cout << "can't create file" << endl;
        }

        void write_file() {
            int file = open(filename, O_WRONLY | O_APPEND);

            char c;
            cout << "Enter element to enter: " << endl;
            cin >> c;
            ssize_t successfullyWritten = write(file, (void*)&c, 1);
            if (successfullyWritten == 0) cout << "couldn't be written" << endl;
            else cout << "successfully written " << c << endl;
        }

        void close_file(void) {
            close(file);
        }
};
