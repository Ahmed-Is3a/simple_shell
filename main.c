#include "main.h"

/**
 * main - the main function where the programm start
 *
 * @argc: number of arguments
 * @argv: list of arguments
 * Return: always 0 (on success)
 */
int main(int argc, char *argv[])
{
	(void)argc;  /* unused parameter */

	shell = argv[0];
	/**
	 * argv[0] is the output_file name
	 * which is in this case the shell name
	 */
	display_shell_prompt();

	return (0);
}
