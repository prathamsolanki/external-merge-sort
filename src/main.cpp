#include "iostream"
#include <string.h>

#include "io_mechanisms.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    IOMechanisms io_mech;

    cout << "#### Benchmarking Data Stream ####" << endl;
    io_mech.benchmark_data_stream();
    cout << endl;

    cout << "#### Benchmarking Buffered Stream ####" << endl;
    io_mech.benchmark_buffered_stream();
    cout << endl;

    cout << "#### Benchmarking Buffered Stream (Fixed Buffer Size) ####" << endl;
    io_mech.benchmark_buffered_stream_fixed_size();
    cout << endl;

    cout << "#### Benchmarking Memory Mapped File IO ####" << endl;;
    io_mech.benchmark_memory_mapped_file_io();
    cout << endl;

    return 0;
}
