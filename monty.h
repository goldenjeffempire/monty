#ifndef MONTY_H
#define MONTY_H

#define  _GNU_SOURCE

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
**/

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
**/

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;

typedef void (*op_func)(stack_t **, unsigned int);

stack_t *generate_node(int n);
void release_nodes(void);
void no_operation(stack_t **stack, unsigned int line_number);
void interchange_nodes(stack_t **stack, unsigned int line_number);

void push_to_stack(stack_t **new_node, __attribute__((unused))unsigned int ln);
void enqueue(stack_t **new_node, __attribute__((unused))unsigned int ln);
void display_stack(stack_t **stack, unsigned int line_number);
void display_top(stack_t **stack, unsigned int line_number);
void remove_top(stack_t **stack, unsigned int line_number);

void access_file(char *file_name);
void scan_file(FILE *fd);
int parse_line(char *lineptr, int line_number, int format);
void locate_func(char *opcode, char *value, int ln, int format);
void execute_func(op_func f, char *op, char *val, int ln, int format);

void sum_nodes(stack_t **stack, unsigned int line_number);
void subtract_nodes(stack_t **stack, unsigned int line_number);
void divide_nodes(stack_t **stack, unsigned int line_number);
void multiply_nodes(stack_t **stack, unsigned int line_number);
void modulus_nodes(stack_t **stack, unsigned int line_number);

void display_char(stack_t **stack, unsigned int line_number);
void display_str(stack_t **stack, __attribute__((unused))unsigned int ln);
void rotate_left(stack_t **stack, __attribute__((unused))unsigned int ln);
void rotate_right(stack_t **stack, __attribute__((unused))unsigned int ln);

void handle_error(int error_code, ...);
void handle_additional_error(int error_code, ...);
void handle_string_error(int error_code, ...);

#endif /* MONTY_H */
