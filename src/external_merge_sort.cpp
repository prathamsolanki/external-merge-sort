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
        int8_t element;  

        Node(int index, int8_t element)
            : index(index), element(element)
        {
        }
}; 

bool operator<(const Node &n1, const Node &n2)
{
    return n1.element > n2.element;
}

void merge_sublists (int sublists_to_merge[], int d) {
    fstream sublists[d];
    char fileName[10];
    for (int i = 0; i < d; i++) { 
        snprintf(fileName, sizeof(fileName), "%d", sublists_to_merge[i]);
        sublists[i].open(fileName, fstream::in);
    } 

    ofstream merged_list("temp");

    priority_queue<Node> Q;

    int i;
    int8_t e;
    for (i = 0; i < d; i++) {
        sublists[i] >> e;
        Q.push(Node(i, e));
    } 

    int count = 0; 

    while (count != i) { 
        Node root = Q.top();
        merged_list << root.element;
        Q.pop();

        if (!(sublists[root.index] >> e)) { 
            Q.push(Node(root.index,127));
            count++; 
        } else {
            Q.push(Node(root.index, e));
        }
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

    for (int n = 0; n < num_sublists; n++) { 
        int buffer_size;
        if (n == num_sublists-1) buffer_size = N - (M * (num_sublists-1));
        else buffer_size = M;

        in.read(buffer, buffer_size);

        sort(buffer, buffer + buffer_size);

        sublists[n].write(buffer, buffer_size);
        sublists[n].close();
    }

    in.close();
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
