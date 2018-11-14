#include "iostream"
#include <string.h>

#include "one_element_at_time.cpp"
#include "cpp_std_file_io.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	const char *filename = "../data/file.txt";

	if (strcmp(argv[1], "1") == 0) {
		OneElementAtTime obj;
		obj.readOneElementAtTime(filename);
		obj.writeOneElementAtTime(filename);
	}
	else if (strcmp(argv[1], "2") == 0) {
		CppStdFileIO obj;
		obj.readFile(filename);
		obj.writeFile(filename);
	}

	return 0;
}
