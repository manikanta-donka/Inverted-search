#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int create_database(main_node *hash_table[],Slist **head)
{ 
    char word[50];  // To hold each word read from file

    Slist *list_temp = *head;   // Pointer to traverse file list
    
    // Traverse all files in list
    while(list_temp != NULL)
    {
        FILE *fp = fopen(list_temp->file_name, "r");    // open file

        // Read all word from list
        while(fscanf(fp, "%s", word) != EOF)
        {
            int index;

            // Compute hash index based on first character of word
            if(isupper(word[0]))
                index = word[0] - 'A';
            else if(islower(word[0]))
                index = word[0] - 'a';
            else if(isdigit(word[0]))
                index = 27; // Digits go to index 27
            else
                index = 28; // Special characters 

            main_node *main_temp = hash_table[index];   // Traverse main list at hash index
            main_node *main_prev = NULL;
            int word_found = 0;

            // Search if the word is already exists in main list
            while(main_temp)
            {
                if(strcmp(main_temp->word, word) == 0)
                {
                    word_found = 1;

                    // if word exists, now check if this file is record in sub list
                    sub_node *sub_temp = main_temp->sub_link;
                    sub_node *sub_prev = NULL;
                    int file_found = 0;

                    while(sub_temp)
                    {
                        // If file is already exists in sub list, increment word count
                        if(strcmp(sub_temp->file_name, list_temp->file_name) == 0)
                        {
                            sub_temp->word_count++;
                            file_found = 1;
                            break;
                        }

                        sub_prev = sub_temp;
                        sub_temp = sub_temp->sub_link;
                    }

                    // If file is not present is sub node list, create new sub node.
                    if(!file_found)
                    {
                        sub_node *new_sub = malloc(sizeof(sub_node));
                        if(!new_sub)
                            return FAILURE;

                        strcpy(new_sub->file_name, list_temp->file_name);
                        new_sub->word_count = 1;
                        new_sub->sub_link = NULL;

                        // Link new sub node into sub list
                        if(sub_prev)
                            sub_prev->sub_link = new_sub;
                        else
                            main_temp->sub_link = new_sub;

                        main_temp->file_count++;    // Update file count
                    }
                    break;
                }

                // Move to next main_node
                main_prev = main_temp;
                main_temp = main_temp->main_link;
            }

            // If word is not found create new main node and sub node
            if(!word_found)
            {
                main_node *new_main = malloc(sizeof(main_node));
                sub_node *new_sub = malloc(sizeof(sub_node));

                if(!new_main || !new_sub)
                    return FAILURE;

                // Initialize main node
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = NULL;
                new_main->sub_link = new_sub;

                // Initialize sub node
                strcpy(new_sub->file_name, list_temp->file_name);
                new_sub->word_count = 1;
                new_sub->sub_link = NULL;

                // Insert new main node into hash table
                if(hash_table[index] == NULL)
                    hash_table[index] = new_main;

                else
                {
                    // Append to end of main list 
                    main_temp = hash_table[index];
                    while(main_temp->main_link != NULL)
                        main_temp = main_temp->main_link;
                    main_temp->main_link = new_main;
                }
            }
        }
        fclose(fp); // Close the current file
        list_temp = list_temp->slink;   // Move to next file in list
    }
    return SUCCESS;
}