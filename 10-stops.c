#include "shell.h"
#include <stdio.h>

/**
 * _reverse - reverses string
 * @str: string to reverse
 * @n: the length of string
 * Return: reversed string
 */
char *_reverse(char *str, int n)
{
	char *start = str;
	char *end;
	char temp;

	end = str + n - 1;
	for (; start < end; start++, end--)
	{
		temp = *end;
		*end = *start;
		*start = temp;
	}
	return (str);
}

/**
 * _itoa - converts an integer of base 10 to a string
 * @num: integer number to convert
 * Return: integer in string format
 */
char *_itoa(int num)
{
	int x = 0, neg = 0, c_num = num, len, rem = 0;
	char *str;


	for (len = 0; c_num; c_num /= 10);
	if (num == 0)
	{
		str = do_mem(2 * sizeof(char), NULL);
		str[x++] = '0';
		str[x] = '\0';
		return (str);
	}
	if (num < 0)
	{
		neg = 1;
		num = -num;
		len++;
	}
	str = do_mem((len + 1) * sizeof(char), NULL);
	while (num != 0)
	{
		rem = num % 10;
		str[x++] = rem + '0';
		num = num / 10;
	}
	if (neg)
		str[x++] = '-';
	str[x] = '\0';
	_reverse(str, x);

	return (str);
}

/**
 * _memset - memset function of a string
 * @s: start point of string to change
 * @b: value that will replace pointer
 * @n: number of bytes to change
 * Return: changed pointer
 */
char *_memset(char *s, char b, int n)
{
	char *x = s;

	for (; n != 0; x++, n--)
		*x = b;
	return (s);
}
