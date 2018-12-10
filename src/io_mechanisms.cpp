#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <math.h>

#include "data_stream.cpp"
#include "buffered_stream.cpp"
#include "buffered_stream_fixed_size_buffer.cpp"

using namespace std;

class IOMechanisms {
    private:
        int N[12] = {10000, 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000};

    public:
        void benchmark_data_stream(void) {
            DataStream obj;

            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            for (int i = 0; i < 12; i++) {
                FILE* in = fopen(input_file, "w");
                for (int n = 0; n < N[i]; n++) {
                    fprintf(in, "%d", rand()%10);
                }
                fclose(in);

                int file = obj.open_file(input_file);

                bool end_of_stream = false;

                clock_t begin = clock();
                while (end_of_stream != true) end_of_stream = obj.read_next(file);
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                obj.close_file(file);
                unlink(input_file);
            }

            cout << endl;

            for (int i = 0; i < 12; i++) {
                int file = obj.create_file(output_file);

                clock_t begin = clock();
                for (int n = 0; n < N[i]; n++) {
                    obj.write_file(file);
                }
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                obj.close_file(file);
                unlink(output_file);
            }
        }

        void benchmark_buffered_stream(void) {
            BufferedStream obj;

            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            for (int i = 0; i < 12; i++) {
                FILE* in = fopen(input_file, "w");
                for (int n = 0; n < N[i]; n++) {
                    fprintf(in, "%d", rand()%10);
                }
                fclose(in);

                FILE *pFile = obj.open_file(input_file);

                clock_t begin = clock();
                obj.read_file(pFile);
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                obj.close_file(pFile);
                unlink(input_file);
            }

            cout << endl;

            for (int i = 0; i < 10; i++) {
                FILE *pFile = obj.create_file(output_file);

                clock_t begin = clock();
                obj.write_file(pFile, N[i]);
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                obj.close_file(pFile);
                unlink(output_file);
            }
        }

        void benchmark_buffered_stream_fixed_size(void) {
            int buffer_size = 1024;
            LimitedBufferSize obj(buffer_size);

            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            for (int i = 0; i < 12; i++) {
                FILE* in = fopen(input_file, "w");
                for (int n = 0; n < N[i]; n++) {
                    fprintf(in, "%d", rand()%10);
                }
                fclose(in);

                clock_t begin = clock();
                obj.read_file(input_file);
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                unlink(input_file);
            }

            cout << endl;

            for (int i = 0; i < 12; i++) {
                int number_of_passes = ceil((float)N[i] / (float)buffer_size);

                clock_t begin = clock();
                for (int n = 0; n < number_of_passes; n++) {
                    obj.write_file(output_file);
                }
                clock_t end = clock();

                double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << elapsed_secs << endl;

                unlink(output_file);
            }
        }
};
