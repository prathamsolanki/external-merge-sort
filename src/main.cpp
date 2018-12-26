#include "iostream"
#include <string.h>

#include "benchmark.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    Benchmark benchmark;

    /*cout << "#### Benchmarking Data Stream ####" << endl;
    benchmark.benchmark_data_stream();
    cout << endl;

    cout << "#### Benchmarking Buffered Stream ####" << endl;
    benchmark.benchmark_buffered_stream();
    cout << endl;

    cout << "#### Benchmarking Buffered Stream (Fixed Buffer Size) ####" << endl;
    benchmark.benchmark_buffered_stream_fixed_size();
    cout << endl;

    cout << "#### Benchmarking Memory Mapped File IO ####" << endl;;
    benchmark.benchmark_memory_mapped_file_io();
    cout << endl;*/

    cout << "#### Benchmarking External Merge Sort" << endl;
    benchmark.benchmark_external_merge_sort();

    return 0;
}
