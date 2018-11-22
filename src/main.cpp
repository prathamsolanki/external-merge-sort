#include "iostream"
#include <string.h>

#include "streams_demo.cpp"

#define DATA_DIRECTORY "../data/"

using namespace std;

string get_filename(void);
char get_io_mechanism(void);

int main(int argc, char *argv[])
{
    while(1) {
        char stream_choice;
        cout << "1) Input Stream\n2) Output Stream\n3) Exit" << endl;
        cin >> stream_choice;

        if (stream_choice == '1') {
            string filename_full = DATA_DIRECTORY + get_filename();
            const char *filename = filename_full.c_str();

            char io_mechanism = get_io_mechanism();
            
            InputStream in(filename, io_mechanism);
            in.open_file();
            in.read_file();
            in.close_file();
            cout << endl;
        } else if (stream_choice== '2') {
            string filename_full = DATA_DIRECTORY + get_filename();
            const char *filename = filename_full.c_str();

            char io_mechanism = get_io_mechanism();

            OutputStream out(filename, io_mechanism);
            out.create_file();
            out.write_file();
            out.close_file();
            cout << endl;
        } else {
            return 0;
        }
    }
}

string get_filename(void) {
    string filename_string;
    cout << "Enter filename: " << endl;
    cin >> filename_string;
    return filename_string;
}

char get_io_mechanism(void) {
    char c;
    cout << "1) Data Stream\n2) Buffered Stream" << endl;
    cin >> c;
    return c;
}
