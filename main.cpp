#include "iostream"
#include <unistd.h>
#include <fcntl.h>

#include "one_element_at_time.cpp"

using namespace std;

int main()
{
	const char *filename = "data/file.txt";

	OneElementAtTime obj;
	obj.readOneElementAtTime(filename);

	return 0;
}
