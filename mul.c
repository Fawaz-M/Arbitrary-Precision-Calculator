#include "apc.h"

static int multiply_by_digit(node *tail1, int digit2,
                             node **headR, node **tailR)
{
    int carry = 0;

    while (tail1 != NULL || carry != 0)
    {
        int product = carry;

        if (tail1 != NULL)
        {
            product += tail1->data * digit2;
            tail1 = tail1->prev;
        }

        int digit = product % 10;
        carry = product / 10;

        if (insert_first(headR, tailR, digit) == FAILURE)
        {
            delete_list(headR, tailR);
            return FAILURE;
        }
    }

    return SUCCESS;
}

void multiplication(node *tail1, node *tail2,
                    node **headR, node **tailR)
{
    *headR = NULL;
    *tailR = NULL;

    int shift = 0;

    while (tail2 != NULL)
    {
        node *tempHead = NULL;
        node *tempTail = NULL;

        // Multiply the first number by the current digit of the second.
        if (multiply_by_digit(tail1, tail2->data,
                              &tempHead, &tempTail) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }

        // Shift the partial product left by adding zeros at the end.
        for (int i = 0; i < shift; i++)
        {
            if (insert_last(&tempHead, &tempTail, 0) == FAILURE)
            {
                delete_list(&tempHead, &tempTail);
                delete_list(headR, tailR);
                return;
            }
        }

        // The first partial product becomes the initial result.
        if (*headR == NULL)
        {
            *headR = tempHead;
            *tailR = tempTail;
        }
        else
        {
            node *sumHead = NULL;
            node *sumTail = NULL;

            // Add the current partial product to the accumulated result.
            addition(*tailR, tempTail, &sumHead, &sumTail);

            delete_list(headR, tailR);
            *headR = sumHead;
            *tailR = sumTail;

            delete_list(&tempHead, &tempTail);
        }

        tail2 = tail2->prev;
        shift++;
    }

    // Remove unnecessary leading zeros from the final result.
    remove_pre_zeros(headR);
}