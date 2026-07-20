#include <stdio.h>
#include <string.h>

char *flab[] = {
        "actually",
        "just",
        "quite",
        "really",
        NULL
};

/* lookup: sequential search for word in array */
int lookup(char *word, char *array[]) 
{
        int i;
        for (i = 0; array[i] != NULL; i++)
                if(strcmp(word, array[i]) == 0)
                        return i;
        return -1;
}

int main() {
    char *target = "quite";
    int index = lookup(target, flab);
    
    if (index != -1) {
        printf("Found '%s' at index: %d\n", target, index);
    } else {
        printf("Word '%s' not found.\n", target);
    }
    
    return 0;
}
