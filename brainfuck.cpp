#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>
using namespace std;
int main(int const argc, char const * argv[])
{
	if (argc != 2) {
		cerr << "Usage: brainfuck [file]" << endl;
		return 1;
	}
    
	// Read the program into a vector.
	ifstream ifs(argv[1]);
	if (!ifs.good()) {
		cerr << "There was an error opening the file for reading." << endl;
		return 1;
	}
	ifs.seekg(0, ios::end);
    vector<char> instructions(ifs.tellg());
    ifs.seekg(0, ios::beg);
    ifs >> noskipws;
    ifs.read(&instructions[0], instructions.size());
    ifs.close();
    
	// Parse and interpret the commands.
    vector<char> stack(30000);
    vector<char>::iterator data_pointer = stack.begin();
    std::stack<vector<char>::const_iterator> jumps;
	for (vector<char>::const_iterator instruction_pointer = instructions.begin(); instruction_pointer != instructions.end(); ++instruction_pointer) {
		switch (*instruction_pointer) {
            case '>':
                ++data_pointer;
                if (data_pointer == stack.end())
                    data_pointer = stack.begin();
                break;
            case '<':
                if (data_pointer == stack.begin())
                    data_pointer = stack.end();
                --data_pointer;
                break;
            case '+':
                ++*data_pointer;
                break;
            case '-':
                --*data_pointer;
                break;
            case '.':
                cout.put(*data_pointer);
                break;
            case ',':
                cin.get(*data_pointer);
                break;
            case '[':
                if (*data_pointer == 0)
                    instruction_pointer = find(instruction_pointer + 1, static_cast<vector<char> const &>(instructions).end(), ']');
                else
                    jumps.push(instruction_pointer);
                break;
            case ']':
                if (*data_pointer != 0)
                    instruction_pointer = jumps.top();
                else
                    jumps.pop();
                break;
		}
	}

	return 0;
}
