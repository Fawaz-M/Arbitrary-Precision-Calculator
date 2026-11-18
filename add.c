#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        int sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        int digit = sum % 10;
        carry = sum / 10;

        // Insert each result digit at the front to keep the correct order.
        if (insert_first(headR, tailR, digit) == FAILURE)
        {
            delete_list(headR, tailR);
            return;
        }
    }
}