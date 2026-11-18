#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow = 0;

    // Assumes the first number is greater than or equal to the second.
    while (tail1 != NULL)
    {
        int digit1 = tail1->data - borrow;
        int digit2 = 0;

        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int digit = digit1 - digit2;

        if (insert_first(headR, tailR, digit) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }

        tail1 = tail1->prev;
    }

    remove_pre_zeros(headR);
}