#include "util.h"
#include "econio.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Instantiates a matrix with the specified number of rows and columns
 * 
 * @param rows Number of rows
 * @param cols Number of columns
 * @return bool** 
 */
bool **init_bool_matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0);

    bool **matrix = malloc(rows * sizeof(bool *));
    check_malloc(matrix);
    matrix[0] = malloc(rows * cols * sizeof(bool));
    check_malloc(matrix[0]);

    for (int i = 1; i < rows; i++)
        matrix[i] = matrix[0] + i * cols;

    return matrix;
}

/**
 * @brief Frees the specified matrix allocated by init_matrix
 * ATTENTION: Only use this on matrixes that have been allocated by init_matrix
 * 
 * @param matrix 
 */
void free_bool_matrix(bool **matrix) {
    free(matrix[0]);
    free(matrix);
}

/**
 * @brief The function splits the string by the separator into an array of pointers
 * ATTENTION: this function modifies str
 * 
 * @param str
 * @param parts
 * @param num_of_splits 
 * @param sep 
 */
void split(char *str, char *parts[], int num_of_splits, const char *sep) {
    assert(num_of_splits > 0);
    parts[0] = strtok(str, sep);
    for (int i = 1; i < num_of_splits; i++) {
        parts[i] = strtok(NULL, sep);
    }
}

/**
 * @brief if the ptr is null than prints an error message and exits
 * 
 * @param ptr 
 */
void check_malloc(void *ptr) {
    if (ptr == NULL) {
        print_error("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Removes all occurences of the specified char in str
 * 
 * @param str 
 * @param char_to_remove 
 */
void remove_chars(char *str, char char_to_remove) {
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == char_to_remove) {
            for (j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

/**
 * @brief Trims whitespace front and back of string
 * 
 * @param str 
 * @return char* Returns the trimmed substring
 */
char *trim(char *str) {
    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    char *end;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

/**
 * @brief Read in a string from the console
 * and does not read more than the specified length
 * 
 * @param str The string to read into
 * @param len The max number of chars to read it has to be between 0 and 256
 */
void read_str(char *str, int len) {
    assert(0 < len && len < 256);
    char format[6]; // contains the format like this "%255s"
    sprintf(format, "%%%ds", len);
    scanf(format, str);
}

/**
 * @brief Prints the message to the console in red and prefixis it with ERROR:
 * 
 */
__attribute__((format(printf, 1, 2))) void print_error(const char *format, ...) {
    va_list arg;
    va_start(arg, format);

    econio_textcolor(COL_RED);
    printf("ERROR: ");
    vprintf(format, arg);
    econio_textcolor(COL_RESET);

    va_end(arg);
}
