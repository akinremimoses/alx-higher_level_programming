#include "lists.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * reverse_list - Reverses a linked list.
 * @head: Double pointer to the head of the list.
 * Return: Pointer to the new head of the reversed list.
 */
listint_t *reverse_list(listint_t **head)
{
    listint_t *prev = NULL, *current = *head, *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
    return *head;
}

/**
 * compare_lists - Compares two linked lists for equality.
 * @list1: Pointer to the first list.
 * @list2: Pointer to the second list.
 * Return: 1 if lists are equal, 0 otherwise.
 */
int compare_lists(listint_t *list1, listint_t *list2)
{
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->n != list2->n)
            return 0;

        list1 = list1->next;
        list2 = list2->next;
    }

    return (list1 == NULL && list2 == NULL);
}

/**
 * is_palindrome - Checks if a singly linked list is a palindrome.
 * @head: Pointer to the head of the list.
 * Return: 1 if it is a palindrome, 0 otherwise.
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow = *head, *fast = *head, *second_half, *prev_slow = *head;
    listint_t *mid_node = NULL;
    int is_palindrome = 1;

    if (*head != NULL && (*head)->next != NULL)
    {
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            prev_slow = slow;
            slow = slow->next;
        }

        if (fast != NULL)
        {
            mid_node = slow;
            slow = slow->next;
        }

        second_half = slow;
        prev_slow->next = NULL;
        reverse_list(&second_half);
        is_palindrome = compare_lists(*head, second_half);
        reverse_list(&second_half);

        if (mid_node != NULL)
        {
            prev_slow->next = mid_node;
            mid_node->next = second_half;
        }
        else
        {
            prev_slow->next = second_half;
        }
    }

    return is_palindrome;
}

