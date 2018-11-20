#include "iostream"

#include "one_element_at_time.cpp"

using namespace std;

class InputStream {
    private:
        const char *filename;
        char *io_mechanism;

    public:
        InputStream(const char *f, char *m) {
            filename = f;
            io_mechanism = m;
        }

        void open_file(void) {
            obj.open_file();
        }

        void read_file(void) {
            obj.read_file();
        }

        bool end_of_stream(void){
            return true;
        }
};

class OutputStream {
    private:
        const char *filename;
        char *io_mechanism;

    public:
        OutputStream(const char *f, char *m) {
            filename = f;
            io_mechanism = m;
        }

        void create_file(void) {
            obj.create_file();
        }

        void write_file(void) {
            obj.write_file();
        }

        void close_file(void) {
            obj.close_file();
        }
};
