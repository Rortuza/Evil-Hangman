#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_vector.h"
#include "my_string.h"
#define size 30

typedef struct node Node;
struct node{
    MY_STRING key;
    GENERIC_VECTOR word;
    Node* next;
};

void clear_keyboard_buffer(void);
void remove_vector_buffer(GENERIC_VECTOR hVector);
void remove_string_buffer(MY_STRING hMy_string);
Node* insert(Node* head, MY_STRING key, MY_STRING word);
void list_remove(Node* *head);
Node* search(Node* head, MY_STRING key, MY_STRING word);
Node* max_node_pop_back(Node* *head);


int main(int argc, char* argv[]){
    //GENERIC_VECTOR hVector;
    GENERIC_VECTOR hGame;
    MY_STRING hMy_string;
    MY_STRING hMy_string_key;
    MY_STRING word_string;
    MY_STRING test;
    MY_STRING string_temp;
    FILE* fin;
    int word_len;
    int guess;
    int isEmpty;
    int succ;
    char again;
    char num_of_word[26];
    Node* head = NULL;
    Node* temp = NULL;
    int i;
    int j;
    int k;


    hMy_string = my_string_init_default();
    word_string = my_string_init_default();
    hMy_string_key = my_string_init_default();
    test=my_string_init_default();
    string_temp=my_string_init_default();
    hGame = generic_vector_init_default(test->Item_destroy, test->assignment);
    GENERIC_VECTOR length[size];
    
    for(i = 0; i < size; i++){
        length[i] = generic_vector_init_default(hMy_string->Item_destroy, hMy_string->assignment);
    }

    fin = fopen("/Users/ryhanmortuza/Desktop/DailyZero/DailyZero/Dailies Comp 2/Evil Hangman/Evil Hangman/dictionary.txt", "r");
    if(fin == NULL){
        printf("ERROR: Failed to open file. Exiting game.\n");
        exit(1);
    }
    while(hMy_string->extraction(hMy_string, fin))
    {
        i = hMy_string->get_size(hMy_string);
        length[i]->push_back(length[i], hMy_string);
    }

   /* for (i = 0; i < size; i++)
    {
        printf("word length: %d size: %d\n", i+1 , generic_vector_get_size(length[i]));
    }*/
    
    hMy_string->destroy(&hMy_string);

    do
    {
        succ = 0;
        printf("\nRyhan Mortuza presents...\nEVIL HANGMAN!\n");
        printf("\n\n");
        
        printf("Please enter a word length (Enter -1 to quit):\n");
        scanf("%d", &word_len);
        if(word_len == -1){
            printf("Exiting game. Thanks for playing!\n");
            exit(0);
        }
        clear_keyboard_buffer();

        while (word_len >= size || word_len < 0 || length[word_len]->get_size(length[word_len]) == 0)
        {
            printf("Please choose a valid word length:\n");
            scanf("%d", &word_len);
            clear_keyboard_buffer();
        }
        printf("Please enter the number of guess you'd like:\n");
        scanf("%d", &guess);
        clear_keyboard_buffer();
        while (guess <= 0)
        {
            printf("Please enter a valid number:\n");
            scanf("%d", &guess);
            clear_keyboard_buffer();
        }
        printf("Your word length: %d.\n", word_len);
        printf("There are %d possibilities for that word length and you\nhave %d guesses.... good luck.\n", length[word_len]->get_size(length[word_len]), guess);
        
        remove_vector_buffer(hGame);

        for (i = 0; i<length[word_len]->get_size(length[word_len]); i++){
            hGame->push_back(hGame, (MY_STRING)length[word_len]->at(length[word_len], i));
        }
        
        for (i = 0; i<word_len; i++){
            word_string->push_back(word_string, '-');
        }
        
        for (i = 0; i < guess; i++){
            printf("Enter letter: ");
            scanf("%c", &num_of_word[i]);
            clear_keyboard_buffer();

            num_of_word[i] = toupper(num_of_word[i]);

            if (i != 0){
                for (j = 0; j < i; j++){
                    if (num_of_word[i] == num_of_word[j]){
                        printf("Letter already chosen, please choose new letter: ");
                        scanf("%c", &num_of_word[i]);
                        num_of_word[i] = toupper(num_of_word[i]);
                        clear_keyboard_buffer();
                        j=0;
                    }
                }
            }
            
            if (i == 0){
                printf("%c\n", num_of_word[i]);
            }
            
            else{
                for (j = 0; j <= i; j++){
                    printf("%c ", num_of_word[j]);
                }
                printf("\n");
            }

            for (j = 0; j < hGame->get_size(hGame); j++){
                for (k = 0; k < ((MY_STRING)hGame->at(hGame, j))->get_size(hGame->at(hGame, j)); k++){
                    test->push_back(test, *((MY_STRING)hGame->at(hGame, j))->at(hGame->at(hGame, j), k));
                }


                for (k = 0; k < word_len; k++){
                    if (*test->at(test, k) == tolower(num_of_word[i])){
                        hMy_string_key->push_back(hMy_string_key, tolower(num_of_word[i]));
                    }
                    
                    else{
                        hMy_string_key->push_back(hMy_string_key, '-');
                    }
                }

                head = search(head, hMy_string_key, (MY_STRING)hGame->at(hGame, j));

                for (k = 0; k < word_len; k++){
                    hMy_string_key->pop_back(hMy_string_key);
                }
                remove_string_buffer(test);
            }


            if (head->next != NULL){
                temp = max_node_pop_back(&head);
                list_remove(&head);
                head = temp;
            }

            remove_vector_buffer(hGame);

            for (k = 0; k < head->word->get_size(head->word); k++){
                hGame->push_back(hGame, (MY_STRING)(head->word->at(head->word, k)));
            }
            
            isEmpty = 1;

            for (k = 0; k < head->key->get_size(head->key); k++){
                if (*head->key->at(head->key, k) != '-'){
                    isEmpty = 0;
                    break;
                }
            }
            if (isEmpty != 1){
                guess++;
                printf("Correct!\n");
                for (k = 0; k < word_string->get_size(word_string); k++){
                    string_temp->push_back(string_temp, *word_string->at(word_string, k));
                }
                
                remove_string_buffer(word_string);
                
                for (k = 0; k < string_temp->get_size(string_temp); k++){
                    if (*string_temp->at(string_temp, k) != '-'){
                        word_string->push_back(word_string, *string_temp->at(string_temp, k));
                    }
                    else{
                        word_string->push_back(word_string, *head->key->at(head->key, k));
                    }
                }
                remove_string_buffer(string_temp);
                for (k = 0; k < word_string->get_size(word_string); k++){
                    if(*word_string->at(word_string, k) == '-'){
                        succ = 0;
                        break;
                    }
                    
                    else{
                        succ = 1;
                    }
                }
                if (succ == 1){
                    printf("Word solved, congratulations!\n");
                    list_remove(&head);
                    break;
                }
                else{
                    printf("You have %d guesses left.\n\n", guess - i - 1);
                }
            }
            else{
                printf("Incorrect! You have %d guesses left.\n\n", guess - i-1);
            }
            list_remove(&head);
            printf("%s\n", word_string->c_str(word_string));

        }
        if (succ == 0){
            printf("Number of guesses has run out. The word was: %s.\n", ((MY_STRING)hGame->at(hGame, 0))->c_str(hGame->at(hGame, rand() % hGame->get_size(hGame))));
        }
        remove_string_buffer(word_string);
        fclose(fin);
        printf("Do you want to play again? (Press Y for yes, press any other key to quit)\n");
        scanf("%c", &again);
        clear_keyboard_buffer();
    }
    while(tolower(again) == 'y');

    printf("\nExiting game, thanks for playing!\n");

    
    word_string->destroy(&word_string);
    hMy_string_key->destroy(&hMy_string_key);
    test->destroy(&test);
    string_temp->destroy(&string_temp);
    return 0;
}

void clear_keyboard_buffer(void){
    char c;
    scanf("%c", &c);
    while(c!= '\n'){
        scanf("%c", &c);
    }
    return;
}

Node* insert(Node* head, MY_STRING key, MY_STRING word)
{
    int i;
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        printf("Failed to create new node.\n");
        exit(1);
    }
    else
    {
        temp->key = my_string_init_default();
        temp->word = generic_vector_init_default(temp->key->Item_destroy, temp->key->assignment);

        for (i = 0; i<key->get_size(key); i++)
        {
            temp->key->push_back(temp->key, (*key->at(key, i)));
        }
        temp->word->push_back(temp->word, word);

        temp->next = head;
        head = temp;
        return head;
    }
}

void list_remove(Node* *head){
    Node* temp = (Node*)*head;
    Node* temp2 = temp;

    while (temp != NULL){
        temp2 = temp->next;
        temp->key->destroy(&temp->key);
        temp->word->destroy(&temp->word);
        free(temp);
        temp = temp2;
    }
    *head = NULL;
}

Node* search(Node* head, MY_STRING keyFind, MY_STRING word){
    Node* temp;
    temp = head;

    if (temp == NULL){
        temp = insert(temp, keyFind, word);
        return temp;
    }
    else{
        while (temp != NULL){
            if(temp->key->string_compare(temp->key, keyFind) == 0){
                temp->word->push_back(temp->word, word);
                return head;
            }
            else{
                temp = temp->next;
            }
        }
        temp = head;
        temp = insert(temp, keyFind, word);
        return temp;
    }
}


Node* max_node_pop_back(Node** head){
    Node* temp = (Node*)* head;
    Node* temp2 = temp;
    int max;

    if (temp != NULL){
        if (temp->next == NULL){
            return temp;
        }
        else{
            max = temp->word->get_size(temp->word);
            temp = temp->next;

            while (temp != NULL){
                if (temp->word->get_size(temp->word) > max){
                    max = temp->word->get_size(temp->word);
                    temp2 = temp;
                    temp = temp->next;
                }
                else{
                    temp = temp->next;
                }
            }
            
            temp = (Node*)* head;
            if (temp == temp2){
                *head = temp->next;
                temp2->next = NULL;
                return temp2;
            }
            else{
                while (temp->next != temp2){
                    temp = temp->next;
                }
                temp->next = temp->next->next;
                temp2->next = NULL;
                return temp2;
            }
        }

    }
    return temp2;
}
void remove_vector_buffer(GENERIC_VECTOR hVector){
    if (hVector->get_size(hVector) > 0){
        while (hVector->get_size(hVector) > 0){
            hVector->pop_back(hVector);
        }
    }
}

void remove_string_buffer(MY_STRING hMy_string){
    if (hMy_string->get_size(hMy_string) > 0){
        while (hMy_string->get_size(hMy_string) > 0){
            hMy_string->pop_back(hMy_string);
        }
    }
}


/*
// Lab 7 Checkpoint 1
#include <stdio.h>
#include <stdlib.h>
#include "my_vector.h"
#include "my_string.h"
#define size 30


int main(int argc, char* argv[])
{
    GENERIC_VECTOR hVector[size];
    int i, length;
 
    MY_STRING hMy_string = NULL;
    FILE* fin;
    hMy_string = my_string_init_default();
    fin = fopen("/Users/ryhanmortuza/Desktop/DailyZero/DailyZero/Dailies Comp 2/Evil Hangman/Evil Hangman/dictionary.txt", "r");
 
    for (i = 0; i < size; i++)
    {
        hVector[i] = generic_vector_init_default(hMy_string -> Item_destroy, hMy_string -> assignment);
        if (hVector[i] == NULL)
        {
            exit(1);
        }
    }
    while (my_string_extraction(hMy_string, fin))
    {
        //printf("1\n");
        length = my_string_get_size(hMy_string);
        generic_vector_push_back(hVector[length-1], hMy_string);
    }
 
    for (i = 0; i < size; i++)
    {
        printf("word length: %d size: %d\n", i+1 , generic_vector_get_size(hVector[i]));
    }
 
    //for (i = 0; i < size; i++)
      //  generic_vector_destroy(&(hVector[i]));
 
    fclose(fin);
  my_string_destroy(&hMy_string);
 
    return 0;
}
*/


//Lab 8

/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_vector.h"
#include "my_string.h"


int main(int argc, char* argv[]) {
 
    MY_STRING str1 = my_string_init_c_str("This");
    MY_STRING key_orig = my_string_init_c_str("----");
    MY_STRING key_modified = my_string_init_default();
    get_word_key_value(key_orig, key_modified, str1, 'T');
    
    MY_STRING str2 = my_string_init_c_str("Project");
    MY_STRING key_orig2 = my_string_init_c_str("-------");
    MY_STRING key_modified2 = my_string_init_default();
    get_word_key_value(key_orig2, key_modified2, str2, 'r');
    
    MY_STRING str3 = my_string_init_c_str("Contains");
    MY_STRING key_orig3 = my_string_init_c_str("Cont----");
    MY_STRING key_modified3 = my_string_init_default();
    get_word_key_value(key_orig3, key_modified3, str3, 's');
    
    MY_STRING str4 = my_string_init_c_str("Words");
    MY_STRING key_orig4 = my_string_init_c_str("W---s");
    MY_STRING key_modified4 = my_string_init_default();
    get_word_key_value(key_orig4, key_modified4, str4, 'r');
    
    printf("Old key: %7s   Word: %7s   Guess: %c   New key: %7s\n", my_string_c_str(key_orig), my_string_c_str(str1), 'T', my_string_c_str(key_modified));
    printf("Old key: %7s   Word: %7s   Guess: %c   New key: %7s\n", my_string_c_str(key_orig2), my_string_c_str(str2), 'r', my_string_c_str(key_modified2));
    printf("Old key: %7s   Word: %7s   Guess: %c   New key: %7s\n", my_string_c_str(key_orig3), my_string_c_str(str3), 's', my_string_c_str(key_modified3));
    printf("Old key: %7s   Word: %7s   Guess: %c   New key: %7s\n", my_string_c_str(key_orig4), my_string_c_str(str4), 'r', my_string_c_str(key_modified4));
 
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    my_string_destroy(&str3);
    my_string_destroy(&str4);
    my_string_destroy(&key_orig);
    my_string_destroy(&key_orig2);
    my_string_destroy(&key_orig3);
    my_string_destroy(&key_orig4);
    my_string_destroy(&key_modified);
    my_string_destroy(&key_modified2);
    my_string_destroy(&key_modified3);
    my_string_destroy(&key_modified4);
 
    return 0;
}
*/
