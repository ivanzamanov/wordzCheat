#include"ptree.h"

const int SIZE = 256;

int ptree::getIndex(char c) {
	int result = (int)c;
	return result;
}

ptree::ptree() {
	cap = 1;
	size = 1;
	table = new int*[cap];
	table[0] = new int[SIZE];
	for(int i=0; i<SIZE; i++)
		table[0][i] = -1;
	flags = new bool[cap];
	flags[0] = 0;
}

ptree::~ptree() {
	for(int i=0; i<size; i++)
		delete table[i];
	delete table;
	delete flags;
}

void ptree::expand() {
	int new_cap = cap << 1;
	int** new_table = new int*[new_cap];
	bool* new_flags = new bool[new_cap];
	for(int i=0; i<cap; i++) {
		new_table[i] = table[i];
		new_flags[i] = flags[i];
	}
	for(int i=cap; i<new_cap; i++) {
		new_table[i] = 0;
		new_flags[i] = 0;
	}

	delete table;
	delete flags;

	table = new_table;
	flags = new_flags;
	cap = new_cap;
}

bool ptree::get(const char* str) {
	const char* s = str;
	int state = 0;
	while(*s != '\0' && state >= 0) {
		int c = getIndex(*s);
		state = table[state][c];
		s++;
	}

	if(state == -1 || !flags[state])
		return 0;

	return 1;
}

void ptree::add(const char* str) {
	const char* s = str;
	int state = 0;
	while(*s != '\0') {
		int c = getIndex(*s);
		int n_state = table[state][c];
		if(n_state == -1) {
			break;
		}
		state = n_state;
		s++;
	}

	while(*s != '\0') {
		int c = getIndex(*s);
		int n_state = buildState();
		table[state][c] = n_state;
		state = n_state;
		s++;
	}
	flags[state] = 1;
}

int ptree::buildState() {
	if(size == cap)
		expand();

	int result = size;
	size++;
	table[result] = new int[SIZE];
	for(int i=0; i<SIZE; i++)
		table[result][i] = -1;
	return result;
}

