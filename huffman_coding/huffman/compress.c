#include "../huffman.h"

/**
 * compress - compress a file using Huffman codes
 * @in_file: input file (uncompressed)
 * @out_file: output file (compressed)
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int compress(const char *in_file, const char *out_file)
{
	int ret = EXIT_SUCCESS;
	char_freq_t *char_data;

	/* Count symbols */
	char_data = count_symbols(in_file);
	if (char_data == NULL)
		return (EXIT_FAILURE);

	/* Make huffman codes */
	ret = huffman_codes(char_data->data, char_data->freq, char_data->size);

	/* Create compressed file */

	return (ret);
}

/**
 * count_symbols - count the number of found symbols in the in_file
 * @in_file: input file for Huffman codes
 * Return: struct pointer holding vectors of each symbol's data and frequency
 */
char_freq_t *count_symbols(const char *in_file)
{
	char_freq_t *char_data;
	FILE *file;
	char *tmp1;
	size_t i, *tmp2;
	int c, found;

	char_data = malloc(sizeof(char_freq_t));
	if (char_data == NULL)
		return (NULL);
	char_data->size = 0;
	char_data->data = calloc(128, sizeof(char));
	char_data->freq = calloc(128, sizeof(size_t));
	if (char_data->freq == NULL || char_data->data == NULL)
		return (NULL);
	file = fopen(in_file, "r");
	while ((c = fgetc(file)) != EOF && c <= 127)
	{
		found = 0;
		for (i = 0; i < char_data->size; i++)
		{
			if (c == char_data->data[i])
			{
				char_data->freq[i]++;
				found = 1;
			}
		}
		if (!found)
		{
			char_data->size++;
			char_data->data[char_data->size - 1] = c;
			char_data->freq[char_data->size - 1] = 1;
		}
	}
	return (char_data);
}
