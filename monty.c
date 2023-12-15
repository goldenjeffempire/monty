#include "monty.h"

stack_t *head = NULL;

/**
 * main - entry point to program
 * @argc: argument count
 * @argv: argument vector
 * Return: always success
**/

int main(int argc, char **argv)
{
	if (argc != 2)
		handle_error(1);
	access_file(argv[1]);
	release_nodes();
	return (0);
}
