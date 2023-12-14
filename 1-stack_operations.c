#include "monty.h"

void push_to_stack(stack_t **new_node, __attribute__((unused))unsigned int ln);
void enqueue(stack_t **new_node, __attribute__((unused))unsigned int ln);
void display_stack(stack_t **stack, unsigned int line_number);
void display_top(stack_t **stack, unsigned int line_number);
void remove_top(stack_t **stack, unsigned int line_number);
/**
 * push_to_stack - Adds a node to the beginning of the stack (LIFO).
 * @new_node: Pointer to the new node.
 * @ln: Line number of the opcode (integer).
 * Return: nothing
 */
void push_to_stack(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}
/**
 * enqueue - Adds a node to the end of the queue (FIFO).
 * @new_node: Pointer to the new node.
 * @ln: Line number of the opcode (integer)
 * Return: void
 */
void enqueue(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *new_node;
	(*new_node)->prev = tmp;
}
/**
 * display_stack - Prints nodes in the stack.
 * @stack: Pointer to the top node of the stack.
 * @line_number: Line number of the opcode (integer).
 * Return: void
 */
void display_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
/**
 * display_top - prints the value at the top of the stack
 * @stack: Pointer to the top node of the stack.
 * @line_number: Line number of the opcode (integer).
 * Return: void
 */
void display_top(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		handle_additional_error(6, line_number);
	printf("%d\n", (*stack)->n);
}
/**
 * remove_top - removes the top element from the stack
 * @stack: Pointer to the top node of the stack
 * @line_number: Line number of the opcode (integer).
 * Return: void
 */
void remove_top(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		handle_additional_error(7, line_number);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}
