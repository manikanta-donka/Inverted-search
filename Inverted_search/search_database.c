#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

int(search_database(char *new_word, main_node *hash_table[]))
{
    // Compute hash index based on first character of word
    int index;
    if(isupper(new_word[0]))
        index = new_word[0] - 'A';
    else if(islower(new_word[0]))
        index = new_word[0] - 'a';
    else if(isdigit(new_word[0]))
        index = 27;
    else
        index = 28;

    int flag = 0;
        
    main_node *main_temp = hash_table[index];

    // Traverse main list at this index
    while(main_temp)
    {
        // Compare each word in the main list with the target word
        if(strcmp(main_temp->word, new_word) == 0)
        {
            flag = 1;// Word found

            // Print how many files the word is present in
            printf("Word %s is present in %d files.\n\n", main_temp->word, main_temp->file_count);

            sub_node *sub_temp = main_temp->sub_link;

            // Traverse sub list and print word count for each file
            while(sub_temp)
            {
                printf("In %s word is present in %d times.\n\n", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->sub_link;
            }
            break;
        }
        main_temp = main_temp->main_link;
    }
        
    // Return status based on whether the word was found
    if(flag == 1)
        return SUCCESS;
    else
        return FAILURE;
}