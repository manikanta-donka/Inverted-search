#include <stdio.h>
#include "main.h"

int display_database(main_node *hash_table[])
{
    printf("Index\tWord\t\tFile count\tFile name\tWord count\n\n");

    // Loop through each index in hash table.
    for(int i = 0; i < 28; i++)
    {
        // Check if any word store at this index
        if(hash_table[i] != NULL)
        {
            main_node *main_temp = hash_table[i];   // Pointer to traverse main list

            // Traverse all words stored at current index
            while(main_temp != NULL)
            {
                // Print main node info: index, word, file count.
                printf("%d\t%s\t\t%d\t\t", i, main_temp->word, main_temp->file_count);

                sub_node *sub_temp = main_temp->sub_link;   // Pointer to traverse sub list
                while(sub_temp)
                {
                    // Print sub node info: file name, word count.
                    printf("%s\t\t%d\n\n", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                main_temp = main_temp->main_link;   // Move to the next word in this index.
            }
        }
    }
    return SUCCESS;
}