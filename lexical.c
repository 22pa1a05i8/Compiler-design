#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_CONTENT_LENGTH 10240  

const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do","double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
"long", "register", "return", "short", "signed", "sizeof", "static", "struct","switch", "typedef", "union", "unsigned", "void", "volatile", "while","printf", "scanf", "%d", "include", "stdio.h", "main"};

const char *operators[] = { "+", "-", "*", "/", "<", ">", "=", "<=", ">=", "==", "++", "!=", "--", "%" };

const char delimiters[] = { '(', ')', '{', '}', '[', ']', '\'', '\"', ';', '#', ':', ',' };

int is_keyword(const char *word);
int is_operator(const char *word);
int is_delimiter(char c);
int is_number(const char *word);
void detect_tokens(char *text);

int is_keyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *word) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); ++i) {
        if (strcmp(word, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_delimiter(char c) {
    for (int i = 0; i < sizeof(delimiters); ++i) {
        if (c == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

int is_number(const char *word) {
    for (int i = 0; i < strlen(word); ++i) {
        if (!isdigit(word[i])) {
            return 0;
        }
    }
    return 1;
}

void detect_tokens(char *text) {
    char *current = text;
    char token[MAX_LINE_LENGTH];
    int i = 0;

    printf("Keywords: ");
    while (*current) {
        if (isalpha(*current) || *current == '_') {
            token[i++] = *current;
            current++;
            while (isalnum(*current) || *current == '_') {
                token[i++] = *current;
                current++;
            }
            token[i] = '\0';
            i = 0;
            if (is_keyword(token)) {
                printf("%s ", token);
            }
        } else if (isspace(*current)) {
            current++;
        } else {
            current++;
        }
    }
    printf("\n");

    current = text;
    printf("Operators: ");
    while (*current) {
        int j;
        for (j = 0; j < sizeof(operators) / sizeof(operators[0]); ++j) {
            int len = strlen(operators[j]);
            if (strncmp(current, operators[j], len) == 0) {
                printf("%s ", operators[j]);
                current += len;
                break;
            }
        }
        if (j == sizeof(operators) / sizeof(operators[0])) {
            current++;
        }
    }
    printf("\n");

    current = text;
    printf("Delimiters: ");
    while (*current) {
        if (is_delimiter(*current)) {
            printf("%c ", *current);
        }
        current++;
    }
    printf("\n");

    current = text;
    printf("Numbers: ");
    while (*current) {
        if (isdigit(*current)) {
            i = 0;
            while (isdigit(*current)) {
                token[i++] = *current;
                current++;
            }
            token[i] = '\0';
            printf("%s ", token);
        } else {
            current++;
        }
    }
    printf("\n");

    current = text;
    printf("Identifiers: ");
    while (*current) {
        if (isalpha(*current) || *current == '_') {
            i = 0;
            while (isalnum(*current) || *current == '_') {
                token[i++] = *current;
                current++;
            }
            token[i] = '\0';
            if (!is_keyword(token) && !is_operator(token) && !is_number(token)) {
                printf("%s ", token);
            }
        } else {
            current++;
        }
    }
    printf("\n");
}

int main() {
    FILE *file = fopen("e1-example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char text[MAX_CONTENT_LENGTH] = "";

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        strncat(text, buffer, MAX_CONTENT_LENGTH - strlen(text) - 1);
    }

    fclose(file);

    detect_tokens(text);

    return EXIT_SUCCESS;
}

