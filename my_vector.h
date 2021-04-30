#ifndef STATUS_H
#define STATUS_H
enum status { FAILURE, SUCCESS };
typedef enum status Status;
#endif
#ifndef VECTOR_H
#define VECTOR_H
struct generic_vector_public;
typedef struct generic_vector_public* GENERIC_VECTOR;
typedef void* ITEM;

struct generic_vector_public
{
    void(*destroy)(GENERIC_VECTOR* phMy_vector);
    Status(*push_back)(GENERIC_VECTOR hMy_vector, ITEM item);
    Status(*pop_back)(GENERIC_VECTOR hMy_vector);
    ITEM(*at)(GENERIC_VECTOR hMy_vector, int index); //checks array bounds
    int(*get_size)(GENERIC_VECTOR hMy_vector); //Accessor function
    int(*get_capacity)(GENERIC_VECTOR hMy_vector); //Accessor function
};


GENERIC_VECTOR generic_vector_init_default(void(*item_destroy)(ITEM* item_handle),
    void(*item_assign)(ITEM* item_handle, ITEM item));

void generic_vector_destroy(GENERIC_VECTOR* phMy_vector);
Status generic_vector_push_back(GENERIC_VECTOR hMy_vector, ITEM item);
Status generic_vector_pop_back(GENERIC_VECTOR hMy_vector);
ITEM generic_vector_at(GENERIC_VECTOR hMy_vector, int index);
int generic_vector_get_size(GENERIC_VECTOR hMy_vector); //Accessor function
int generic_vector_get_capacity(GENERIC_VECTOR hMy_vector); //Accessor function

#endif

