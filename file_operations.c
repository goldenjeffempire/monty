#include "monty.h"

/**
 * access_file - function that opens file
 * @file_name: string of file name
 * Return: nothing
**/

void access_file(char *file_name)
{
	FILE *fd;

	if (file_name == NULL)
		handle_error(2, file_name);
	if (access(file_name, R_OK) == -1)
		handle_error(2, file_name);
	fd = fopen(file_name, "r");
	if (fd == NULL)
		handle_error(2, file_name);
	scan_file(fd);
	fclose(fd);
}

/**
 * scan_file - function that reads the opened file
 * @fd: pointer to file discriptor
**/

void scan_file(FILE *fd)
{
	int line_n;
	int format;
	char *lineptr;
	size_t n;

	lineptr = NULL;
	n = 0;
	format = 0;

	for (line_n = 1; getline(&lineptr, &n, fd) != -1; line_n++)
	{
		format = parse_line(lineptr, line_n, format);
	}
	free(lineptr);
}

/**
 * parse_line - tokenizes line and turns to a command function to call
 * @lineptr: string in line of a file
 * @line_number: line number for the opcode
 * @format: format specifier, 0 if nodes will be entered as a stack
 * 1 if nodes will be entered as a queue
 * Return: 0 if the opcode is stack or 1 if queue
**/

int parse_line(char *lineptr, int line_number, int format)
{
	const char *delim;
	char *opcode;
	char *value;

	if (lineptr == NULL)
		err(4);
	delim = "\n ";
	opcode = strtok(lineptr, delim);

	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "queue") == 0)
		return (1);
	else if (strcmp(opcode, "stack") == 0)
		return (0);

	locate_func(opcode, value, line_number, format);
	return (format);
}

/**
 * locate_func - function that finds the right function to run the opcode
 * @opcode: operation code
 * @value: possible value for the operation
 * @ln: line number for the opcode
 * @format: format specifier, 0 if nodes will be entered as a stack
 * 1 if nodes will be entered as a queue
 * Return: nothing
**/

void locate_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t opcode_executors[] = {
		{"push", push_to_stack},
		{"pall", display_stack},
		{"pint", display_top},
		{"pop", remove_top},
		{"nop", no_operation},
		{"swap", interchange_nodes},
		{"add", sum_nodes},
		{"sub", subtract_nodes},
		{"div", divide_nodes},
		{"mul", multiply_nodes},
		{"mod", modulus_nodes},
		{"pchar", display_char},
		{"pstr", display_str},
		{"rotl", rotate_left},
		{"rotr", rotate_right},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;
	for (flag = 1, i = 0; opcode_executors[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, opcode_executors[i].opcode) == 0)
		{
			execute_func(opcode_executors[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		handle_error(3, ln, opcode);
}

/**
 * execute_func - executes the required function
 * @f: pointer to function that is about to be called
 * @op: string representing opcode
 * @val: string representing a numeric value
 * @ln: line number for the instruciton
 * @format: format specifier, 0 if nodes will be entered as a stack
 * 1 if nodes will be entered as a queue
 * Return: nothing
**/

void execute_func(op_func f, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = generate_node(atoi(val) * flag);
		if (format == 0)
			f(&node, ln);
		if (format == 1)
			enqueue(&node, ln);
	}
	else
		f(&head, ln);
}
