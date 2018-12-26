#include <iostream> 
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <climits>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <experimental/filesystem>

using namespace std; 

struct MinHeapNode { 
    int8_t element; 

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

void merge_sublists (int sublists_to_merge[], int d) {
    fstream sublists[d];
    char fileName[10];
    for (int i = 0; i < d; i++) { 
        snprintf(fileName, sizeof(fileName), "%d", sublists_to_merge[i]);
        sublists[i].open(fileName, fstream::in);
    } 

    ofstream merged_list("temp");

    MinHeapNode harr[d]; 
    int i; 
    for (i = 0; i < d; i++) {
        sublists[i] >> harr[i].element;
        harr[i].i = i;
    } 
    MinHeap hp(harr, i);

    int count = 0; 

    while (count != i) { 
        MinHeapNode root = hp.getMin(); 
        merged_list << root.element; 

        if (!(sublists[root.i] >> root.element)) { 
            root.element = 127; 
            count++; 
        } 

        hp.replaceMin(root); 
    }

    for (int i = 0; i < d; i++) {
        sublists[i].close();
    }

    merged_list.close();

    char p[10];
    sprintf(p, "%d", sublists_to_merge[0]);
    remove(p);
    std::experimental::filesystem::copy("temp", p);
    remove("temp");
} 

void create_sorted_sublists (char *input_file, int N, int M, int num_sublists) {
    ifstream in(input_file);

    fstream sublists[num_sublists]; 
    char fileName[10]; 
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

        in.read(buffer, buffer_size);

        sort(buffer, buffer + buffer_size);

        sublists[count_sublist].write(buffer, buffer_size);
        sublists[count_sublist].close();

        count_sublist++;
    }

    in.close();
} 

void externalSort(char* input_file, int N, int num_sublists, int M, int d) { 
    create_sorted_sublists(input_file, N, M, num_sublists);

    priority_queue<int> q;
    for (int i = 0; i < num_sublists; i++) q.push(i);

    while (q.size() > 1) {
        if (q.size() < d) {
            int temp[q.size()];
            int i = 0;
            while (!q.empty()) {
                temp[i] = q.top();
                q.pop();
                i++;
            }
            merge_sublists(temp, sizeof(temp) / sizeof(*temp));
            break;
        }
        else {
            int temp[d];
            for (int i = 0; i < d; i++) {
                temp[i] = q.top();
                q.pop();
            }
            merge_sublists(temp, sizeof(temp) / sizeof(*temp));
            q.push(temp[0]);
        }
    }
} 
