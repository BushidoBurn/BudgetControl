#include <stdlib.h>
#include <string.h>
#include "expense.h"

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
