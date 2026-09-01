#include "inverted.h"

void search_database(hash *HT)
{
    char word[25];
    int index;

    M_node *m_temp;
    S_node *s_temp;

    printf("Enter the word to search : ");
    scanf("%24s", word);

    index = get_index(word);

    if (HT[index].H_link == NULL)
    {
        printf("INFO : Word '%s' not found in database\n", word);
        return;
    }

    m_temp = HT[index].H_link;

    while (m_temp != NULL)
    {
        if (strcmp(m_temp->word, word) == 0)
        {
            printf("\nWord '%s' found in database\n", word);
            printf("File count : %d\n", m_temp->file_count);

            s_temp = m_temp->sub_link;

            while (s_temp != NULL)
            {
                printf("File name  : %s\n", s_temp->filename);
                printf("Word count : %d\n", s_temp->word_count);

                s_temp = s_temp->sub_link;
            }

            return;
        }

        m_temp = m_temp->main_link;
    }

    printf("INFO : Word '%s' not found in database\n", word);
}