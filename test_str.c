#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FManC_CStrView
{
    size_t size;
    char *str;
};

typedef struct FManC_CStrView FMC_CStrView;

FMC_CStrView* FMC_allocStrView(const char* const str, size_t len)
{
    FMC_CStrView* view = malloc(sizeof(FMC_CStrView));
    if (view == NULL)
    {
        return NULL;
    }
    view->size = len;
    view->str = malloc(sizeof(char) * (len + 1));
    if (view->str == NULL)
    {
        free(view);
        return NULL;
    }
    strncpy(view->str, str, len+1);
    return view;
}
void FMC_freeStrView(FMC_CStrView* view)
{
    free(view->str);
    free(view);
}

int main(int argc, char const *argv[])
{
    // make an array of strViews
    FMC_CStrView* views[3];
    views[0] = FMC_allocStrView("Hello", 5);
    views[1] = FMC_allocStrView("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    views[2] = FMC_allocStrView("!", 1);
    // print the array
    for (size_t i = 0; i < 3; i++)
    {
        printf("%s ", views[i]->str);
    }
    printf("\n");
    
    // print the size of all the views
    for (size_t i = 0; i < 3; i++)
    {
        printf("%zu ", sizeof(views[i]));
    }
    printf("\n");
    
    // free the array
    for (size_t i = 0; i < 3; i++)
    {
        FMC_freeStrView(views[i]);
    }
    
    return 0;
}