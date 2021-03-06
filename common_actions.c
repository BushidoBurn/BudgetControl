#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "expense.h"
#include <wchar.h>
#include <locale.h>

void insert_from_terminal(expense **first_expense_address, expense **last_expense_address, int *expense_counter)
{

    char definition[80];
    float price = 0;
    int month = 0;
    expense *new_expense;

    printf("Enter Definition  max 79 characters\n");
    //fputs("Enter Definition  max 79 characters", stdout);
    //fgets(definition, sizeof(definition), stdin);
    //scanf("%79s[0-9a-zA-Z ]", definition);
    fflush(stdin);
    fgets(definition, 80, stdin);
    int len = strlen(definition); //where buff is your char array fgets is using
    if (definition[len - 1] == '\n')
        definition[len - 1] = '\0';
    printf("\nEnter price\n");
    scanf("%f", &price);
    printf("\nEnter month as a number Ex: 1 for January");
    scanf("%d", &month);
    //printf("\nok");

    new_expense = create_expense(definition, &month, &price);

    //printf("Allocated address %p", new_expense);

    add_expense(first_expense_address, last_expense_address, new_expense, expense_counter);
}

void add_expense(expense **first_expense_address, expense **last_expense_address, expense *new_expense_address, int *expense_counter)
{

    if (!(*expense_counter))
    {
        *first_expense_address = new_expense_address;
        *last_expense_address = new_expense_address;

        *expense_counter = *expense_counter + 1;
    }
    else
    {
        (*last_expense_address)->next = new_expense_address;
        *last_expense_address = new_expense_address;
        *expense_counter = *expense_counter + 1;
    }
}

void delete_all_expenses_from_memory(expense *first_expense_address, int *expense_counter)
{
    release_expense(first_expense_address);
    *expense_counter = 0;
}

void list_all_expenses(expense *first_expense_address, int *expense_counter, wchar_t *currency)
{
    int item_index = 0;

    if ((*expense_counter))
    {
        expense *i = first_expense_address;
        expense *next = NULL;
        for (; i != NULL; i = next)
        {
            next = i->next;
            wprintf(L"(%d)  %30s  %.2f %lc  %i\n", item_index, i->definition, i->how_much, currency[0], i->month);
            item_index++;
        }
    }
    else
    {
        printf("\nNo Expense To List\n");
    }
}

void sort_by_price(expense *first_expense_address, int *expense_counter, wchar_t *currency)
{
    expense dummy_array[*expense_counter];

    if ((*expense_counter))
    {
        int count = 0;
        expense *i = first_expense_address;
        expense *next = NULL;
        for (; i != NULL; i = next)
        {
            next = i->next;
            dummy_array[count] = *i;
            count++;
        }
    }

    for (int xx = 0; xx < *expense_counter - 1; xx++)
    {
        for (int yy = 0; yy < *expense_counter - 1 - xx; yy++)
            if (dummy_array[yy + 1].how_much < dummy_array[yy].how_much)
            {                                         /* compare the two neighbors */
                float tmp = dummy_array[yy].how_much; /* swap a[j] and a[j+1]      */
                dummy_array[yy].how_much = dummy_array[yy + 1].how_much;
                dummy_array[yy + 1].how_much = tmp;

                int tmp1 = dummy_array[yy].month; /* swap a[j] and a[j+1]      */
                dummy_array[yy].month = dummy_array[yy + 1].month;
                dummy_array[yy + 1].month = tmp1;

                char *tmp2 = dummy_array[yy].definition; /* swap a[j] and a[j+1]      */
                dummy_array[yy].definition = dummy_array[yy + 1].definition;
                dummy_array[yy + 1].definition = tmp2;
            }
    }
    for (int i = 0; i < *expense_counter; i++)
    {
        wprintf(L"  %30s  %.2f %lc %i\n", dummy_array[i].definition, dummy_array[i].how_much, currency[0], dummy_array[i].month);
    }
    modify_sorted_link_nexts(dummy_array, expense_counter);
}

void modify_link_pointers(expense *i)
{
    expense *temp;
    temp->next = (i + 1)->next;
    (i + 1)->next = i->next;
    i->next = temp->next;

    (i - 1)->next = i->next;
}

void modify_sorted_link_nexts(expense i[], int *expense_counter)
{
    for (int j = 0; j < *expense_counter - 1; j++)
    {
        /* code */
        (*(i + j)).next = (i + j);
    }
}

void write_to_file(char *filename, expense *first_expense_address, int *expense_counter)
{
    FILE *outfile;
    if (access(filename, F_OK) == 0)
    {
        // file exists
        outfile = fopen(filename, "a");
    }
    else
    {
        // file doesn't exist
        outfile = fopen(filename, "w");
    }

    if ((*expense_counter))
    {

        expense *i = first_expense_address;
        expense *next = NULL;
        for (; i != NULL; i = next)
        {
            next = i->next;
            fprintf(outfile, "%s %.2f %d\n", i->definition, i->how_much, i->month);
        }
    }
    fclose(outfile);
}

void read_from_file(char *filename, expense **first_expense_address, expense **last_expense_address, int *expense_counter)
{
    //printf("\n\n");
    FILE *infile;
    char line[200];
    expense *new_expense;

    if (access(filename, F_OK) == 0)
    {
        // file exists
        infile = fopen(filename, "r");

        while (fscanf(infile, "%[^\n] ", line) != EOF)
        {
            // printf("%s\n", line);
            char *token = strtok(line, " ");
            char *definition;
            int month;
            float price;
            int counter = 0;

            while (token != NULL)
            {
                if (counter == 0)
                {
                    definition = token;
                }
                else if (counter == 1)
                {
                    price = atof(token);
                }
                else if (counter == 2)
                {
                    month = atoi(token);
                    counter = 0;
                }
                //printf(" %s\n", token); //printing each token

                token = strtok(NULL, " ");
                counter++;
            }
            //printf("%s %f %d", definition, price, month);
            new_expense = create_expense(definition, &month, &price);

            add_expense(first_expense_address, last_expense_address, new_expense, expense_counter);
        }
        printf("\n");
        printf("   !!!  Data Was Loaded Succesfully !!!\n");
        printf("   !!!  Press l for listing !!!\n");
    }
    else
    {
        // file doesn't exist
        printf("That file does not exist in current directory\n");
    }
    printf("\n");
}

void search_in_definition(expense *first_expense_address, int *expense_counter, char *search_term, wchar_t *currency)
{

    int item_index = 0;

    if ((*expense_counter))
    {
        expense *i = first_expense_address;
        expense *next = NULL;
        for (; i != NULL; i = next)
        {
            next = i->next;
            if (strstr(i->definition, search_term))
                wprintf(L"(%d)  %30s  %.2f %lc  %i\n", item_index, i->definition, i->how_much, currency[0], i->month);
            item_index++;
        }
    }
    else
    {
        printf("\nNo Expense To List\n");
    }
}

void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}