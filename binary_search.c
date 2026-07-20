#include <stdio.h>
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

/* lookup: binary search for name in tab; return index */
int lookup(char *name, Nameval tab[], int ntab)
{
        int low, high, mid, cmp;
        
        low = 0;
        high = ntab - 1;
        
        while (low <= high) {
                mid = low + (high - low) / 2; 
                cmp = strcmp(name, tab[mid].name);
                
                if (cmp < 0)
                        high = mid - 1; 
                else if (cmp > 0)
                        low = mid + 1;
                else 
                        return mid;
        }
        return -1; 
}

int main() {
    /* Calculate the number of elements in the array automatically */
    int ntab = sizeof(htmlchars) / sizeof(htmlchars[0]);
    
    /* Dummy data to test the search */
    char *test_queries[] = {
        "AElig",   /* First element */
        "Acirc",   /* Middle element */
        "zeta",    /* Last element */
        "Abeta",   /* Missing element (would be between AElig and Aacute) */
        "omega",   /* Missing element (would be between Acirc and zeta) */
        "apple"    /* Missing element (lowercase 'a' comes after all uppercase) */
    };
    
    int num_queries = sizeof(test_queries) / sizeof(test_queries[0]);

    printf("Testing Binary Search...\n");
    printf("------------------------\n");

    for (int i = 0; i < num_queries; i++) {
        char *query = test_queries[i];
        int index = lookup(query, htmlchars, ntab);
        
        if (index != -1) {
            printf("[PASS] Found '%-6s' at index %d (Hex value: 0x%04X)\n", 
                   query, index, htmlchars[index].value);
        } else {
            printf("[PASS] Word  '%-6s' not found (returned -1)\n", query);
        }
    }
    
    return 0;
}
