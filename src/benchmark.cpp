#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
#include <math.h>
#include <tuple>
#include <iostream>
#include <utility>
#include <algorithm>

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
        double elapsed_time;
        double elapsed_time_stl;
        int N[12] = {10000, 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000};
        int B[9] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};
        int D[8] = {3, 4, 5, 6, 7, 8, 9, 10};

    public:
        void benchmark_data_stream(void) {
            DataStream obj;

            char input_file[] = "../data/input";
            char output_file[] = "../data/output";

            FILE *in;
            int file;
            bool end_of_stream;
            int integer;

            for (int n: N) {
                file = open(input_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
                for (int i_n = 0; i_n < n; i_n++) {
                    int value = rand();
                    write(file, &value, sizeof(int));
                }
                close(file);

                file = obj.open_file(input_file);

                end_of_stream = false;

                begin = clock();
                while (true) {
                    tie(integer, end_of_stream) = obj.read_next(file);
                    if (end_of_stream == true) break;
                }
                end = clock();

                elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(R)"  << "N: " << n << " Elapsed Time: " << elapsed_time << endl;

                obj.close_file(file);
                remove(input_file);

                file = obj.create_file(output_file);
                integer = rand();

                begin = clock();
                for (int i_n = 0; i_n < n; i_n++) {
                    obj.write_file(file, integer);
                }
                end = clock();

                elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(W)"  << "N: " << n << " Elapsed Time: " << elapsed_time << endl;

                obj.close_file(file);

                remove(output_file);
            }
        }

        void benchmark_buffered_stream(void) {
            BufferedStream obj;

            char input_file[] = "../data/input";
            char output_file[] = "../data/output";

            int file;
            FILE *pFile;

            for (int n: N) {
                file = open(input_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
                for (int i_n = 0; i_n < n; i_n++) {
                    int value = rand();
                    write(file, &value, sizeof(int));
                }
                close(file);

                pFile = obj.open_file(input_file);

                begin = clock();
                obj.read_file(pFile);
                end = clock();

                elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(R)"  << "N: " << n << " Elapsed Time: " << elapsed_time << endl;

                obj.close_file(pFile);
                remove(input_file);

                pFile = obj.create_file(output_file);

                begin = clock();
                obj.write_file(pFile, n);
                end = clock();

                elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                cout << "(W)"  << "N: " << n << " Elapsed Time: " << elapsed_time << endl;

                obj.close_file(pFile);
                remove(output_file);
            }
        }

        void benchmark_buffered_stream_fixed_size(void) {
            char input_file[] = "../data/input";
            char output_file[] = "../data/output";

            int buffer_size;
            int file;
            FILE *pFile;
            int number_of_passes;

            for (int b: B) {
                LimitedBufferSize obj;

                for (int n: N) {
                    file = open(input_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
                    for (int i_n = 0; i_n < n; i_n++) {
                        int value = rand();
                        write(file, &value, sizeof(int));
                    }
                    close(file);

                    pFile = obj.open_file(input_file);

                    begin = clock();
                    obj.read_file(pFile, b);
                    end = clock();

                    elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(R)"  << "b: " << b << " N: " << n << " Elapsed Time: " << elapsed_time << endl;

                    obj.close_file(pFile);
                    remove(input_file);

                    number_of_passes = ceil((float)n / (float)b);
                    pFile = obj.create_file(output_file);

                    begin = clock();
                    for (int i_np = 0; i_np < number_of_passes; i_np++) {
                        obj.write_file(pFile, b);
                    }
                    end = clock();

                    elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(W)"  << "b: " << b << " N: " << n << " Elapsed Time: " << elapsed_time << endl;

                    obj.close_file(pFile);
                    remove(output_file);

                    cout << endl;
                }
            }
        }

        void benchmark_memory_mapped_file_io(void) {
            char input_file[] = "../data/input";
            char output_file[] = "../data/output";

            int buffer_size;
            int file;

            MemoryMappedFileIO obj;

            for (int b: B) {
                if (b < 4096) continue;
                for (int n: N) {
                    file = open(input_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
                    for (int i_n = 0; i_n < n; i_n++) {
                        int value = rand();
                        write(file, &value, sizeof(int));
                    }
                    close(file);

                    begin = clock();
                    obj.read_file(input_file, n, b);
                    end = clock();

                    elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(R)"  << "b: " << b << " N: " << n << " Elapsed Time: " << elapsed_time << endl;

                    remove(input_file);

                    ofstream ofs(output_file, std::ios::binary | std::ios::out);
                    ofs.seekp((n*sizeof(int)<<20) - 1);
                    ofs.write("", 1);

                    begin = clock();
                    obj.write_file(output_file, n, b);
                    end = clock();

                    elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                    cout << "(W)"  << "b: " << b << " N: " << n << " Elapsed Time: " << elapsed_time << endl;

                    remove(output_file);
                }

                cout << endl;
            }
        }

        void benchmark_external_merge_sort(void) {
            char input_file[] = "../data/input"; 
            int buffer_size;
            int file;

            for (int n: N) {
                file = open(input_file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR);
                for (int i_n = 0; i_n < n; i_n++) {
                    int value = rand();
                    write(file, &value, sizeof(int));
                }
                close(file);

                begin = clock();

                FILE *in = fopen(input_file, "rb");
                int *buf = (int*) malloc (sizeof(int)*n);                
                fread(buf, sizeof(int), n, in);

                sort(buf, buf + n);

                FILE *out = fopen("Sorted", "wb");
                fwrite(buf, sizeof(int), n, out);
                remove("Sorted");

                end = clock();

                elapsed_time_stl = double(end - begin) / (CLOCKS_PER_SEC / 1000);

                for (int b: B) {
                    int num_sublists = ceil(float(n)/float(b));
                    if (num_sublists > 1000) continue;
                    for (int d: D) {
                        begin = clock();
                        external_merge_sort(input_file, n, num_sublists, b, d);
                        end = clock();

                        elapsed_time = double(end - begin) / (CLOCKS_PER_SEC / 1000);
                        cout << "(E)"  << "b: " << b << " N: " << n << " d: " << d << " Elapsed Time: " << elapsed_time << " Elapsed Time (STL): " << elapsed_time_stl << endl;

                        char fileName[10];
                        for (int k = 0; k < num_sublists; k++) {
                            snprintf(fileName, sizeof(fileName), "%d", k);
                            remove(fileName);
                        }
                    }
                }
            }
        }

};
