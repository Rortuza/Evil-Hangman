#ifndef MY_STRING_H
#define MY_STRING_H
#include "my_vector.h"

#ifndef STATUS_H
#define STATUS_H
enum status { FAILURE, SUCCESS };
typedef enum status Status;
#endif

struct my_string_public;
typedef struct my_string_public* MY_STRING;


MY_STRING my_string_init_default(void);
void my_string_destroy(MY_STRING* phMy_string);
Status my_string_push_back(MY_STRING hMy_string, char letter);
Status my_string_pop_back(MY_STRING hMy_string);
int my_string_get_size(MY_STRING hMy_string);
int my_string_get_capacity(MY_STRING hMy_string);
char* my_string_at(MY_STRING hMy_string, int index);
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
MY_STRING my_string_init_c_str(const char* c_string);
char* my_string_c_str(MY_STRING hMy_string);
int my_string_compare(MY_STRING hMy_string1, MY_STRING hMy_string2);
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);
void my_string_assignment(ITEM* pLeft, ITEM right);
void Item_destroy(ITEM* phMy_string);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);


struct my_string_public
{
    void(*destroy)(MY_STRING* phMy_string);
    Status(*push_back) (MY_STRING hMy_string, char item);
    Status(*pop_back)(MY_STRING hMy_string);
    int(*get_size)(MY_STRING hMy_string);
    int(*get_capacity)(MY_STRING hMy_string);
    char* (*at)(MY_STRING hMy_string, int index);
    Status(*extraction)(MY_STRING hMy_string, FILE* fp);
    char* (*c_str)(MY_STRING hMy_string);// (MAY RESIZE FOR NULL TERM)
    //string_compare
    //POST: returns -1 if string 1 < string 2
    //     returns 0 if strings are equivalent
    //       returns 1 if
    int(*string_compare)(MY_STRING hMy_string1, MY_STRING hMy_string2);
    //concatenation (put two strings together)
    Status(*concat)(MY_STRING hResult, MY_STRING hAppend);
    Status(*insertion)(MY_STRING hMy_string, FILE* fp);
    void(*assignment)(ITEM* pLeft, ITEM right);
    void(*Item_destroy) (ITEM* phMy_string);
    //copy a string?
    //assignment for complete and independent copies of these things
};




#endif
