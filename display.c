#include "inverted.h"

void display_database(hash *HT)
{
    int i;
    M_node *m_temp;
    S_node *s_temp;

    printf("\n====================================================================\n");
    printf("                      INVERTED SEARCH DATABASE\n");
    printf("====================================================================\n");

    printf("%-8s %-15s %-12s %-20s %-12s\n",
           "Index", "Word", "File Count", "File Name", "Word Count");

    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < 27; i++)
    {
        m_temp = HT[i].H_link;

        while (m_temp != NULL)
        {
            s_temp = m_temp->sub_link;

            while (s_temp != NULL)
            {
                printf("%-8d %-15s %-12d %-20s %-12d\n",
                       HT[i].index,
                       m_temp->word,
                       m_temp->file_count,
                       s_temp->filename,
                       s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            m_temp = m_temp->main_link;
        }
    }

    printf("====================================================================\n");
}