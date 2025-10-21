#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int save_database(char *file_name, main_node *hash_table[])
{
    FILE *fp = fopen(file_name, "w");   // Open file in write mode
    if(fp == NULL)
       printf("failed to open save file");
    
    // Loop through each index in hash table    
    for(int i = 0; i < 28; i++)
    {
        // Check if there ia a list in current index.
        if(hash_table[i] != NULL)
        {
            main_node *main_temp = hash_table[i];   // Pointer to traverse main list

            // traverse all main node at this index
            while(main_temp != NULL)
            {
                sub_node *sub_temp = main_temp->sub_link;   // Pointer to traverse sub list

                // Write main node data in the format:
                // #index;word;file_count
                fprintf(fp, "%c%d;%s;%d", '#', i, main_temp->word, main_temp->file_count);

                // For each sub node (file details), write:
                // ;filename;word_count
                while(sub_temp)
                {
                    fprintf(fp, ";%s;%d", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }

                // End the line with '#\n'
                fprintf(fp, "%c%c", '#','\n');

                // Move to next main node
                main_temp = main_temp->main_link;
            }
        }
    }
    fclose(fp); // Close the file after writing
    return SUCCESS;
}

