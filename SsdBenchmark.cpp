// SSD testing tool for real life results
// Running (for a 20 GB file, read/write giga per giga):
// time ssdbenchmark w test.bin 1024 20
// time ssdbenchmark r test.bin 1024
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MB (1024 * 1024)


static void writeFile(const char* fileName, unsigned blockSize, unsigned fileSize) {
	FILE* f = fopen(fileName, "wb");
	void *block = calloc(1, blockSize);

	for (unsigned i = 0; i < fileSize; i++) {
		fwrite(block, blockSize, 1, f);
	}

	free(block);
	fclose(f);
}

static void readFile(const char* fileName, unsigned blockSize) {
	FILE* f = fopen(fileName, "rb");
	void* block = calloc(1, blockSize);

	while (!feof(f)) {
		fread(block, blockSize, 1, f);
	}

	free(block);
	fclose(f);
}

int main(int argc, char **argv) {
	const char* USAGE = "Usage: ssdbenchmark r|w filename.bin [blockSizeInMB] [numberOfBlocksToWrite]\n";

	if (argc < 4) {
		printf(USAGE);
		return 0;
	}

	const char* fileName = argv[2];
	unsigned blockSizeInMb = atoi(argv[3]);

	switch (argv[1][0]) {
	case 'w':
		if (argc < 5) {
			printf(USAGE);
			break;
		}
		writeFile(argv[2], blockSizeInMb * MB, atoi(argv[4]));
		break;

	case 'r':
		readFile(argv[2], blockSizeInMb * MB);
		break;

	default:
		printf(USAGE);
		break;
	}

	return 0;
}
