#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <math.h>

#include "data_stream.cpp"
#include "buffered_stream.cpp"
#include "buffered_stream_fixed_size_buffer.cpp"
#include "memory_mapped_file_io.cpp"
#include "external_merge_sort.cpp"

using namespace std;

class Benchmark {
    private:
        clock_t begin;
        clock_t end;
        double elapsed_secs;
        int N[12] = {10000, 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000};
        int D[8] = {3, 4, 5, 6, 7, 8, 9, 10};

    public:
        void benchmark_data_stream(void) {
            DataStream obj;

            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            FILE *in;
            int file;
            bool end_of_stream;

            for (int i = 0; i < 12; i++) {
                in = fopen(input_file, "w");
                for (int n = 0; n < N[i]; n++) {
                    fprintf(in, "%d", rand()%10);
                }
                fclose(in);

                file = obj.open_file(input_file);

                end_of_stream = false;

                begin = clock();
                while (end_of_stream != true) end_of_stream = obj.read_next(file);
                end = clock();

                elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(R)"  << "N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                obj.close_file(file);
                unlink(input_file);
            }

            cout << endl;

            for (int i = 0; i < 12; i++) {
                file = obj.create_file(output_file);

                begin = clock();
                for (int n = 0; n < N[i]; n++) {
                    obj.write_file(file);
                }
                end = clock();

                elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(W)"  << "N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                obj.close_file(file);
                unlink(output_file);
            }
        }

        void benchmark_buffered_stream(void) {
            BufferedStream obj;

            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            FILE *in;
            FILE *pFile;

            for (int i = 0; i < 12; i++) {
                in = fopen(input_file, "w");
                for (int n = 0; n < N[i]; n++) {
                    fprintf(in, "%d", rand()%10);
                }
                fclose(in);

                pFile = obj.open_file(input_file);

                begin = clock();
                obj.read_file(pFile);
                end = clock();

                elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(R)"  << "N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                obj.close_file(pFile);
                unlink(input_file);
            }

            cout << endl;

            for (int i = 0; i < 12; i++) {
                pFile = obj.create_file(output_file);

                begin = clock();
                obj.write_file(pFile, N[i]);
                end = clock();

                elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(W)"  << "N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                obj.close_file(pFile);
                unlink(output_file);
            }
        }

        void benchmark_buffered_stream_fixed_size(void) {
            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            int buffer_size;
            FILE *in;
            int number_of_passes;

            for (int b = 0; b < 5; b++) {
                buffer_size = 1000 * pow(10, b);
                LimitedBufferSize obj;

                for (int i = 0; i < 12; i++) {
                    in = fopen(input_file, "w");
                    for (int n = 0; n < N[i]; n++) {
                        fprintf(in, "%d", rand()%10);
                    }
                    fclose(in);

                    begin = clock();
                    obj.read_file(input_file, buffer_size);
                    end = clock();

                    elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(R)"  << "b: " << buffer_size << " N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                    unlink(input_file);
                }

                cout << endl;

                for (int i = 0; i < 12; i++) {
                    number_of_passes = ceil((float)N[i] / (float)buffer_size);

                    begin = clock();
                    for (int n = 0; n < number_of_passes; n++) {
                        obj.write_file(output_file, buffer_size);
                    }
                    end = clock();

                    elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(W)"  << "b: " << buffer_size << " N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                    unlink(output_file);
                }

                cout << endl;
            }
        }

        void benchmark_memory_mapped_file_io(void) {
            char input_file[] = "../data/input.txt";
            char output_file[] = "../data/output.txt";

            int buffer_size;

            MemoryMappedFileIO obj;
            for (int b = 0; b < 5; b++) {
                buffer_size = 1000 * pow(10, b);

                for (int i = 0; i < 12; i++) {
                    begin = clock();
                    obj.read_file(input_file, N[i], buffer_size);
                    end = clock();

                    elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(R)"  << "b: " << buffer_size << " N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                    unlink(input_file);
                }

                cout << endl;

                for (int i = 0; i < 12; i++) {
                    begin = clock();
                    obj.write_file(output_file, N[i], buffer_size);
                    end = clock();

                    elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(W)"  << "b: " << buffer_size << " N: " << N[i] << " Elapsed Time: " << elapsed_secs << endl;

                    unlink(output_file);
                }

                cout << endl;
            }
        }

        void benchmark_external_merge_sort(void) {
            char input_file[] = "../data/input.txt"; 
            int buffer_size;
            FILE *in;

            MemoryMappedFileIO obj;
            for (int b = 0; b < 5; b++) {
                buffer_size = 1000 * pow(10, b);
                for (int n = 0; n < 3; n++) {
                    in = fopen(input_file, "w");
                    for (int i = 0; i < N[n]; i++) { 
                        fprintf(in, "%d", rand()% 10); 
                    }
                    fclose(in);

                    for (int d: D) {
                        int num_sublists = ceil(float(N[n])/float(buffer_size));

                        begin = clock();
                        externalSort(input_file, N[n], num_sublists, buffer_size, d);
                        end = clock();

                        elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                        cout << "(E)"  << "b: " << buffer_size << " N: " << N[n] << " d: " << d << " Elapsed Time: " << elapsed_secs << endl;

                    }

                    unlink(input_file);
                }
            }
        }
};
