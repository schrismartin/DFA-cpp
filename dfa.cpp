#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

class DFA {
	public:
		vector< vector<string> > data;
		map<string, vector<string> > instruction_set;
		map<char, int> symbols;
		string fs, str, start;

		DFA(string input_string) {
			// Acts as main operator of program. All functionality
			// is wrapped into a class to allow access of class
			// variables to simplify read/write operations and
			// reduce the cost of copying potentially large data 
			// structures.

			str = input_string;
			parseFile();
			construct();
			printf("%s\n", dfa_recursive(0, start) ? "true" : "false");
		}

		void parseFile() {
			// Reads the config file from stdin to construct the rules
			// of our DFA. Sample config can be found in template.txt

			vector<string> input;
			istringstream iss;
			string line, buffer;
			int size;

			// Parse header line
			getline(cin, line);
			iss.str(line);
			iss >> start; // Read start state
			iss >> fs; // Read final state

			while(iss >> buffer) {
				// Read in symbols
				input.push_back(buffer);
			}
			size = input.size() + 1;
			data.push_back(input);

			// Get state instructions
			while(getline(cin, line)) {
				input.resize(0);
				iss.clear();
				iss.str(line);
				while(iss >> buffer) {
					input.push_back(buffer);
				}
				if(input.size() != size) { fprintf(stderr, "Each symbol must have a state (found %d, expected %d)\n", input.size(), size); exit(0); }
				data.push_back(input);
			}
		}

		void construct() {
			// Creates needed links in order to make template more flexible,
			// allowing for use of strings as states, as opposed to integers.
			// This makes the state file more readable and potentially more
			// flexible.

			vector<string> instruction;
			int i;
			string key;

			// Convert Symbols
			for(i = 0; i < data[0].size(); i++){
				symbols[data[0][i][0]] = i; // First letter of the string
			}

			// Key instruction sets
			for(i = 1; i < data.size(); i++){
				key = data[i][0];
				instruction_set[key] = data[i];
			}
		}

		void printData() {
			// Helper function for debugging - prints contents of data vector.
			int i, j;
			for(i = 0; i < data.size(); i++){
				for(j = 0; j < data[i].size(); j++){
					printf("%s ", data[i][j].c_str());
				}
				printf("\n");
			}
		}

		bool dfa_recursive(int i, string state) {
			// Recursive algorithm which follows instructions for the lifetime
			// of the input string. Easily convertable to interative structure,
			// but recursion made more intuitive sense. Made to also practice
			// recursion.

			bool rv;
			int symbol_i;
			vector<string> instructions;
			string newstate;

			// Base case, exit out.
			if(i == str.size()) { return state == fs; }

			// Find and execute next state
			symbol_i = symbols[str[i]];
			instructions = instruction_set[state];
			newstate = instructions[symbol_i + 1];

			return dfa_recursive(i+1, newstate);
		}
};

int main(int argc, char** argv) {
	if(argc != 2) { fprintf(stderr, "usage dfs test_string < dfs_δ\n"); exit(0); }

	// Initialize DFA class, where all of the logic incurs.
	DFA *dfa = new DFA(argv[1]);
}
