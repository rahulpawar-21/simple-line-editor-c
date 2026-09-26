#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 10
#define MAX_LINE_LENGTH 500
#define MAX_FILENAME_LENGTH 100

typedef struct {
    char **lines;
    int count;
    int capacity;
} Document;

/* ---------- Utility functions ---------- */

void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard remaining input */
    }
}

void trim_newline(char *text) {
    text[strcspn(text, "\n")] = '\0';
}

void initialize_document(Document *doc) {
    doc->lines = malloc(INITIAL_CAPACITY * sizeof(char *));
    if (doc->lines == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    doc->count = 0;
    doc->capacity = INITIAL_CAPACITY;
}

void free_document(Document *doc) {
    int i;

    for (i = 0; i < doc->count; i++) {
        free(doc->lines[i]);
    }

    free(doc->lines);
    doc->lines = NULL;
    doc->count = 0;
    doc->capacity = 0;
}

int ensure_capacity(Document *doc) {
    char **temp;
    int new_capacity;

    if (doc->count < doc->capacity) {
        return 1;
    }

    new_capacity = doc->capacity * 2;
    temp = realloc(doc->lines, new_capacity * sizeof(char *));

    if (temp == NULL) {
        return 0;
    }

    doc->lines = temp;
    doc->capacity = new_capacity;
    return 1;
}

char *duplicate_string(const char *text) {
    char *copy = malloc(strlen(text) + 1);

    if (copy != NULL) {
        strcpy(copy, text);
    }

    return copy;
}

/* ---------- Core features ---------- */

/*
   Insert a new line at a 1-based position.
   Valid positions are 1 through count + 1.
*/
int insert_line(Document *doc, int line_number, const char *text) {
    int i;
    char *new_line;

    if (line_number < 1 || line_number > doc->count + 1) {
        return 0;
    }

    if (!ensure_capacity(doc)) {
        return 0;
    }

    new_line = duplicate_string(text);
    if (new_line == NULL) {
        return 0;
    }

    /* Shift existing lines down. */
    for (i = doc->count; i >= line_number; i--) {
        doc->lines[i] = doc->lines[i - 1];
    }

    doc->lines[line_number - 1] = new_line;
    doc->count++;

    return 1;
}

/*
   Delete a line at a 1-based position.
*/
int delete_line(Document *doc, int line_number) {
    int i;

    if (line_number < 1 || line_number > doc->count) {
        return 0;
    }

    free(doc->lines[line_number - 1]);

    /* Shift following lines up. */
    for (i = line_number - 1; i < doc->count - 1; i++) {
        doc->lines[i] = doc->lines[i + 1];
    }

    doc->count--;
    return 1;
}

/*
   Display all lines with their line numbers.
*/
void display_document(const Document *doc) {
    int i;

    if (doc->count == 0) {
        printf("Document is empty.\n");
        return;
    }

    printf("\n----- Document -----\n");

    for (i = 0; i < doc->count; i++) {
        printf("%d: %s\n", i + 1, doc->lines[i]);
    }

    printf("--------------------\n");
}

/* ---------- Bonus: Save / Load ---------- */

int save_document(const Document *doc, const char *filename) {
    FILE *file;
    int i;

    file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }

    for (i = 0; i < doc->count; i++) {
        fprintf(file, "%s\n", doc->lines[i]);
    }

    fclose(file);
    return 1;
}

int load_document(Document *doc, const char *filename) {
    FILE *file;
    char buffer[MAX_LINE_LENGTH];
    Document temp;

    file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    initialize_document(&temp);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        trim_newline(buffer);

        if (!insert_line(&temp, temp.count + 1, buffer)) {
            free_document(&temp);
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    free_document(doc);
    *doc = temp;

    return 1;
}

/* ---------- Bonus: Search ---------- */

void search_document(const Document *doc, const char *query) {
    int i;
    int found = 0;

    if (query[0] == '\0') {
        printf("Search text cannot be empty.\n");
        return;
    }

    for (i = 0; i < doc->count; i++) {
        if (strstr(doc->lines[i], query) != NULL) {
            printf("Found on line %d: %s\n", i + 1, doc->lines[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Text not found.\n");
    }
}

/* ---------- Bonus: Statistics ---------- */

int count_words_in_line(const char *line) {
    int words = 0;
    int in_word = 0;
    const unsigned char *p = (const unsigned char *)line;

    while (*p != '\0') {
        if (isspace(*p)) {
            in_word = 0;
        } else if (!in_word) {
            words++;
            in_word = 1;
        }
        p++;
    }

    return words;
}

void show_statistics(const Document *doc) {
    int i;
    int total_words = 0;

    for (i = 0; i < doc->count; i++) {
        total_words += count_words_in_line(doc->lines[i]);
    }

    printf("Line count: %d\n", doc->count);
    printf("Word count: %d\n", total_words);
}

/* ---------- Help ---------- */

void show_help(void) {
    printf("\n========== LINE EDITOR HELP ==========\n");
    printf("insert <line>       Insert a new line at the given number.\n");
    printf("delete <line>       Delete the line at the given number.\n");
    printf("display             Display all lines with line numbers.\n");
    printf("save <filename>     Save the document to a text file.\n");
    printf("load <filename>     Load a text file into the document.\n");
    printf("search <text>       Find lines containing the given text.\n");
    printf("count               Show line and word counts.\n");
    printf("help                Show this help message.\n");
    printf("quit                Exit the editor.\n");
    printf("======================================\n");
}

/* ---------- Command handling ---------- */

void command_loop(Document *doc) {
    char command[600];

    while (1) {
        printf("\nline-editor> ");

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\nExiting.\n");
            break;
        }

        trim_newline(command);

        if (strcmp(command, "display") == 0) {
            display_document(doc);
        }
        else if (strcmp(command, "help") == 0) {
            show_help();
        }
        else if (strcmp(command, "count") == 0) {
            show_statistics(doc);
        }
        else if (strcmp(command, "quit") == 0 ||
                 strcmp(command, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        else if (strncmp(command, "insert ", 7) == 0) {
            int line_number;
            char *text;

            if (sscanf(command + 7, "%d", &line_number) != 1) {
                printf("Usage: insert <line>\n");
                continue;
            }

            if (line_number < 1 || line_number > doc->count + 1) {
                printf("Invalid line number. Use 1 to %d.\n",
                       doc->count + 1);
                continue;
            }

            printf("Enter text: ");

            text = malloc(MAX_LINE_LENGTH);
            if (text == NULL) {
                printf("Memory allocation failed.\n");
                continue;
            }

            if (fgets(text, MAX_LINE_LENGTH, stdin) == NULL) {
                free(text);
                printf("Could not read the line.\n");
                continue;
            }

            trim_newline(text);

            if (insert_line(doc, line_number, text)) {
                printf("Line inserted successfully.\n");
            } else {
                printf("Could not insert the line.\n");
            }

            free(text);
        }
        else if (strncmp(command, "delete ", 7) == 0) {
            int line_number;

            if (sscanf(command + 7, "%d", &line_number) != 1) {
                printf("Usage: delete <line>\n");
                continue;
            }

            if (delete_line(doc, line_number)) {
                printf("Line deleted successfully.\n");
            } else {
                printf("Invalid line number. Document has %d line(s).\n",
                       doc->count);
            }
        }
        else if (strncmp(command, "save ", 5) == 0) {
            char filename[MAX_FILENAME_LENGTH];

            if (sscanf(command + 5, "%99s", filename) != 1) {
                printf("Usage: save <filename>\n");
                continue;
            }

            if (save_document(doc, filename)) {
                printf("Document saved to '%s'.\n", filename);
            } else {
                printf("Error: could not save '%s'.\n", filename);
            }
        }
        else if (strncmp(command, "load ", 5) == 0) {
            char filename[MAX_FILENAME_LENGTH];

            if (sscanf(command + 5, "%99s", filename) != 1) {
                printf("Usage: load <filename>\n");
                continue;
            }

            if (load_document(doc, filename)) {
                printf("Document loaded from '%s'.\n", filename);
            } else {
                printf("Error: could not load '%s'.\n", filename);
            }
        }
        else if (strncmp(command, "search ", 7) == 0) {
            const char *query = command + 7;
            search_document(doc, query);
        }
        else if (command[0] == '\0') {
            printf("Please enter a command. Type 'help' for commands.\n");
        }
        else {
            printf("Unknown command. Type 'help' to see available commands.\n");
        }
    }
}

int main(void) {
    Document document;

    initialize_document(&document);

    printf("=================================\n");
    printf("       SIMPLE LINE EDITOR        \n");
    printf("=================================\n");
    printf("Type 'help' to see available commands.\n");

    command_loop(&document);
    free_document(&document);

    return 0;
}
