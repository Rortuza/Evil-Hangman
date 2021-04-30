#include <stdlib.h>
#include "my_vector.h"

void generic_vector_destroy(GENERIC_VECTOR* phMy_vector);
Status generic_vector_push_back(GENERIC_VECTOR hMy_vector, ITEM item);
Status generic_vector_pop_back(GENERIC_VECTOR hMy_vector);
ITEM generic_vector_at(GENERIC_VECTOR hMy_vector, int index);
int generic_vector_get_size(GENERIC_VECTOR hMy_vector);
int generic_vector_get_capacity(GENERIC_VECTOR hMy_vector);

typedef struct generic_vector{
    //public (function pointers)
    void(*destroy)(GENERIC_VECTOR* phMy_vector);
    Status(*push_back)(GENERIC_VECTOR hMy_vector, ITEM item);
    Status(*pop_back)(GENERIC_VECTOR hMy_vector);
    ITEM(*at)(GENERIC_VECTOR hMy_vector, int index);
    int(*get_size)(GENERIC_VECTOR hMy_vector);
    int(*get_capacity)(GENERIC_VECTOR hMy_vector);

    //private
    int size;
    int capacity;
    ITEM* data;
    
    //function pointers
    void(*item_destroy)(ITEM* item_handle);
    void(*item_assign)(ITEM* item_handle, ITEM item);
 
}GenericVector;


GENERIC_VECTOR generic_vector_init_default(void(*item_destroy)(ITEM* item_handle),
    void(*item_assign)(ITEM* item_handle, ITEM item)){
    GenericVector* pVector = (GenericVector*)malloc(sizeof(GenericVector));
    int i;
    if (pVector != NULL)
    {
        pVector->size = 0;
        pVector->capacity = 1;
        pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
        pVector->destroy = generic_vector_destroy;
        pVector->push_back = generic_vector_push_back;
        pVector->get_size = generic_vector_get_size;
        pVector->get_capacity = generic_vector_get_capacity;
        pVector->pop_back = generic_vector_pop_back;
        pVector->at = generic_vector_at;
        pVector->item_destroy = item_destroy;
        pVector->item_assign = item_assign;
        if (pVector->data == NULL) {
            free(pVector);
            return NULL;
        }
        for(i = 0; i < pVector->capacity; i++){
            pVector->data[i] = NULL;
        }
    }
    
    return (GENERIC_VECTOR)pVector;
        
}

void generic_vector_destroy(GENERIC_VECTOR* phVector){
    GenericVector* pVector = (GenericVector*)*phVector;
    int i;

    for (i = 0; i < pVector->size; i++) {
        pVector->item_destroy(&(pVector->data[i]));
    }
    
    free(pVector->data);
    free(pVector);
    *phVector = NULL;
}
Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM hItem){
    GenericVector* pVector = (GenericVector*)hVector;
    
       if (pVector->size >= pVector->capacity) {
           ITEM* temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);
           if (temp == NULL) {
               return FAILURE;
           }
           int i;
           for (i = 0; i < pVector->size; i++) {
               temp[i] = pVector->data[i];
           }
           pVector->capacity *= 2;
           for (; i < pVector->capacity; i++) {
               temp[i] = NULL;
           }
           free(pVector->data);
           pVector->data = temp;
       }
       pVector->item_assign(&pVector->data[pVector->size], hItem);
       pVector->size++;

       return SUCCESS;
}

int generic_vector_get_size(GENERIC_VECTOR hVector){
    GenericVector* pVector = (GenericVector*)hVector;
    return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector){
    GenericVector* pVector = (GenericVector*)hVector;
    return pVector->capacity;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
    GenericVector* pVector = (GenericVector*)hVector;
    if (pVector <= 0) {
        return FAILURE;
    }
    pVector->size--;
    pVector->item_destroy(&pVector->data[pVector->size]);
    return SUCCESS;
}

ITEM generic_vector_at(GENERIC_VECTOR hVector, int index)
{
    GenericVector* pVector = (GenericVector*)hVector;
    if (index < 0 || index >= pVector->size) {
        return NULL;
    }
    return pVector->data[index];
}

