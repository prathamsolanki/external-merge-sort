#include "iostream"
#include <string.h>

#include "io_mechanisms.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    IOMechanisms io_mech;

    io_mech.benchmark_data_stream();
    cout << endl;
    io_mech.benchmark_buffered_stream();
    cout << endl;
    io_mech.benchmark_buffered_stream_fixed_size();

    return 0;
}
