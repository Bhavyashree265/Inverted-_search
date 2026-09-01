#include "inverted.h"

void save_database(hash *HT)
{
    char filename[50];
    FILE *fptr;

    int i;

    M_node *m_temp;
    S_node *s_temp;

    printf("Enter the backup file name : ");
    scanf("%49s", filename);

    /*
     * Check .txt extension
     */
    char *ext = strrchr(filename, '.');

    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("ERROR: Backup file should have .txt extension\n");
        return;
    }

    /*
     * Open backup file
     */
    fptr = fopen(filename, "w");

    if (fptr == NULL)
    {
        printf("ERROR: Unable to open backup file\n");
        return;
    }

    /*
     * Traverse hash table
     */
    for (i = 0; i < 27; i++)
    {
        m_temp = HT[i].H_link;

        while (m_temp != NULL)
        {
            /*
             * Print:
             * #index;word;file_count
             */
            fprintf(fptr, "#%d;%s;%d",
                    HT[i].index,
                    m_temp->word,
                    m_temp->file_count);

            /*
             * Traverse sub nodes
             */
            s_temp = m_temp->sub_link;

            while (s_temp != NULL)
            {
                /*
                 * Print:
                 * ;filename;word_count
                 */
                fprintf(fptr, ";%s;%d",
                        s_temp->filename,
                        s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            /*
             * End of each main node
             */
            fprintf(fptr, ";#\n");

            m_temp = m_temp->main_link;
        }
    }

    fclose(fptr);

    printf("Database saved successfully\n");
}