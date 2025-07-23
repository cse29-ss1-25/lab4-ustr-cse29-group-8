#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char *contents)
{
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char *contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s)
{
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive)
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end)
{
	// TODO: implement this
	if (start < 0 || end > s.codepoints || start >= end)
	{
		return new_ustr("");
	}
	int32_t byte_start = bi_of_cpi(s.contents, start);
	int32_t byte_end = bi_of_cpi(s.contents, end);
	if (byte_start < 0 || byte_end < 0 || byte_start >= byte_end)
	{
		return new_ustr("");
	}
	int32_t sub_len = byte_end - byte_start;
	char *buffer = malloc(sub_len + 1);
	if (buffer == NULL)
	{
		return new_ustr("");
	}
	memcpy(buffer, s.contents + byte_start, sub_len);
	buffer[sub_len] = '\0';
	UStr result = new_ustr(buffer);
	free(buffer);
	return result;
}

/*
Given 2 strings s1 and s2, returns a string that is the result of
concatenating s1 and s2.
*/
UStr concat(UStr s1, UStr s2)
{
	// TODO: implement this
	int total_bytes = s1.bytes + s2.bytes;
	char *new_contents = malloc(total_bytes + 1);
	if (new_contents == NULL)
	{

		UStr empty = {0, 0, 1, NULL};
		return empty;
	}

	int i = 0;
	for (int j = 0; j < s1.bytes; j++)
	{
		new_contents[i] = s1.contents[j];
		i++;
	}
	for (int j = 0; j < s2.bytes; j++)
	{
		new_contents[i] = s2.contents[j];
		i++;
	}
	new_contents[i] = '\0';

	UStr result = {
		.codepoints = s1.codepoints + s2.codepoints,
		.bytes = total_bytes,
		.contents = new_contents,
		.is_ascii = s1.is_ascii && s2.is_ascii};
	return result;
}

/*
Given a string s and an index, return a string with the character at index
removed from the original string.

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index)
{
	// TODO: implement this
	if (index < 0 || index >= s.codepoints)
	{

		return new_ustr(s.contents);
	}

	char *new_contents = malloc(s.bytes + 1);
	if (new_contents == NULL)
	{
		return new_ustr("");
	}

	int32_t cpi = 0;
	int32_t read = 0;
	int32_t write = 0;

	while (s.contents[read] != '\0')
	{
		if (cpi == index)
		{

			int skip_bytes = utf8_codepoint_size(s.contents[read]);
			read += skip_bytes;
			cpi++;
			continue;
		}

		int cp_size = utf8_codepoint_size(s.contents[read]);
		for (int i = 0; i < cp_size; i++)
		{
			new_contents[write++] = s.contents[read++];
		}
		cpi++;
	}

	new_contents[write] = '\0';

	UStr result = new_ustr(new_contents);
	free(new_contents);
	return result;
}

/*
Given a string s, return s reversed.

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s)
{
	// TODO: implement this
	const char *input = s.contents;
	int32_t len = s.bytes;
	char *reversed = malloc(len + 1);
	if (reversed == NULL)
	{
		return new_ustr("");
	}

	int32_t read_index = len - 1;
	int32_t write_index = 0;
	while (read_index >= 0)
	{

		while (read_index > 0 && is_continuation_byte((unsigned char)input[read_index]))
		{
			read_index--;
		}
		int8_t cp_size = utf8_codepoint_size(input[read_index]);
		if (cp_size <= 0)
		{
			free(reversed);
			return new_ustr("");
		}
		memcpy(reversed + write_index, input + read_index, cp_size);
		write_index += cp_size;
		read_index--;
	}
	reversed[write_index] = '\0';
	UStr result = new_ustr(reversed);
	free(reversed);
	return result;
}

void print_ustr(UStr s)
{
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s)
{
	if (s.contents != NULL)
	{
		free(s.contents);
		s.contents = NULL;
	}
}
