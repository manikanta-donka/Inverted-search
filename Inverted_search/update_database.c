#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int update_database(char *data_file, main_node *hash_table[], Slist **head)
{
    FILE *fp = fopen(data_file, "r");
    if(fp == NULL)
    {
        printf("INFO: Unable to open file\n\n");
        return FAILURE;
    }

    // Check if the file starts with '#' to validate saved file format
    char first;
    first = fgetc(fp);
    if (first != '#')
    {
        printf("INFO: File %s is not a saved file \n\n", data_file);
        fclose(fp);
        return FAILURE;
    }

    // Move file pointer back to beginning after validation
    rewind(fp);

    char ch;

    // Read until end of file
    while((ch = fgetc(fp)) != EOF)
    {
        // Each word block starts with '#'
        if(ch == '#')
        {
            int index;

            // Read hash index
            fscanf(fp, "%d;", &index);

            // Allocate memory for new main_node
            main_node *new_main = malloc(sizeof(main_node));
            if(new_main == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            // Read word and file count into new_main
            fscanf(fp, "%[^;];%d;", new_main->word, &new_main->file_count);
            new_main->main_link = NULL;
            new_main->sub_link = NULL;

            sub_node *prev_sub = NULL;

            // Loop through each file the word appeared in
            for(int i = 0; i < new_main->file_count; i++)
            {
                // Allocate memory for new sub_node
                sub_node *new_sub = malloc(sizeof(sub_node));
                if(new_sub == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                // Read file name and word count for this file
                if (fscanf(fp, "%[^;];%d;", new_sub->file_name, &new_sub->word_count) != 2)
                {
                    free(new_sub);
                    continue;
                }

                // Remove this file from the linked list if already present (to avoid duplicates)
                Slist *temp_list = *head;
                Slist *prev_list = NULL;
                while(temp_list)
                {
                    if(strcmp(temp_list->file_name, new_sub->file_name) == 0)
                    {
                        if(prev_list)
                            prev_list->slink = temp_list->slink;
                        else
                            *head = temp_list->slink;

                        free(temp_list);    // Free the matched node
                        break;
                    }
                    else
                    {
                        prev_list = temp_list;
                        temp_list = temp_list->slink;
                    }
                }

                new_sub->sub_link = NULL;

                // Append sub_node to main_node’s sub_link list
                if(new_main->sub_link == NULL)
                    new_main->sub_link = new_sub;
                else
                    prev_sub->sub_link = new_sub;

                prev_sub = new_sub;
            }

            // Insert the new_main node into the hash table
            if(hash_table[index] == NULL)
                hash_table[index] = new_main;
            else
            {
                // Traverse to the end of the linked list at this index
                main_node *temp = hash_table[index];
                while(temp->main_link)
                    temp = temp->main_link;

                temp->main_link = new_main;
            }

            // Read and discard next character unless it's '#' or EOF
            int c = fgetc(fp);
            if(c != '#' && c != EOF)
                ungetc(c, fp);
        }
    }

    //Print remaining file list for verification Slist *temp = *head; // Traverse the list and print each node's data
    while(temp)
    {
        printf("%s -> ", temp->file_name);  // Print current node's data
        temp = temp->slink;             // Move to the next node
    }

    printf("NULL\n\n");  // Indicate the end of the list

    fclose(fp);
    return SUCCESS;
}