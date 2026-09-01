#include "inverted.h"

int main(int argc, char *argv[])
{
    F_node *head = NULL;
    hash HT[27];

    int option;
    int create_flag = 0;
    int update_flag = 0;

    /*
     * Check CLA
     */
    if (argc <= 1)
    {
        printf("ERROR: No input files passed\n");
        printf("Usage: ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    /*
     * Initialize hash table
     */
    for (int i = 0; i < 27; i++)
    {
        HT[i].index = i;
        HT[i].H_link = NULL;
    }

    /*
     * Validate input files
     */
    validate_files(argv, &head);

    /*
     * Print validated files
     */
    printf("\nValidated files:\n");
    print_filenames(head);

    /*
     * No valid files
     */
    if (head == NULL)
    {
        printf("ERROR: No valid input files\n");
        return FAILURE;
    }

    do
    {
        printf("\nSelect your choice among following operations:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Save Database\n");
        printf("4. Search\n");
        printf("5. Update Database\n");
        printf("6. Exit\n\n");

        printf("Enter your choice : ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:

                /*
                 * Create database only once
                 */
                if (create_flag == 1)
                {
                    printf("INFO : Database already created\n");
                }
                else
                {
                    create_database(HT, head);

                    create_flag = 1;

                    printf("INFO : Database creation completed\n");
                }

                break;


            case 2:

                display_database(HT);

                break;


            case 3:

                if (create_flag == 0 && update_flag == 0)
                {
                    printf("INFO : Database is empty\n");
                }
                else
                {
                    save_database(HT);
                }

                break;


            case 4:

                if (create_flag == 0 && update_flag == 0)
                {
                    printf("INFO : Database is empty\n");
                }
                else
                {
                    search_database(HT);
                }

                break;


            case 5:

                /*
                 * Update can be performed only once
                 */
                if (update_flag == 1)
                {
                    printf("INFO : Database already updated\n");
                }
                else
                {
                    if (update_database(HT, &head) == SUCCESS)
                    {
                        update_flag = 1;
                        create_flag = 1;

                        printf("\nUpdated file list:\n");
                        print_filenames(head);
                    }
                }

                break;


            case 6:

                printf("Exiting...\n");
                printf("------------------------------------------------\n");
                printf("     THANKYOU FOR USING THIS APPLICATION\n");
                printf("------------------------------------------------\n");

                break;


            default:

                printf("INFO : Please enter a valid option\n");
        }

    } while (option != 6);

    return SUCCESS;
}