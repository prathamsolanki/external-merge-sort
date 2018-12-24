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
        while (i >= 0) { 
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
    int sublists[d]; 
    for (int i = 0; i < d; i++) { 
        char fileName[2]; 

        snprintf(fileName, sizeof(fileName), "%d", i); 

        sublists[i] = open(fileName, O_RDONLY);
    } 

    int merged_list = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR, O_RDWR); 

    MinHeapNode harr[d]; 
    int i; 
    for (i = 0; i < d; i++) {
        read(sublists[i], (void*)&harr[i].element, 1);

        harr[i].i = i;
    } 
    MinHeap hp(harr, i);

    int count = 0; 

    while (count != i) { 
        MinHeapNode root = hp.getMin(); 
        write(merged_list, (void*)&root.element, 1); 

        if (read(sublists[root.i], (void*)&root.element, 1) == 0) { 
            root.element = CHAR_MAX; 
            count++; 
        } 

        hp.replaceMin(root); 
    }

    for (int i = 0; i < d; i++) {
        close(sublists[i]);
    }

    close(merged_list); 
} 

void create_sorted_sublists (char *input_file, int N, int M, int num_sublists) {
    ifstream in(input_file);

    fstream sublists[num_sublists]; 
    char fileName[2]; 
    for (int i = 0; i < num_sublists; i++) {
        snprintf(fileName, sizeof(fileName), "%d", i);
        sublists[i].open(fileName, fstream::out);
    } 

    char *buffer = (char*) malloc (sizeof(char)*M);

    int count_sublist = 0; 

    for (int n = 0; n < num_sublists; n++) { 
        int buffer_size;
        if (n == num_sublists-1) buffer_size = N - (M * (num_sublists-1));
        else buffer_size = M;

        cout << buffer_size;

        in.read(buffer, buffer_size);

        sort(buffer, buffer + buffer_size);

        sublists[count_sublist].write(buffer, buffer_size);
        sublists[count_sublist].close();

        count_sublist++;
    }

    in.close();
} 

void externalSort(char* input_file, int N, char *output_file, int num_sublists, int M, int d) { 
    create_sorted_sublists(input_file, N, M, num_sublists);
    merge_sublists(output_file, d);
} 
