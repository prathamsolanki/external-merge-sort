#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <climits>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

using namespace std; 

struct MinHeapNode { 
    char element; 

    int i; 
}; 

void swap(MinHeapNode* x, MinHeapNode* y) { 
    MinHeapNode temp = *x; 
    *x = *y; 
    *y = temp; 
}

class MinHeap { 
    MinHeapNode* harr;
    int heap_size; 

    public:
    MinHeap(MinHeapNode a[], int size) { 
        heap_size = size; 
        harr = a; 
        int i = (heap_size - 1) / 2; 
        while (i >= 0) 
        { 
            MinHeapify(i); 
            i--; 
        } 
    }

    void MinHeapify(int i ) { 
        int l = left(i); 
        int r = right(i); 
        int smallest = i; 
        if (l < heap_size && harr[l].element < harr[i].element) 
            smallest = l; 
        if (r < heap_size && harr[r].element < harr[smallest].element) 
            smallest = r; 
        if (smallest != i) 
        { 
            swap(&harr[i], &harr[smallest]); 
            MinHeapify(smallest); 
        } 
    }

    int left(int i) { return (2 * i + 1); } 

    int right(int i) { return (2 * i + 2); } 

    MinHeapNode getMin() { return harr[0]; } 

    void replaceMin(MinHeapNode x) { 
        harr[0] = x; 
        MinHeapify(0); 
    } 
}; 

void merge_sublists (char *output_file, int d) { 
    int in[d]; 
    for (int i = 0; i < d; i++) { 
        char fileName[2]; 

        snprintf(fileName, sizeof(fileName), "%d", i); 

        in[i] = open(fileName, O_RDONLY);
    } 

    int out = open (output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR, O_RDWR); 

    MinHeapNode harr[d]; 
    int i; 
    for (i = 0; i < d; i++) 
    {
        read(in[i], (void*)&harr[i].element, 1);
        
        harr[i].i = i;
    } 
    MinHeap hp(harr, i);

    int count = 0; 

    while (count != i) 
    { 
        MinHeapNode root = hp.getMin(); 
        write(out, (void*)&root.element, 1); 

        if (read(in[root.i], (void*)&root.element, 1) == 0) 
        { 
            root.element = CHAR_MAX; 
            count++; 
        } 

        hp.replaceMin(root); 
    }

    for (int i = 0; i < d; i++) {
        close(in[i]);
    }

    close(out); 
} 

void create_sorted_sublists (char *input_file, int M, int num_sublists) {
    ifstream inFile(input_file);

    fstream outFile[num_sublists]; 
    char fileName[2]; 
    for (int i = 0; i < num_sublists; i++) {
        snprintf(fileName, sizeof(fileName), "%d", i);
        outFile[i].open(fileName, fstream::out);
    } 

    char *buffer = (char*) malloc (sizeof(char)*M);

    int next_output_file = 0; 

    for (int n = 0; n < num_sublists; n++) { 
        inFile.read(buffer, M);

        sort(buffer, buffer + M);

        outFile[next_output_file].write(buffer, M);
        outFile[next_output_file].close();

        next_output_file++;
    }

    inFile.close();
} 

void externalSort(char* input_file, char *output_file, int num_sublists, int M, int d) { 
    create_sorted_sublists(input_file, M, num_sublists);
    merge_sublists(output_file, d);
} 
