#include "iostream"
#include <string.h>

#include "benchmark.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    Benchmark benchmark;

    if (strcmp(argv[1], "1") == 0) {
        freopen("benchmark_data_stream.txt","w",stdout);
        cout << "#### Benchmarking Data Stream ####" << endl;
        benchmark.benchmark_data_stream();
        cout << endl;
    }

    else if (strcmp(argv[1], "2") == 0) {
        freopen("benchmark_buffered_stream.txt","w",stdout);
        cout << "#### Benchmarking Buffered Stream ####" << endl;
        benchmark.benchmark_buffered_stream();
        cout << endl;
    }

    else if (strcmp(argv[1], "3") == 0) {
        freopen("benchmark_buffered_stream_fixed_size.txt","w",stdout);
        cout << "#### Benchmarking Buffered Stream (Fixed Buffer Size) ####" << endl;
        benchmark.benchmark_buffered_stream_fixed_size();
        cout << endl;
    }

    else if (strcmp(argv[1], "4") == 0) {
        freopen("benchmark_memory_mapping.txt","w",stdout);
        cout << "#### Benchmarking Memory Mapped File IO ####" << endl;;
        benchmark.benchmark_memory_mapped_file_io();
        cout << endl;
    }

    else {
        freopen("benchmark_external_merge_sort.txt","w",stdout);
        cout << "#### Benchmarking External Merge Sort" << endl;
        benchmark.benchmark_external_merge_sort();
    }

    return 0;
}
