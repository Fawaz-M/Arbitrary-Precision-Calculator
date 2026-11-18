#include "apc.h"

int divide_by_subtraction(node **currentHead, node **currentTail,
                          node *divisorHead)
{
    int count = 0;

    // Subtract the divisor repeatedly to find one quotient digit.
    while (compare_list(*currentHead, divisorHead) != OPERAND2)
    {
        node *subHead = NULL;
        node *subTail = NULL;

        subtraction(*currentTail, divisorHead, &subHead, &subTail);

        delete_list(currentHead, currentTail);
        *currentHead = subHead;
        *currentTail = subTail;

        count++;
    }

    return count;
}

void division(node *head1, node *head2,
              node **headQ, node **tailQ,
              node **headRem, node **tailRem,
              node **headFrac, node **tailFrac)
{
    *headQ = *tailQ = NULL;
    *headRem = *tailRem = NULL;
    *headFrac = *tailFrac = NULL;

    if (head1 == NULL || head2 == NULL)
        return;

    // Reject a divisor containing only zero.
    if (head2->data == 0 && head2->next == NULL)
        return;

    node *divisorTail = head2;
    while (divisorTail->next != NULL)
        divisorTail = divisorTail->next;

    node *currentHead = NULL;
    node *currentTail = NULL;
    node *digitPtr = head1;

    // Process the dividend one digit at a time.
    while (digitPtr != NULL)
    {
        // Remove a temporary zero before bringing down the next digit.
        if (currentHead != NULL &&
            currentHead->data == 0 &&
            currentHead->next == NULL)
        {
            delete_list(&currentHead, &currentTail);
        }

        insert_last(&currentHead, &currentTail, digitPtr->data);

        int qDigit = 0;

        // Find this quotient digit by repeated subtraction.
        while (currentHead != NULL &&
               compare_list(currentHead, head2) != OPERAND2)
        {
            node *subHead = NULL;
            node *subTail = NULL;

            subtraction(currentTail, divisorTail, &subHead, &subTail);
            delete_list(&currentHead, &currentTail);

            currentHead = subHead;
            currentTail = subTail;

            if (currentHead == NULL)
                insert_first(&currentHead, &currentTail, 0);

            remove_pre_zeros(&currentHead);
            qDigit++;
        }

        // Skip leading zeros in the quotient.
        if (*headQ != NULL || qDigit != 0)
            insert_last(headQ, tailQ, qDigit);

        digitPtr = digitPtr->next;
    }

    if (*headQ == NULL)
        insert_first(headQ, tailQ, 0);

    if (currentHead == NULL)
        insert_first(&currentHead, &currentTail, 0);

    // Continue dividing the remainder to generate decimal digits.
    for (int i = 0; i < 7; i++)
    {
        // No more fractional digits are needed if remainder is zero.
        if (currentHead->data == 0 && currentHead->next == NULL)
            break;

        // Appending zero is equivalent to multiplying the remainder by 10.
        insert_last(&currentHead, &currentTail, 0);

        int qDigit = 0;

        // Find the next fractional digit using repeated subtraction.
        while (compare_list(currentHead, head2) != OPERAND2)
        {
            node *subHead = NULL;
            node *subTail = NULL;

            subtraction(currentTail, divisorTail, &subHead, &subTail);
            delete_list(&currentHead, &currentTail);

            currentHead = subHead;
            currentTail = subTail;

            if (currentHead == NULL)
                insert_first(&currentHead, &currentTail, 0);

            remove_pre_zeros(&currentHead);
            qDigit++;
        }

        insert_last(headFrac, tailFrac, qDigit);
    }

    // The remaining value is the remainder after decimal expansion.
    *headRem = currentHead;
    *tailRem = currentTail;
}