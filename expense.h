
#include <stddef.h>

typedef struct expense
{
    /* data */
    int month;
    float how_much;
    char *definition;
    struct expense *next;

} expense;

expense *create_expense(char *definition, int *month, float *price);
void release_expense(expense *start);
void add_expense(expense **first_expense_address, expense **last_expense_address, expense *new_expense_address, int *expense_counter);
void insert_from_terminal(expense **first_expense_address, expense **last_expense_address, int *expense_counter);
void delete_all_expenses_from_memory(expense *first_expense_address, int *expense_counter);
void list_all_expenses(expense *first_expense_address, int *expese_counter, wchar_t *currency);
void sort_by_price(expense *first_expense_address, int *expense_counter, wchar_t *currency);
void modify_link_pointers(expense *i);
void modify_sorted_link_nexts(expense i[], int *expense_counter);
void write_to_file(char *filename, expense *first_expense_address, int *expense_counter);
void read_from_file(char *filename, expense **first_expense_address, expense **last_expense_address, int *expense_counter);