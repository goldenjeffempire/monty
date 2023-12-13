#include "monty.h"

void handle_error(int error_code, ...);
void handle_additional_error(int error_code, ...);
void handle_string_error(int error_code, ...);

/**
 * handle_error - Display appropriate error based on error codes.
 * @error_code: The error codes and their meanings:
 * (1) -> User didn't specify a file or provided multiple files.
 * (2) -> Provided file is not openable or readable.
 * (3) -> Provided file contains an invalid instruction.
 * (4) -> Program is unable to allocate additional memory using malloc.
 * (5) -> Parameter passed to the "push" instruction is not an integer.
 * (6) -> Stack is empty for the "pint" instruction.
 * (7) -> Stack is empty for the "pop" instruction.
 * (8) -> Stack is too short for the specified operation
 * Return: void
 */
void handle_error(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n",
				va_arg(ag, char *));
			break;
		case 3:
			l_num = va_arg(ag, int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", l_num, op);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(ag, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * handle_additional_error - Manages stack errors and division by zero.
 * @error_code: Error codes
 * (6) -> Stack is empty for "pint."
 * (7) -> Stack is empty for "pop."
 * (8) -> Stack is too short for the operation.
 * (9) -> Division by zero.
 * Return: void
 */
void handle_additional_error(int error_code, ...)
{
	va_list ag;
	char *op;
	int l_num;

	va_start(ag, error_code);
	switch (error_code)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n",
				va_arg(ag, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n",
				va_arg(ag, int));
			break;
		case 8:
			l_num = va_arg(ag, unsigned int);
			op = va_arg(ag, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", l_num, op);
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n",
				va_arg(ag, unsigned int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * handle_string_error - Handles specific errors related to string operations.
 * @error_code: Error codes:
 * (10) -> Number inside a node is outside ASCII bounds.
 * (11) -> Stsck is empty
 * Return: void
 */
void handle_string_error(int error_code, ...)
{
	va_list ag;
	int l_num;

	va_start(ag, error_code);
	l_num = va_arg(ag, int);
	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", l_num);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", l_num);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
