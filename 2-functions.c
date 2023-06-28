#include "main.h"

/**
 * print_char - This prints a character
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  This will calculate active flags
 * @width: Width
 * @precision: Specifies Precision
 * @size: Specifies size
 * Return: The number of Characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - This will print strings
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  This will calculate active flags
 * @width: width.
 * @precision: Specifies Precision
 * @size: Specifies size
 * Return: The number of Characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - This will print percent sign
 * @types: A list of argument
 * @buffer: Buffer array to handle print
 * @flags:  This will calculate active flags
 * @width: width.
 * @precision: Specifies Precision
 * @size: Specifies size
 * Return: The number of Characters printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - This will print int
 * @types: A list of argument
 * @buffer: Buffer array to handle print
 * @flags:  This will calculate active flags
 * @width: width.
 * @precision: Specifies Precision
 * @size: Specifies size
 * Return: The number of Characters printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (write_number(is_negative, k, buffer, flags, width, precision, size));
}


/**
 * print_binary - Prints an unsigned number
 * @types: A list of argument
 * @buffer: Buffer array to handle print
 * @flags:  This will calculate active flags
 * @width: width.
 * @precision: Specifies Precision
 * @size: Specifies size
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	a[0] = x / y;
	for (k = 1; k < 32; k++)
	{
		y /= 2;
		a[k] = (x / y) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
