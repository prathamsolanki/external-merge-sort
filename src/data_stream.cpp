#include "iostream"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <tuple>
#include <stdio.h>

using namespace std;

class DataStream {
    public:
        int open_file(const char *filename) {
            return open(filename, O_RDONLY);
        }

        tuple<int, bool> read_next(int file) {
            int i;
            ssize_t bytes_read = read(file, &i, sizeof(i));
            bool end_of_stream;
            if (bytes_read == 0) end_of_stream = true;
            else end_of_stream = false;

            return make_tuple(i, end_of_stream);
        }

        int create_file(const char *filename) {
            return open (filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR);
        }

        void write_file(int file, int value) {
            write(file, &value, sizeof(value));
        }

        void close_file(int file) {
            close(file);
        }
};
