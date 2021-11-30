/***
 * 
 *  This program is written for managing monthly expences and budget
 * 
 * 
 * Program a budget planner for the available monthly capital and the
*  monthly cost of living informa7on 
*   such as rent, food, telephone costs, etc.
*
*  For the months January to December. Use a suitable structure array for
*  this. (Array of months)
*
*  Allow you to enter individual values in a monetary currency of your choice. (Define an enum for currencies)
*
*  Save the entries in a suitable structure array with variable amount of
*  entries.(Define a customtype with struct and make a linked list)
*
*  Enable the entry of new items with their data and a list func7on that
*  displays the budget planner .(Read and print entries)
*
*  Implement add, delete, sort, search and list func7ons in your code
*
*  Write and read your data in and from a file with the name “budget.txt".
* 
 **/

#include <stdio.h>
#include "expense.h"
#include <wchar.h>
#include <locale.h>
#include <string.h>

float income_for_months[12];
float money_left[12];
int months[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
expense *first_item_address = NULL;
expense *last_item_address = NULL;
//expense *temp;
int expense_counter = 0;
int selected_item = -1;
char search_term[80];

wchar_t currency_symbols[] = {0x20ac, 0x0024, 0x00A3, 0x00A5};

//char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int main()
{

    printf("\n");
    setlocale(LC_CTYPE, "");
    //float price;
    //char *definition[80];
    //int month;

    char *action;
    // printf("\033[0;31m"); //Set the text to the color red
    //printf(“\033[0m”); //Resets the text to default color
    // printf("\033[0;37m"); //Resets the text to default white
    // printf("\n\n");
    // printf("Income Values For Months\n");

    // printf("\033[0;32m"); //Set the text to the color green

    //printf("\033[0m"); //Resets the text to default color

    while (1)
    {
        char fname[51];
        printf("\n#################################################################################################--Commands--################################################################################################");
        printf("\n#\ti=insert\n#\tx=Delete all items from memory\n#\tz=Delete given item\n#\tf=find\n#\tl=list\n#\ts=sort\n#\tw=write to file\n#\tr=read from file\n#\tc=clearscreen\n");
        printf("\n############################################################################################################################################################################################################\n");
        scanf("%c", action);
        // fflush(stdin);
        // fgets(action, 30, stdin);
        // int len = strlen(search_term); //where buff is your char array fgets is using
        // if (action[len - 1] == '\n')
        //     action[len - 1] = '\0';

        switch (*action)
        {
        case 'i':
            insert_from_terminal(&first_item_address, &last_item_address, &expense_counter);
            //printf("first address %p", first_item_address);
            printf("\nCreated %d expense\n", expense_counter);
            break;

        case 'l':
            list_all_expenses(first_item_address, &expense_counter, currency_symbols);
            break;

        case 'x':
            delete_all_expenses_from_memory(first_item_address, &expense_counter);
            break;
        case 's':
            sort_by_price(first_item_address, &expense_counter, currency_symbols);
            break;

        case 'w':

            printf("\nEnter file name with extension Ex: Data.txt\n");
            scanf("%50s", fname);
            write_to_file(fname, first_item_address, &expense_counter);
            break;
        case 'r':

            printf("\nEnter file name with extension Ex: Data.txt\n");
            scanf("%50s", fname);
            read_from_file(fname, &first_item_address, &last_item_address, &expense_counter);
            break;

        case 'z':
            printf("Enter index number of item that you want to delete");
            scanf("%d", &selected_item);
            release_selected_expense(first_item_address, &selected_item, &expense_counter);

            break;
        case 'f':
            printf("Enter search term\n");
            fflush(stdin);
            fgets(search_term, 80, stdin);
            int len = strlen(search_term); //where buff is your char array fgets is using
            if (search_term[len - 1] == '\n')
                search_term[len - 1] = '\0';
            search_in_definition(first_item_address, &expense_counter, search_term, currency_symbols);
            break;
        case 'c':
            clearScreen();
            break;
        default:

            break;
        }
    }

    return 0;
}
