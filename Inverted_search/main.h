#ifndef IS_H
#define IS_H


#define SUCCESS 0
#define FAILURE -1


typedef struct main
{
    int file_count;
    char word[25];
    struct sub *sub_link;
    struct main *main_link;
} main_node;

typedef struct sub
{
    int word_count;
    char file_name[25];
    struct sub *sub_link;
} sub_node;

typedef struct hash
{
    int key;
    struct main *hash_link;
} hash_t;

typedef struct file
{
    char file_name[25];
    struct file *slink;
} Slist;


int validation(char *argv[], Slist **head);
int create_database(main_node *arr[],Slist **head);
int display_database(main_node *arr[]);
int save_database(char *file_name, main_node *arr[]);
int search_database(char *new_word, main_node *hash_table[]);
int update_database(char *data_file, main_node *hash_table[], Slist **head);

#endif