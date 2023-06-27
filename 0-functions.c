#include "main.h"

/**
 * print_char - This prints a char
 * @types: List a of arguments
 * @buffer: This is the buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],

	int flags, int width, int precision, int size)

{

	char c = va_arg(types, int);



	return (handle_write_char(c, buffer, flags, width, precision, size));

}


/**
 * print_string - This prints a string
 * @types: This is a list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],

	int flags, int width, int precision, int size)

{

	int length = 0, k;

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

			for (k = width - length; k > 0; k--)

				write(1, " ", 1);

			return (width);

		}

		else

		{

			for (k = width - length; k > 0; k--)

				write(1, " ", 1);

			write(1, &str[0], length);

			return (width);

		}

	}



	return (write(1, str, length));

}



/**
 * print_percent - Will print a percent sign
 * @types: A list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Will calculate active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
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
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_int(va_list types, char buffer[],

	int flags, int width, int precision, int size)

{

	int k = BUFF_SIZE - 2;

	int is_negative = 0;

	long int h = va_arg(types, long int);

	unsigned long int num;



	h = convert_size_number(h, size);



	if (h == 0)

		buffer[k--] = '0';



	buffer[BUFF_SIZE - 1] = '\0';

	num = (unsigned long int)h;



	if (h < 0)

	{

		num = (unsigned long int)((-1) * h);

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
 * print_binary - Will print an unsigned number
 * @types: A list of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],

	int flags, int width, int precision, int size)

{

	unsigned int h, j, k, sum;

	unsigned int a[32];

	int count;



	UNUSED(buffer);

	UNUSED(flags);

	UNUSED(width);

	UNUSED(precision);

	UNUSED(size);



	h = va_arg(types, unsigned int);

	j = 2147483648; /* (2 ^ 31) */

	a[0] = h / j;

	for (k = 1; k < 32; k++)

	{

		j /= 2;

		a[k] = (h / j) % 2;

	}

	for (k = 0, sum = 0, count = 0; k < 32; k++)

	{

		sum += a[k];

		if (sum || k == 31)

		{

			char e = '0' + a[k];



			write(1, &e, 1);

			count++;

		}

	}

	return (count);

}
