/*
Name                : Mohamed fawaz.K.H
Class               : 26015C
Start Date          : 07 / 10 / 2026
End Date            : 30 / 10 / 2026
Project Name        : Arbitrary Precision Calculator (APC)

Project Description :
 Developed an Arbitrary Precision Calculator (APC) in C to perform arithmetic operations on large integers beyond standard data type limits.
*/


#include "apc.h"

static void print_digits(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

static void print_header(char *num1, char oper, char *num2)
{
    printf("========== APC ==========\n");
    printf("Operation : %s %c %s\n", num1, oper, num2);
}

static void print_footer(void)
{
    printf("=========================\n");
}

static void help(void)
{
    printf("\n========== APC HELP ==========\n");
    printf("Usage: ./a.out <operand1> <operator> <operand2>\n\n");

    printf("Operators:\n");
    printf("  +   Addition\n");
    printf("  -   Subtraction\n");
    printf("  x   Multiplication\n");
    printf("  X   Multiplication\n");
    printf("  *   Multiplication\n");
    printf("  /   Division\n\n");

    printf("Examples:\n");
    printf("  ./a.out 123 + 456\n");
    printf("  ./a.out 987 - 123\n");
    printf("  ./a.out 123 x 45\n");
    printf("  ./a.out 100 / 7\n\n");

    printf("Help options: ./a.out -h | -help | --help\n");
    printf("==============================\n");
}

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;
    node *headQ = NULL, *tailQ = NULL;
    node *headRem = NULL, *tailRem = NULL;
    node *headFrac = NULL, *tailFrac = NULL;

    int status = SUCCESS;

    if (argc == 1 ||
        (argc == 2 &&
         (strcmp(argv[1], "-h") == 0 ||
          strcmp(argv[1], "-help") == 0 ||
          strcmp(argv[1], "--help") == 0)))
    {
        help();
        return SUCCESS;
    }

    if (argc != 4)
    {
        printf("Usage: ./a.out num1 operator num2\n");
        printf("Use ./a.out --help for help.\n");
        return FAILURE;
    }

    int sign1 = 1, sign2 = 1;
    char *num1 = argv[1];
    char *num2 = argv[3];

    if (num1[0] == '-')
    {
        sign1 = -1;
        num1++;
    }

    if (num2[0] == '-')
    {
        sign2 = -1;
        num2++;
    }

    if (validate(num1) == FAILURE)
    {
        printf("Num 1 is not a proper digit\n");
        return FAILURE;
    }

    if (validate(num2) == FAILURE)
    {
        printf("Num 2 is not a proper digit\n");
        return FAILURE;
    }

    create_list(num1, &head1, &tail1);
    create_list(num2, &head2, &tail2);

    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    tail1 = head1;
    while (tail1 != NULL && tail1->next != NULL)
        tail1 = tail1->next;

    tail2 = head2;
    while (tail2 != NULL && tail2->next != NULL)
        tail2 = tail2->next;

    char oper = argv[2][0];

    switch (oper)
    {
        case '+':
        {
            if (sign1 == sign2)
            {
                addition(tail1, tail2, &headR, &tailR);
            }
            else
            {
                int cmp = compare_list(head1, head2);

                if (cmp == SAME)
                {
                    insert_first(&headR, &tailR, 0);
                }
                else if (cmp == OPERAND1)
                {
                    subtraction(tail1, tail2, &headR, &tailR);
                }
                else
                {
                    subtraction(tail2, tail1, &headR, &tailR);
                }
            }

            print_header(argv[1], oper, argv[3]);

            if (headR != NULL &&
                !(headR->data == 0 && headR->next == NULL) &&
                ((sign1 == sign2 && sign1 == -1) ||
                 (sign1 != sign2 &&
                  compare_list(head1, head2) == OPERAND1 &&
                  sign1 == -1) ||
                 (sign1 != sign2 &&
                  compare_list(head1, head2) == OPERAND2 &&
                  sign2 == -1)))
            {
                printf("-");
            }

            print_digits(headR);
            printf("\n");
            print_footer();
            break;
        }

        case '-':
        {
            int cmp = compare_list(head1, head2);

            if (sign1 != sign2)
            {
                addition(tail1, tail2, &headR, &tailR);
            }
            else if (cmp == SAME)
            {
                insert_first(&headR, &tailR, 0);
            }
            else if (cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);
            }
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);
            }

            print_header(argv[1], oper, argv[3]);

            if (headR != NULL &&
                !(headR->data == 0 && headR->next == NULL) &&
                ((sign1 != sign2 && sign1 == -1) ||
                 (sign1 == sign2 && cmp == OPERAND1 && sign1 == -1) ||
                 (sign1 == sign2 && cmp == OPERAND2 && sign1 == 1)))
            {
                printf("-");
            }

            print_digits(headR);
            printf("\n");
            print_footer();
            break;
        }

        case 'x':
        case 'X':
        case '*':
        {
            multiplication(tail1, tail2, &headR, &tailR);

            print_header(argv[1], oper, argv[3]);

            if (headR != NULL &&
                !(headR->data == 0 && headR->next == NULL) &&
                sign1 != sign2)
            {
                printf("-");
            }

            print_digits(headR);
            printf("\n");
            print_footer();
            break;
        }

        case '/':
        {
            division(head1, head2,
                     &headQ, &tailQ,
                     &headRem, &tailRem,
                     &headFrac, &tailFrac);

            if (headQ == NULL || headRem == NULL)
            {
                printf("Invalid division (possibly division by zero)\n");
                status = FAILURE;
                break;
            }

            print_header(argv[1], oper, argv[3]);

            printf("Quotient  : ");

            if (sign1 != sign2 &&
                !(headQ->data == 0 && headQ->next == NULL))
            {
                printf("-");
            }

            print_digits(headQ);

            if (headFrac != NULL)
            {
                printf(".");
                print_digits(headFrac);
            }

            printf("\nRemainder : ");

            if (sign1 == -1 &&
                !(headRem->data == 0 && headRem->next == NULL))
            {
                printf("-");
            }

            print_digits(headRem);
            printf("\n");
            print_footer();
            break;
        }

        default:
        {
            printf("Invalid operator\n");
            status = FAILURE;
            break;
        }
    }

    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);
    delete_list(&headQ, &tailQ);
    delete_list(&headRem, &tailRem);
    delete_list(&headFrac, &tailFrac);

    return status;
}