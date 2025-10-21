// Name: D Manikanta
// Date: 23/07/2025
// Description: Inverted search

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Read and validate files.
int validation(char *argv[], Slist **head)
{
    FILE *fp;

    // Loop through all command line arguments starting from index 1.
    for(int i = 1; argv[i] != NULL; i++)
    {
        // Check if the argument has ".txt" extention.
        char *str = strstr(argv[i], ".");

        if(str != NULL && strcmp(str, ".txt") == 0)
        {
            fp = fopen(argv[i], "r");   // If file valid, open file in read mode
            if(fp != NULL)
            {
                fseek(fp, 0, SEEK_END); // Move to the end of file

                if(ftell(fp))   // If file is not empty
                {
                    fclose(fp);

                    // If linked list is empty, insert first file
                    if(*head == NULL)
                    {
                        Slist *new = malloc(sizeof(Slist));
                        if(new == NULL)
                            return FAILURE;

                        strcpy(new->file_name, argv[i]);
                        new->slink = NULL;
                        *head = new;
                        printf("INFO: File %s is successfully inseted in list.\n\n", argv[i]);
                    }
                    else
                    {
                        // Traverse list to check for duplicate file or add new file.
                        Slist *temp = *head;
                        while(temp)
                        {
                            if(strcmp(temp->file_name, argv[i]) == 0)
                            {
                                printf("INFO: File %s is duplicate file.\n\n", argv[i]);
                                break;
                            }
                            else if(temp->slink == NULL)
                            {
                                Slist *new = malloc(sizeof(Slist));
                                if(new == NULL)
                                    return FAILURE;

                                strcpy(new->file_name, argv[i]);

                                new->slink = NULL;
                                temp->slink = new;

                                printf("INFO: File %s is successfully inseted in list.\n\n", argv[i]);

                                break;
                            }
                            temp = temp->slink;
                        }
                    }
                }
                else
                {
                    // File is empty.
                    printf("Info: File %s is empty.\n\n", argv[i]);
                    continue;
                }
            }
            else
            {
                // File couldn't be opened.
                printf("Info: File %s cannot be opened\n\n", argv[i]);
                continue;
            }
        }
        else
        {
            // File is not a text file.
            printf("Info: File %s ia not a text file\n\n", argv[i]);
            continue;
        }
        //return SUCCESS;
    }

    // Print linked list of file names.
    Slist *temp = *head;
        // Traverse the list and print each node's data
    while(temp)
    {
        printf("%s -> ", temp->file_name);  // Print current node's data
        temp = temp->slink;             // Move to the next node
    }

    printf("NULL\n\n");  // Indicate the end of the list
    
}

int main(int argc, char *argv[])
{
    Slist *head = NULL; // Head of file list
    main_node *hash_table[28] = {NULL}; // Hash table for word index
    int choice; // Menu choice
    int flag = 0;   // Indicate if DB is created.
    int flag1 = 0;  // Indicate if DB is updated.

    // If no arguments passed
    if(argv[1] == NULL)
    {
        printf("Pass correct argumants.\n\n");
        printf("./a.out file1.txt file2.txt ....\n\n");
    }
    else
    {
        // Validate the input files
        if(validation(argv, &head))
        {
            printf("INFO: Read and validation successfull\n\n");
            while(1)
            {
                printf("1. Create Database\n2. Display Database\n3. Save Database\n4. Search Database\n5. Update Database\n6. Exit\nEnter your choice: ");
                scanf("%d", &choice);

                switch(choice)
                {
                    case 1: 
                        if(flag == 0)
                        {
                            if(create_database(hash_table, &head) == SUCCESS)
                            {
                                flag = 1;
                                printf("INFO: Database created successfully.\n\n");
                            }
                            else
                                printf("INFO: Database creation failed.\n\n");
                        }
                        else
                            printf("INFO: Database is already created.\n\n");

                        break;

                    case 2:
                        if(display_database(hash_table) == SUCCESS)
                            printf("INFO: Display Database successfull.\n\n");

                        else
                            printf("INFO: Display Database failed.\n\n");
                        
                        break;

                    case 3:
                        char new_file[25];
                        printf("Enter the file name: ");
                        scanf("%s", new_file);

                        char *ptr = strstr(new_file, ".");
                        if(ptr != NULL && strcmp(ptr, ".txt") == 0)
                        {
                            if(save_database(new_file, hash_table) == SUCCESS)
                                printf("INFO: Database saved successfully\n\n");
                            else
                                printf("INFO: Database saved faild\n\n");
                        }
                        else
                            printf("INFO: File %s is not a .txt file\n\n", new_file);

                        break;

                    case 4:
                        char new_word[20];
                        printf("Enter the word to search: ");
                        scanf("%s", new_word);
                        
                        if(search_database(new_word, hash_table) == SUCCESS)
                            printf("INFO: word '%s' is found.\n\n", new_word);
                        else    
                            printf("INFO: word '%s' is not found.\n\n", new_word);

                        break;

                    case 5:
                        
                        if(flag == 0)
                        {
                            char data_file[25];
                            printf("Enter the data base file name: ");
                            scanf("%s", data_file);

                            char *ptr1 = strstr(data_file, ".");

                            if(ptr1 != NULL && strcmp(ptr1, ".txt") == 0)
                            {
                                if(flag1 == 0)
                                {
                                    if(update_database(data_file, hash_table, &head) == SUCCESS)
                                    {
                                        flag1 = 1;
                                        printf("INFO: Update database is successfull.\n\n");
                                    }
                                    else
                                        printf("INFO: Update database is failed.\n\n");
                                }
                                else
                                    printf("INFO: Database is already updated.\n\n");
                                
                            }
                            else
                                printf("INFO: File %s is not a .txt file\n\n", data_file);
                        }
                        else
                        {
                            printf("INFO: Database not empty.\n\n");
                        }
                        
                        break;
                    case 6:
                        return SUCCESS;
                        break;

                    default:
                        printf("Invalid choice...!\n\n");

                }
            }
        }
        
    }
}