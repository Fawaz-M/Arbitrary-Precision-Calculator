#include "apc.h"

// Validate command-line arguments
int cla_validation(int argc, char *argv[])
{
    // Check that exactly three arguments are provided
    if (argc != 4)
        return FAILURE;

    // Validate the first operand
    if (validate(argv[1]) == FAILURE)
        return FAILURE;

    // Ensure the operator contains exactly one character
    if (argv[2][1] != '\0')
        return FAILURE;

    // Check whether the operator is supported
    if (argv[2][0] != '+' &&
        argv[2][0] != '-' &&
        argv[2][0] != 'x' &&
        argv[2][0] != '*' &&
        argv[2][0] != '/')
    {
        return FAILURE;
    }

    // Validate the second operand
    if (validate(argv[3]) == FAILURE)
        return FAILURE;

    // Reject division by zero, including values like 000
    if (argv[2][0] == '/')
    {
        int i = 0;

        // Skip leading zeros
        while (argv[3][i] == '0' && argv[3][i] != '\0')
            i++;

        // If only zeros were found, the divisor is zero
        if (argv[3][i] == '\0')
            return FAILURE;
    }

    return SUCCESS;
}

// Convert a numeric string into a linked list of digits
void create_list(char *opr, node **head, node **tail)
{
    while (*opr)
    {
        // Convert the character digit into an integer
        int digit = *opr - '0';

        // Append the digit to the list
        if (insert_last(head, tail, digit) == FAILURE)
        {
            printf("INSERTION FAILED\n");
            delete_list(head, tail);
            return;
        }

        opr++;
    }
}

// Free all nodes in a linked list
int delete_list(node **head, node **tail)
{
    // Nothing to delete
    if (*head == NULL)
        return FAILURE;

    node *temp = *head;

    // Free each node
    while (temp != NULL)
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }

    // Reset the list pointers
    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}

// Print the digits stored in a linked list
void print_list(node *head)
{
    node *temp = head;

    // Print each digit without linked-list arrows
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

// Count the number of nodes in a linked list
int list_len(node *head)
{
    int count = 0;
    node *temp = head;

    // Visit each node and increment the count
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

// Validate that a string contains only decimal digits
int validate(char *str)
{
    // Reject an empty string
    if (*str == '\0')
        return FAILURE;

    // Check each character
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return FAILURE;

        str++;
    }

    return SUCCESS;
}

// Compare two non-negative integer linked lists
int compare_list(node *head1, node *head2)
{
    // Compare the number of digits first
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    if (len1 > len2)
        return OPERAND1;

    if (len1 < len2)
        return OPERAND2;

    // If lengths match, compare digits from left to right
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return OPERAND1;

        if (head1->data < head2->data)
            return OPERAND2;

        // Move to the next digit in both lists
        head1 = head1->next;
        head2 = head2->next;
    }

    // Both numbers are equal
    return SAME;
}

// Remove leading zeros while keeping at least one digit
void remove_pre_zeros(node **head)
{
    // Handle an empty list
    if (*head == NULL)
        return;

    // Remove leading zero nodes, but keep one zero for the number 0
    while ((*head)->data == 0 && (*head)->next != NULL)
    {
        node *temp = *head;

        *head = (*head)->next;
        (*head)->prev = NULL;

        free(temp);
    }
}

// Insert a new digit at the beginning of a linked list
int insert_first(node **head, node **tail, int data)
{
    // Allocate memory for the new node
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    // Store the digit
    new->data = data;

    // Handle an empty list
    if (*head == NULL && *tail == NULL)
    {
        new->prev = NULL;
        new->next = NULL;

        *head = *tail = new;
    }
    else
    {
        // Link the new node before the current head
        new->prev = NULL;
        new->next = *head;

        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}

// Insert a new digit at the end of a linked list
int insert_last(node **head, node **tail, int data)
{
    // Allocate memory for the new node
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    // Initialize the new node
    new->prev = *tail;
    new->data = data;
    new->next = NULL;

    // Handle an empty list
    if (*head == NULL && *tail == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        // Link the new node after the current tail
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}