#include "iostream"

#include "data_stream.cpp"
#include "buffered_stream.cpp"
#include "buffered_stream_fixed_size_buffer.cpp"

using namespace std;

class InputStream {
    private:
        const char *filename;
        char io_mechanism;

    public:
        InputStream(const char *f, char m) {
            filename = f;
            io_mechanism = m;
        }

        void open_file(void) {
            DataStream obj(filename);
            obj.open_file();
        }

        void read_file(void) {
            DataStream obj(filename);
            obj.read_file();
        }

        void close_file(void) {
            DataStream obj(filename);
            obj.close_file();
        }

        bool end_of_stream(void){
            return true;
        }
};

class OutputStream {
    private:
        const char *filename;
        char io_mechanism;

    public:
        OutputStream(const char *f, char m) {
            filename = f;
            io_mechanism = m;
        }

        void create_file(void) {
            DataStream obj(filename);
            obj.create_file();
        }

        void write_file(void) {
            DataStream obj(filename);
            obj.write_file();
        }

        void close_file(void) {
            DataStream obj(filename);
            obj.close_file();
        }
};
