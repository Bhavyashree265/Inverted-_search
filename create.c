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
void create_database(hash *HT, F_node *head)
{
    F_node *f_temp = head;
    FILE *fptr;

    char word[25];
    int index;

    while (f_temp != NULL)
    {
        if (file_in_database(HT, f_temp->f_name) == SUCCESS)
        {
            printf("%s -> Database already created\n",f_temp->f_name);
            f_temp = f_temp->link;
            continue;
        }
        fptr = fopen(f_temp->f_name, "r");

        if (fptr == NULL)
        {
            printf("ERROR: Unable to open %s\n",f_temp->f_name);
            f_temp = f_temp->link;
            continue;
        }       

        while (fscanf(fptr, "%24s", word) == 1)
        {
            index = get_index(word);

            /*
             * Main node does not exist
             */
            if (HT[index].H_link == NULL)
            {
                M_node *m_new = malloc(sizeof(M_node));

                if (m_new == NULL)
                {
                    fclose(fptr);
                    return;
                }

                strcpy(m_new->word, word);
                m_new->file_count = 1;
                m_new->main_link = NULL;

                S_node *s_new = malloc(sizeof(S_node));

                if (s_new == NULL)
                {
                    free(m_new);
                    fclose(fptr);
                    return;
                }

                s_new->word_count = 1;
                strcpy(s_new->filename, f_temp->f_name);
                s_new->sub_link = NULL;

                m_new->sub_link = s_new;

                HT[index].H_link = m_new;
            }
            else
            {
                M_node *m_temp = HT[index].H_link;
                M_node *prev = NULL;

                /*
                 * Search main node
                 */
                while (m_temp != NULL)
                {
                    if (strcmp(m_temp->word, word) == 0)
                    {
                        S_node *s_temp = m_temp->sub_link;

                        /*
                         * Search filename
                         */
                        while (s_temp != NULL)
                        {
                            if (strcmp(s_temp->filename,
                                       f_temp->f_name) == 0)
                            {
                                /*
                                 * Same word + same file
                                 */
                                s_temp->word_count++;
                                break;
                            }

                            s_temp = s_temp->sub_link;
                        }

                        /*
                         * Same word but new file
                         */
                        if (s_temp == NULL)
                        {
                            S_node *s_new = malloc(sizeof(S_node));

                            if (s_new == NULL)
                            {
                                fclose(fptr);
                                return;
                            }

                            s_new->word_count = 1;
                            strcpy(s_new->filename, f_temp->f_name);
                            s_new->sub_link = NULL;

                            s_temp = m_temp->sub_link;

                            while (s_temp->sub_link != NULL)
                            {
                                s_temp = s_temp->sub_link;
                            }

                            s_temp->sub_link = s_new;

                            m_temp->file_count++;
                        }

                        break;
                    }

                    prev = m_temp;
                    m_temp = m_temp->main_link;
                }

                /*
                 * Word not present in main list
                 */
                if (m_temp == NULL)
                {
                    M_node *m_new = malloc(sizeof(M_node));

                    if (m_new == NULL)
                    {
                        fclose(fptr);
                        return;
                    }

                    strcpy(m_new->word, word);
                    m_new->file_count = 1;
                    m_new->main_link = NULL;

                    S_node *s_new = malloc(sizeof(S_node));

                    if (s_new == NULL)
                    {
                        free(m_new);
                        fclose(fptr);
                        return;
                    }

                    s_new->word_count = 1;
                    strcpy(s_new->filename, f_temp->f_name);
                    s_new->sub_link = NULL;

                    m_new->sub_link = s_new;

                    prev->main_link = m_new;
                }
            }
        }

        fclose(fptr);

        printf("%s -> Database created successfully\n",f_temp->f_name);
        f_temp = f_temp->link;
    }
}


int get_index(char *word)
{
    if (word[0] >= 'a' && word[0] <= 'z')
    {
        return word[0] - 'a';
    }

    if (word[0] >= 'A' && word[0] <= 'Z')
    {
        return word[0] - 'A';
    }

    return 26;
}