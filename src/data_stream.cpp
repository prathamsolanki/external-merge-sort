#include "iostream"
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class DataStream {
    public:
        int open_file(const char *filename) {
            return open(filename, O_RDONLY);
        }

        bool read_next(int file) {
            char c;
            ssize_t bytes_read = read(file, (void*)&c, 1);
            if (bytes_read == 0) return true;
            else return false;
        }

        int create_file(const char *filename) {
            return open (filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR, O_RDWR);
        }

        void write_file(int file) {
            char c = '4';
            write(file, (void*)&c, 1);
        }

        void close_file(int file) {
            close(file);
        }
};
