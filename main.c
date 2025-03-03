#include "stack.h"

void stream(char **c) {
    printf("\n");
    for (int i = 0; c[i] != NULL; i++) {
        printf("%s >>> ", c[i]);
    }
    printf("\n");
}

int main(void) {
    char s[STRLIM];
    printf("Enter string: ");
    fgets(s, STRLIM, stdin);
    char **res = split(s, ' ');
    char **res3 = split(s, ',');
    stream(res);
    stream(res3);
    free(res);
    free(res3);
    return 0;
}
