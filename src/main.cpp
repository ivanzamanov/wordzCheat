#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include"ptree.h"
#include"utils.h"

int main(int argc, const char** argv) {
	int fd;
	if(argc <= 1) {
		printf("Usage: %s <data_file>\n", argv[0]);
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	if(fd < 0) {
		printf("Cannot open file %s\n", argv[1]);
		return 2;
	}

	struct stat fileStat;
	if(fstat(fd, &fileStat)) {
		printf("Cannot stat file %s\n", argv[1]);
		return 3;
	}

	int size = fileStat.st_size;
	char* buffer = new char[size];

	int bytes = read(fd, buffer, size);
	if(bytes != size) {
		printf("Could not read entire file\n");
		return 4;
	}

	const int BUF_SIZE = 1024;
	char wordBuf[BUF_SIZE];
	int offset = 0;
	int index;
	ptree t;
	while(offset < size) {
		index = 0;
		while(!isWhitespace(*(buffer + offset)) && offset < size) {
			wordBuf[index] = *(buffer + offset);
			offset++;
			if(index >= BUF_SIZE)
				printf("Error: buffer overflow\n");
			index++;
		}
		offset++;
		wordBuf[index] = '\0';
		t.add(wordBuf);
	}
	return 0;
}

