#include "inverted.h"


void validate_files(char *argv[], F_node **head)
{
    int i = 1;
    FILE *fptr;
    char *ext;

    while (argv[i] != NULL)
    {
        /*
         * Check .txt extension
         */
        ext = strrchr(argv[i], '.');

        if (ext == NULL || strcmp(ext, ".txt") != 0)
        {
            printf("%s -> Not a .txt file\n", argv[i]);
            i++;
            continue;
        }

        /*
         * Check duplicate
         */
        if (check_duplicates(*head, argv[i]) == SUCCESS)
        {
            printf("%s -> Duplicate file\n", argv[i]);
            i++;
            continue;
        }

        /*
         * Check file exists
         */
        fptr = fopen(argv[i], "r");

        if (fptr == NULL)
        {
            printf("%s -> File does not exist\n", argv[i]);
            i++;
            continue;
        }

        /*
         * Check empty file
         */
        fseek(fptr, 0, SEEK_END);

        if (ftell(fptr) == 0)
        {
            printf("%s -> File is empty\n", argv[i]);

            fclose(fptr);

            i++;
            continue;
        }

        fclose(fptr);

        /*
         * Store valid file
         */
        if (insert_last(head, argv[i]) == SUCCESS)
        {
            printf("%s -> File added successfully\n", argv[i]);
        }
        else
        {
            printf("%s -> File insertion failed\n", argv[i]);
        }

        i++;
    }
}


int insert_last(F_node **head, char *f_name)
{
    F_node *new = malloc(sizeof(F_node));

    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->f_name, f_name);

    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    F_node *temp = *head;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}


int check_duplicates(F_node *head, char *f_name)
{
    F_node *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->f_name, f_name) == 0)
        {
            return SUCCESS;
        }

        temp = temp->link;
    }

    return FAILURE;
}


int print_filenames(F_node *head)
{
    F_node *temp = head;

    if (temp == NULL)
    {
        printf("head -> NULL\n");
        return FAILURE;
    }

    printf("head -> ");

    while (temp != NULL)
    {
        printf("%s -> ", temp->f_name);

        temp = temp->link;
    }

    printf("NULL\n");

    return SUCCESS;
}