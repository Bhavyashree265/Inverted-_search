#include "inverted.h"


static int file_in_database(hash *HT, char *filename)
{
    int i;

    M_node *m_temp;
    S_node *s_temp;

    for (i = 0; i < 27; i++)
    {
        m_temp = HT[i].H_link;

        while (m_temp != NULL)
        {
            s_temp = m_temp->sub_link;

            while (s_temp != NULL)
            {
                if (strcmp(s_temp->filename, filename) == 0)
                {
                    return SUCCESS;
                }

                s_temp = s_temp->sub_link;
            }

            m_temp = m_temp->main_link;
        }
    }

    return FAILURE;
}


static int check_backup_format(FILE *fptr)
{
    int ch;

    /*
     * Check first non-space character
     */
    rewind(fptr);

    do
    {
        ch = fgetc(fptr);
    }
    while (ch == ' ' || ch == '\n' ||
           ch == '\t' || ch == '\r');

    if (ch != '#')
    {
        return FAILURE;
    }

    /*
     * Check last non-space character
     */
    fseek(fptr, -1, SEEK_END);

    while (1)
    {
        ch = fgetc(fptr);

        if (ch == EOF)
        {
            return FAILURE;
        }

        if (ch != ' ' && ch != '\n' &&
            ch != '\t' && ch != '\r')
        {
            break;
        }

        fseek(fptr, -2, SEEK_CUR);
    }

    if (ch != '#')
    {
        return FAILURE;
    }

    return SUCCESS;
}


int update_database(hash *HT, F_node **head)
{
    char backup_file[50];

    FILE *fptr;

    int index;
    int file_count;
    int word_count;

    char word[25];
    char filename[20];

    /*
     * New files only
     */
    F_node *new_head = NULL;

    F_node *temp;


    printf("Enter the backup file name : ");
    scanf("%49s", backup_file);


    /*
     * Check extension
     */
    char *ext = strrchr(backup_file, '.');

    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("ERROR: Backup file should have .txt extension\n");
        return FAILURE;
    }


    /*
     * Check backup exists
     */
    fptr = fopen(backup_file, "r");

    if (fptr == NULL)
    {
        printf("ERROR: Backup file does not exist\n");
        return FAILURE;
    }


    /*
     * Check backup format
     */
    if (check_backup_format(fptr) == FAILURE)
    {
        printf("ERROR: Invalid backup file\n");

        fclose(fptr);

        return FAILURE;
    }


    /*
     * Restore old database
     */
    rewind(fptr);

    while (fscanf(fptr, "#%d;%24[^;];%d",&index, word, &file_count) == 3)
    {
        M_node *m_new = malloc(sizeof(M_node));

        if (m_new == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

        strcpy(m_new->word, word);

        m_new->file_count = file_count;

        m_new->sub_link = NULL;
        m_new->main_link = NULL;


        S_node *s_tail = NULL;


        for (int i = 0; i < file_count; i++)
        {
            if (fscanf(fptr, ";%19[^;];%d",filename, &word_count) != 2)
            {
                free(m_new);

                fclose(fptr);

                return FAILURE;
            }


            S_node *s_new = malloc(sizeof(S_node));

            if (s_new == NULL)
            {
                free(m_new);

                fclose(fptr);

                return FAILURE;
            }


            strcpy(s_new->filename, filename);

            s_new->word_count = word_count;

            s_new->sub_link = NULL;


            if (m_new->sub_link == NULL)
            {
                m_new->sub_link = s_new;

                s_tail = s_new;
            }
            else
            {
                s_tail->sub_link = s_new;

                s_tail = s_new;
            }
        }


        /*
         * Insert main node into hash table
         */
        if (HT[index].H_link == NULL)
        {
            HT[index].H_link = m_new;
        }
        else
        {
            M_node *m_temp = HT[index].H_link;

            while (m_temp->main_link != NULL)
            {
                m_temp = m_temp->main_link;
            }

            m_temp->main_link = m_new;
        }


        fscanf(fptr, "\n");
    }


    fclose(fptr);

    printf("Database restored successfully\n");


    /*
     * Check CLA files
     *
     * Existing files -> do not process
     * New files      -> new_head
     */
    temp = *head;

    while (temp != NULL)
    {
        if (file_in_database(HT, temp->f_name) == SUCCESS)
        {
            printf("%s -> Already updated\n",
                   temp->f_name);
        }
        else
        {
            printf("%s -> New file\n",
                   temp->f_name);

            insert_last(&new_head, temp->f_name);
        }

        temp = temp->link;
    }


    /*
     * Only NEW files are sent to create_database()
     */
    if (new_head != NULL)
    {
        create_database(HT, new_head);

        printf("New files added to database successfully\n");
    }
    else
    {
        printf("INFO : No new files to update\n");
    }


    /*
     * IMPORTANT:
     *
     * From now onwards head must contain
     * ONLY the new files.
     *
     * Example:
     *
     * Before:
     * head -> file1 -> file2 -> file3 -> NULL
     *
     * After update:
     * head -> file3 -> NULL
     */
    while (*head != NULL)
    {
        temp = *head;

        *head = (*head)->link;

        free(temp);
    }

    *head = new_head;


    return SUCCESS;
}