#include <stdio.h>
#include "main.h"
/**
 * pass_betty_check -  a beautiful code that passes the Betty checks
 *
 * Return: 0 (on success)
*/
int pass_betty_check(void)
{
	write(STDOUT_FILENO, "Betty check passed!\n", 2);
	return (0);
}
