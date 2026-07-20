#include <stdio.h>
#include <stdlib.h> /* Required for bsearch */
#include <string.h>

typedef struct Nameval Nameval;
struct Nameval {
        char *name;
        int value;
};

/* HTML characters strictly sorted by ASCII value for binary search */
Nameval htmlchars[] = {
        {"AElig",  0x00c6},
        {"Aacute", 0x00c1},
        {"Acirc",  0x00c2}, 
        {"zeta",   0x03b6}  
};

/* 
 * Comparator function for bsearch.
 * 'key' is a pointer to the string we are searching for.
 * 'elem' is a pointer to the current Nameval struct in the array.
 */
int cmp_nameval(const void *key, const void *elem) {
    const char *search_name = (const char *)key;
    const Nameval *array_item = (const Nameval *)elem;
    
    return strcmp(search_name, array_item->name);
}

int main() {
    size_t ntab = sizeof(htmlchars) / sizeof(htmlchars[0]);
    
    /* Dummy data to test the search */
    char *test_queries[] = {
        "AElig",   
        "Acirc",   
        "zeta",    
        "Abeta",   /* Missing element */
        "apple"    /* Missing element */
    };
    
    int num_queries = sizeof(test_queries) / sizeof(test_queries[0]);

    printf("Testing <stdlib.h> bsearch()...\n");
    printf("-------------------------------\n");

    for (int i = 0; i < num_queries; i++) {
        char *query = test_queries[i];
        
        /* 
         * bsearch returns a pointer to the matching element, 
         * or NULL if it wasn't found.
         */
        Nameval *result = bsearch(
            query,              /* The key to search for */
            htmlchars,          /* The array to search in */
            ntab,               /* Number of elements in the array */
            sizeof(Nameval),    /* Size of each element */
            cmp_nameval         /* The comparator function */
        );
        
        if (result != NULL) {
            printf("[PASS] Found '%-6s' (Hex value: 0x%04X)\n", 
                   query, result->value);
        } else {
            printf("[PASS] Word  '%-6s' not found (returned NULL)\n", query);
        }
    }
    
    return 0;
}
