#include "iostream"
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class OneElementAtTime {
	public:
		char c;

		void readOneElementAtTime(const char *filename) {
			int file = open(filename, O_RDONLY);

			if (file < 0) {
				cout << "can't open file" << endl;
			}
			else {
				ssize_t isLastElement;
				while (isLastElement != 0) {
					isLastElement = read(file, (void*)&c, 1);
					if (c == '\n') continue;
					cout << c << endl;
				}
				close(file);
			}
		}

		void writeOneElementAtTime(const char *filename) {
			int file = open(filename, O_WRONLY | O_APPEND);

			if (file < 0) {
				cout << "can't open file" << endl;
			}
			else {
				char c;
				cout << "Enter element to enter: " << endl;
				cin >> c;
				ssize_t successfullyWritten = write(file, (void*)&c, 1);
				if (successfullyWritten == 0) cout << "couldn't be written" << endl;
				else cout << "successfully written " << c << endl;
				close(file);
			}
		}
};
