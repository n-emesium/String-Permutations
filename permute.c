#include <stdio.h>
#include "stack.h"


char *convert(stack *characters) {
    char *ret = malloc(sizeof(char) * (characters->len + 1));
    for (int i = 0; i < characters->len; i++) {
        ret[i] = *(characters->args[i]);
    }
    ret[characters->len] = '\0';
    return ret;
}


void remove_at(char *c, int x) {
    int len = mlen(c);
    for (int i = x; i < len - 1; i++) {
        c[i] = c[i + 1];
    }
    c[len - 1] = '\0';
}


//This version can lead to undefined behavior, do NOT use it. 

/*void populate(char *str, int len, stack *strings, stack *characters) {
    if (len == 0) {
        push(strings, convert(characters));
        return;
    }
    for (int i = 0; i < len; i++) {
        char *c = malloc(sizeof(char));        
        *c = str[i];
        push(characters, c);
        //push(characters, &str[i]);
        char *clone = malloc(sizeof(char) * (len));
        copy(clone, str);
        remove_at(clone, i);
        populate(clone, len - 1, strings, characters);
        free(clone);
        free(pop(characters));
    }
}*/


void populate(char *str, int len, stack *strings, stack *characters) {
    if (len == 0) {
        push(strings, convert(characters));
        return;
    }
    for (int i = 0; i < len; i++) {
        char *c = malloc(2 * sizeof(char)); //+1 for the null terminator
        c[0] = str[i];
        c[1] = '\0';
        push(characters, c);
        char *clone = malloc((len + 1) * sizeof(char));
        copy(clone, str);
        remove_at(clone, i);
        populate(clone, len - 1, strings, characters);
        free(clone);
        free(pop(characters));
    }
}


int main(int argc, char **args) {
    printf("\n");
    int glob = 0;
    for (int i = 1; i < argc; i++) {
        int loc = 0;
        char *cur = args[i];    
        int len = mlen(cur) - 1;
        stack *strings = new();
        stack *characters = new();
        populate(cur, len, strings, characters);
        del(characters);
        for (int i = 0; i < strings->len; i++) {
            printf("%s ", strings->args[i]);
            loc++;
        }
        del(strings);
        printf("\nTotal number of all permutations for the word '%s' is: %d\n", cur, loc);
        printf("\n");
        glob += loc;
    }
    printf("\n Total number of all permutations for every word is: %d\n", glob);
    return 0;
}
