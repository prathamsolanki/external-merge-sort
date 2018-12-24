#include "iostream"
#include <string.h>

#include "io_mechanisms.cpp"
#include "external_merge_sort.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    /*IOMechanisms io_mech;

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
    cout << endl;*/

    cout << "#### Benchmarking External Merge Sort" << endl;
    int M = 5; 
    int N = 22;
    int d = 5;

    int num_sublists = ceil(float(N)/float(M));

    char input_file[] = "../data/input.txt"; 
    char output_file[] = "../data/output.txt"; 

    FILE* in = fopen(input_file, "w"); 

    srand(time(NULL)); 
    for (int i = 0; i < N; i++) 
        fprintf(in, "%d", rand()% 10); 

    fclose(in); 

    externalSort(input_file, N, output_file, num_sublists, M, d);

    return 0;
}
