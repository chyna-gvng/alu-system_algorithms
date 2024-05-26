#include "../huffman.h"
#include <unistd.h>

/**
 * main - entrypoint for huffman encoder/decoder
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	int ret = EXIT_FAILURE;

	if (argc != 4)
	{
		printf("Usage: huffman <mode> <filename> <out_filename>\n");
		return (ret);
	}
	if (access(argv[2], F_OK | R_OK) == -1)
		printf("No such file: %s\n", argv[2]);
	if (access(argv[3], F_OK) != -1)
		printf("File already exists: %s\n", argv[3]);

	if (!strcmp(argv[1], "c"))
		ret = compress(argv[2], argv[3]);
	else if (!strcmp(argv[1], "d"))
		ret = decompress(argv[2], argv[3]);
	else
		printf("Option has to be either 'c' or 'd'\n");

	return (ret);
}
