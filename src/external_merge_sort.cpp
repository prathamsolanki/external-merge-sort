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

class Node { 
    public:
        int index;
        int element;  

        Node(int index, int element)
            : index(index), element(element)
        {
        }
}; 

bool operator<(const Node &n1, const Node &n2)
{
    return n1.element > n2.element;
}

void merge_sublists (int sublists_to_merge[], int d) {
    int sublists[d];
    char fileName[10];
    for (int i = 0; i < d; i++) { 
        snprintf(fileName, sizeof(fileName), "%d", sublists_to_merge[i]);
        sublists[i] = open(fileName, O_RDONLY);
    } 

    int merged_list = open("temp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, S_IRUSR);

    priority_queue<Node> Q;

    int i;
    int e;
    for (i = 0; i < d; i++) {
        read(sublists[i], &e, sizeof(e));
        Q.push(Node(i, e));
    } 

    int count = 0; 

    while (count != i) { 
        Node root = Q.top();
        write(merged_list, &root.element, sizeof(root.element));
        Q.pop();

        if (read(sublists[root.index], &e, sizeof(e)) == 0) { 
            Q.push(Node(root.index,INT_MAX));
            count++; 
        } else {
            Q.push(Node(root.index, e));
        }
    }

    for (int i = 0; i < d; i++) {
        close(sublists[i]);
    }

    close(merged_list);

    char p[10];
    sprintf(p, "%d", sublists_to_merge[0]);
    remove(p);
    std::experimental::filesystem::copy("temp", p);
    remove("temp");
} 

void create_sorted_sublists (char *input_file, int N, int M, int num_sublists) {
    FILE *in = fopen(input_file, "rb");

    FILE *sublists[num_sublists]; 
    char fileName[10]; 
    for (int i = 0; i < num_sublists; i++) {
        snprintf(fileName, sizeof(fileName), "%d", i);
        sublists[i] = fopen(fileName, "wb");
    } 

    int *buffer = (int*) malloc (sizeof(int)*M);

    for (int n = 0; n < num_sublists; n++) { 
        int buffer_size;
        if (n == num_sublists-1) buffer_size = N - (M * n);
        else buffer_size = M;

        fread(buffer, sizeof(int), buffer_size, in);

        sort(buffer, buffer + buffer_size);

        fwrite(buffer, sizeof(int), buffer_size, sublists[n]);
        fclose(sublists[n]);
    }

    fclose(in);
} 

void external_merge_sort(char* input_file, int N, int num_sublists, int M, int d) { 
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
