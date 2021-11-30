#include <stdlib.h>
#include <string.h>
#include "expense.h"
#include <stdio.h>

expense *create_expense(char *definition, int *month, float *price)
{
    expense *i = malloc(sizeof(expense));
    i->definition = strdup(definition);
    i->month = *month;
    i->how_much = *price;
    i->next = NULL;
    return i;
}

void release_expense(expense *start)
{
    expense *i = start;
    expense *next = NULL;
    for (; i != NULL; i = next)
    {
        next = i->next;
        free(i->definition);
        free(i);
    }
}

void release_selected_expense(expense *start, int *selected_index, int *expense_counter)
{
    printf("in function 1 st line");
    fflush(stdout);
    expense *i = start;
    expense *next = NULL;
    expense *before_next = NULL;
    int counter = 0;
    printf("in function");
    fflush(stdout);
    if ((*selected_index < *expense_counter) && (*selected_index >= 0))
    {
        printf("in if");
        fflush(stdout);

        for (; i != NULL; i = next)
        {
            printf("in loop");
            fflush(stdout);
            if (*selected_index == 0)
            { // printf("This is before adres %p", i);
                printf("if 0 worked");
                fflush(stdout);
                *start = *i->next;
                free(i->definition);
                free(i);
                *expense_counter = *expense_counter - 1;
                break;
            }

            if (counter == *selected_index - 1)
            {
                printf("in -1");
                fflush(stdout);
                before_next = i;
                // printf("This is before adres %p", i);
            }

            if (counter == *selected_index)
            {
                printf("in last");
                fflush(stdout);
                before_next->next = i->next;
                //printf("Bye bye  %p", i);
                //printf("This is befores nextt adres %p", before_next->next);
                free(i->definition);
                free(i);
                *expense_counter = *expense_counter - 1;
            }
            next = i->next;
            counter++;
        }
    }
}
