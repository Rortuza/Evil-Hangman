#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"my_string.h"



void my_string_destroy(MY_STRING* phMy_string);
Status my_string_push_back(MY_STRING hMy_string, char letter);
Status my_string_pop_back(MY_STRING hMy_string);
int my_string_get_size(MY_STRING hMy_string);
int my_string_get_capacity(MY_STRING hMy_string);
char* my_string_at(MY_STRING hMy_string, int index);
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
char* my_string_c_str(MY_STRING hMy_string);
int my_string_compare(MY_STRING hMy_string1, MY_STRING hMy_string2);
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);
void my_string_assignment(ITEM* pLeft, ITEM right);
void Item_destroy(ITEM* phMy_string);

typedef struct my_string
{
    void(*destroy) (MY_STRING* phMy_string);
    Status(*push_back)(MY_STRING hMy_string, char item);
    Status(*pop_back) (MY_STRING hMy_string);
    int(*get_size) (MY_STRING hMy_string);
    int(*get_capacity) (MY_STRING hMy_string);
    char* (*at)(MY_STRING hMy_string, int index);
    Status(*extraction)(MY_STRING hMy_string, FILE* fp);
    char* (*c_str)(MY_STRING hMy_string);
    int(*string_compare)(MY_STRING hLeft_string, MY_STRING hRight_string);
    Status(*concat)(MY_STRING hResult, MY_STRING hAppend);
    Status(*insertion)(MY_STRING hMy_string, FILE* fp);
    void(*assignment)(ITEM* pLeft, ITEM right);
    void(*Item_destroy)(ITEM* phMy_string);

    int size;
    int capacity;
    char* data;
}String;


void init_functions(String* pString)
{
    pString->destroy = my_string_destroy;
    pString->push_back = my_string_push_back;
    pString->pop_back = my_string_pop_back;
    pString->get_size = my_string_get_size;
    pString->get_capacity = my_string_get_capacity;
    pString->at = my_string_at;
    pString->extraction = my_string_extraction;
    pString->c_str = my_string_c_str;
    pString->string_compare = my_string_compare;
    pString->concat = my_string_concat;
    pString->insertion = my_string_insertion;
    pString->assignment = my_string_assignment;
    pString->Item_destroy = Item_destroy;
}


MY_STRING my_string_init_default(void){
  String* pString;
  pString = (String*)malloc(sizeof(String));
        if(pString != NULL){
            init_functions(pString);
            pString->size = 0;
            pString->capacity = 7;
            pString->data = (char*)malloc(sizeof(char) * pString->capacity);
            if(pString->data == NULL){
              free(pString);
              return NULL;
            }
        }

        return (MY_STRING)pString;
}

void my_string_assignment(ITEM* pLeft, ITEM right){
  String* pRight = (String*)right;

  if(*pLeft == NULL){
   *pLeft = (String*)my_string_init_default();
  }

  for(int i = 0; i < pRight -> size; i++){
    my_string_push_back(*pLeft, pRight -> data[i]);
  }

}


void Item_destroy(ITEM* phMy_string)
{
    String* pMy_string = (String*)*phMy_string;
    if (pMy_string != NULL){
        pMy_string->destroy(&pMy_string);
        free(pMy_string);
        *phMy_string = NULL;
    }
}


MY_STRING my_string_init_c_str(const char* c_string){

    int i = 0;
    int size = 0;
    String* pMy_string = (String*)malloc(sizeof(String));


    while (c_string[i] != '\0')
    {
        i++;
        size++;
    }
    
    if (pMy_string == NULL)
    {
        free(pMy_string);
        return NULL;
    }

    if (pMy_string != NULL)
    {
        init_functions(pMy_string);
        pMy_string->size = 0;
        pMy_string->capacity = size + 5;
        pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
        if (pMy_string->data == NULL)
        {
            free(pMy_string);
            pMy_string = NULL;
        }
    }

    i = 0;
    while (c_string[i] != '\0')
    {
        pMy_string->push_back((MY_STRING)pMy_string, c_string[i]);
        i++;
    }
    return (MY_STRING)pMy_string;


}

void my_string_destroy(MY_STRING* phMy_string){
    String* pMy_string = (String*)*phMy_string;

    if (pMy_string != NULL)
    {
        free(pMy_string->data);
        free(pMy_string);
        *phMy_string = NULL;
    }
}


Status my_string_push_back(MY_STRING hMy_string, char item){
    //char* temp;
    int i;
    String* pMy_string = (String*)hMy_string;
    if (pMy_string -> size >= pMy_string -> capacity){
        pMy_string->capacity *= 2;
        char* temp = (char*)malloc(sizeof(char) * pMy_string -> capacity);
        if (temp == NULL){
            pMy_string -> capacity /= 2;
            return FAILURE;
        }
        
        for (i = 0; i < pMy_string->size; i++){
            temp[i] = pMy_string -> data[i];
        }
        
        free(pMy_string -> data);
        pMy_string -> data = temp;
    }
    pMy_string -> data[pMy_string -> size] = item;
    pMy_string -> size++;
    return SUCCESS;
}



Status my_string_pop_back(MY_STRING hMy_string){
    String* string = (String*)hMy_string;
    if (string->size != 0){
        string->size--;
        return SUCCESS;
    }
    
    else{
        return FAILURE;
    }
}

int my_string_get_size(MY_STRING hMy_string){
    String* pMy_string = (String*)hMy_string;
    return pMy_string->size;
}

int my_string_get_capacity(MY_STRING hMy_string){
    String* pMy_string = (String*)hMy_string;
    return pMy_string->capacity;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
    String* pMy_string = (String*)hMy_string;
    if (index <= -1 || index >= pMy_string -> size)
    {
        return NULL;
    }
    return &(pMy_string -> data[index]);
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fin){
    String* pMy_string = (String*)hMy_string;
    char c;
    
    if(fin != NULL){
        pMy_string -> size = 0;

        fscanf(fin, " ");
        c = getc(fin);
        while (!(isalpha(c)) && c != EOF){
            c = getc(fin);
        }
        
        if (isalpha(c)){
            pMy_string->push_back((MY_STRING)pMy_string, c);
        }
        
        while (!(isspace(c)) && c != EOF){
            c = getc(fin);
            if (isspace(c)){
                ungetc(c, fin);
                break;
            }
            
            else{
                if (c == EOF){
                    break;
                }
                pMy_string->push_back((MY_STRING)pMy_string, c);
            }
        }
        
        if (pMy_string->get_size((MY_STRING)pMy_string) == 0){
            return FAILURE;
        }
        
        return SUCCESS;
    }
    return FAILURE;
}

char* my_string_c_str(MY_STRING hMy_string){
    String* c_string = (String*)hMy_string;
    int i = 0;
    if (c_string->size >= c_string->capacity){
        char* temp = (char*)malloc(sizeof(char) * c_string->capacity + 5);
        
        if (temp == NULL)
        {
            c_string->capacity -= 5;
            return NULL;
        }
        
        i = 0;
        while(i < c_string->size){
            temp[i] = c_string->data[i];
            i++;
        }
        free(c_string -> data);
        c_string -> data = temp;
    }
    
    c_string -> data[c_string -> size] = '\0';
    return c_string->at((MY_STRING)c_string, 0);
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string){
    String* str1 = (String*)hLeft_string;
    String* str2 = (String*)hRight_string;

    int lenL;
    int lenR;
    int i = 0;

    lenL = str1->get_size((MY_STRING)str1);
    lenR = str2->get_size((MY_STRING)str2);

    while (i < lenL && i < lenR){
        if ((int)*str1->at((MY_STRING)str1, i) < (int)*str2->at((MY_STRING)str2, i)){
            return -1;
        }
        
        if ((int)*str1->at((MY_STRING)str1, i) > (int)*str2->at((MY_STRING)str2, i)){
            return 1;
        }
        
        i++;
    }

    if(lenL < lenR){
        return -1;
    }
    
    if(lenL>lenR){
        return 1;
    }
    
    else{
        return 0;
    }
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
    String* result = (String*)hResult;
    String* append = (String*)hAppend;

    int lenR;
    int i;
    if (append -> size == 0){
        return FAILURE;
    }
    if ((lenR = result->get_size((MY_STRING)append)) == 0){
        return FAILURE;
    }

    for (i = 0; i < lenR; i++){
        result->push_back((MY_STRING)result, *append->at((MY_STRING)append, i));
    }
    return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp){
    String* pMy_string = (String*)hMy_string;
    char c;
    
    if (fp != NULL){
        pMy_string -> size = 0;
        c = getc(fp);
        while (c != '\n'){
            if (feof(fp)){
                break;
            }
            pMy_string->push_back((MY_STRING)pMy_string, c);
            c = getc(fp);
        }
        return SUCCESS;
    }
    return FAILURE;
}

int order_str(MY_STRING hLeft, MY_STRING hRight){ //sorts string in alphabetical order (case insensitive)
    String* left = (String*)hLeft; //string cast to know type
    String* right = (String*)hRight;



    for(int i = 0; i < left->size && i < right->size; i++){ //checks each index of strings
        char l = left->data[i];
        char r = right->data[i];

        if(l < r){ //returns -1 if l is less than r
            return -1;
        }

        if(l > r){ // returns 1 if r is less than l
            return 1;
        }
    }

    return left->size - right->size; //returns positive or negative number
}

int order_str_ignore_case(MY_STRING hLeft, MY_STRING hRight){ //sorts string in alphabetical order (case sensitive)

    String* left = (String*)hLeft; // string cast to know type
    String* right = (String*)hRight;


    for(int i = 0; i < left->size && i < right->size; i++){ // checks each index of strings
        char l = left->data[i];
        char r = right->data[i];


        if((l >= 'a' && l <= 'z') || (l >= 'a' && l <= 'z')){ // if one word is lowercase
            l = tolower(l); //make both lowercase
            r = tolower(r);
        }

        else if((l >= 'A' && l <= 'Z') || (l >= 'A' && l <= 'Z')){ // if one word is capital
            l = toupper(l); // make others capital
            r = toupper(r);
        }

        if(l < r){ // if l comes first
            return -1;
    }

        if(l > r){ // if l comes after
            return 1;
        }
    }

    return left->size - right->size; // returns positive or negative number
}


Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
        MY_STRING temp = NULL;
        int i;
        char word_char;
        char family_char;
     
        temp = my_string_init_default();
        if (temp == NULL)
            return FAILURE;
     
        guess = tolower(guess);
     
        for (i = 0; i < my_string_get_size(word); i++)
        {
            word_char = tolower(*(my_string_at(word, i)));
            family_char = tolower(*(my_string_at(current_word_family, i)));
     
            if (guess == word_char){
                if (my_string_push_back(temp, word_char) == FAILURE){
                    return FAILURE;
                }
            }
            
            else{
                if (my_string_push_back(temp, family_char) == FAILURE){
                    return FAILURE;
                }
            }
        }
        my_string_assignment(&new_key, temp);
        my_string_destroy(&temp);
     
    return SUCCESS;
    }
     
