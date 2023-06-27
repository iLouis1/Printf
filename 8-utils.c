#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @b: Char to be evaluated.
 *
 * Return: 1 if b is printable, 0 otherwise
 */

int is_printable(char b)

{
	if (b >= 32 && b < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: An array of chars.
 * @j: Index to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */

int append_hexa_code(char ascii_code, char buffer[], int j)

{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[j++] = '\\';
	buffer[j++] = 'x';

	buffer[j++] = map_to[ascii_code / 16];
	buffer[j] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @b: Char to be evaluated
 *
 * Return: 1 if b is a digit, 0 otherwise
 */

int is_digit(char b)
{
	if (b >= '0' && b <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Will casts a number to the specified size
 * @num: The number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */

long int convert_size_number(long int num, int size)

{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Will cast a number to the specified size
 * @num: The number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */

long int convert_size_unsgnd(unsigned long int num, int size)

{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
