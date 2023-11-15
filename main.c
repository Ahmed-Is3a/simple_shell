#include "main.h"

/**
 * main - the main function where the programm start
 *
 * @argc: num of args
 * @argv: list of args
 * Return: always 0 (on success)
 */
int main(int argc, char *argv[])
{
	(void)argc;  /* unused parameter */

	/**
	 * argv[0] is the output_file name
	 * which is in this case the shell name
	 */
	display_shell_prompt(argv[0]);

	return (0);
}
