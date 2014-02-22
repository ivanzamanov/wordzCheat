#ifndef __PTREE_H__
#define __PTREE_H__

class ptree {
public:
	ptree();
	~ptree();
	void add(const char* str);
	bool get(const char* str);

private:
	int getIndex(char c);
	void expand();
	int buildState();
	int** table;
	bool* flags;
	int cap;
	int size;
};

#endif
