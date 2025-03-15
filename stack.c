#include "stack.h"


int mlen(char *c) { //does account for \0
    if (c == NULL) {
        return -1;
    }
    int x = 0;
    for (int i = 0; c[i] != '\0'; i++) {
        x++;
    }
    return x + 1;
}

void copy(char *c, char *s) { //c is dest, s is source
    if (c == NULL || s == NULL) {
        return;
    }
    while (*c++ = *s++);
    //now reallocate memory for c;
    //c = realloc(c, len * sizeof(char)); //len + 1 is not required since while loop already sets \0
    //free(s) is not required, this function is not responsible for garbage collecting
}

stack *new(void) {
    stack *s = malloc(sizeof(stack));
    s->len = 0;
    s->capac = DEFAULT;
    s->args = malloc(s->capac * sizeof(char *));
    for (int i = 0; i < s->capac; i++) {
        s->args[i] = NULL;
    }
    return s;
}

void del(stack *s) {
    for (int i = 0; i < s->len; i++) {
        free(s->args[i]);
    }
    free(s->args);
    free(s);
}

void push(stack *s, char *c) {
    if (s->len == s->capac) {
        s->capac *= 2;
        s->args = realloc(s->args, sizeof(char *) * s->capac);
    }
    s->args[s->len] = malloc(sizeof(char) * mlen(c));
    copy(s->args[s->len], c);
    s->len++;
}

char *pop(stack *s) {
    if (s->len == 0) {
        return NULL;
    }
    char *c = malloc(mlen(s->args[s->len - 1]) * sizeof(char));
    copy(c,s->args[s->len - 1]);
    free(s->args[s->len - 1]);
    s->len--;
    return c;
}

void pstack(stack *s) {
    printf("\n");
    for (int i = 0; i < s->len; i++) {
        printf("%s ", s->args[i]);    
    }
    printf("\n");
}
    
void insert(stack *s, int index, char *c) {
    stack *clone = new();
    for (int i = 0; i < index; i++) {
        push(clone, s->args[i]);
        free(s->args[i]);
    }
    push(clone, c);
    for (int i = index; i < s->len; i++) {
        push(clone, s->args[i]);
        free(s->args[i]);
    }
    s->args = realloc(s->args, (s->len + 1) * sizeof(char *));
    for (int i = 0; i < clone->len; i++) {
        s->args[i] = malloc(sizeof(char) * mlen(clone->args[i])); 
        copy(s->args[i], clone->args[i]);
    }
    del(clone);
    s->len++;
}

char *mremove(stack *s, int index) {
    char *c = malloc(mlen(s->args[index]) * sizeof(char));
    copy(c, s->args[index]);
    stack *clone = new();
    for (int i = 0; i < s->len; i++) {
        if (i == index) {
            continue;
        } else {
            push(clone, s->args[i]);
        }
        free(s->args[i]);
    }
    s->args = realloc(s->args, (s->len - 1) * sizeof(char *));
    for (int i = 0; i < clone->len; i++) {
        s->args[i] = malloc(sizeof(char) * mlen(clone->args[i]));
        copy(s->args[i], clone->args[i]);
    }
    del(clone);
    s->len--;
    return c;
}

void set(stack *s, int index, char *c) {
    s->args[index] = realloc(s->args[index], sizeof(char) * mlen(c));
    copy(s->args[index], c);
}

char **split(char *s, char c) { //s is string, c is delimiter
    stack *st = new();
    int i = 0;
    char buffer[STRLIM];
    int j = 0; //current string length;
    while (s[i] != '\0') {
        if (s[i] == c) { //delimiter encountered
            buffer[j] = '\0';
            if (j > 0) {
                push(st, buffer);
            }
            //push(st, buffer);
            j = 0;
            //flush buffer completely
            for (int x = 0; x < STRLIM; x++) {
                buffer[x] = '\0';
            }
        } else {
            buffer[j] = s[i];
            j++;
        }
        i++;
    }
    if (buffer[0] != '\0') { //means that we have at least 1 copy left
        push(st, buffer);
    }
    char **ans = malloc(sizeof(char *) * (st->len + 1));
    for (int i = 0; i < st->len; i++) {
        ans[i] = malloc(sizeof(char) * mlen(st->args[i]));
        copy(ans[i], st->args[i]);
    }
    ans[st->len] = NULL;
    del(st);
    return ans;
}
