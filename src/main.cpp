#include "iostream"
#include <string.h>

#include "streams_demo.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	const char *filename = "../data/file.txt";

    InputStream in(filename, argv[1]);
    OutputStream out(filename, argv[1]);

	return 0;
}
