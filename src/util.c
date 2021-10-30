#include "util.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Instantiates a matrix with the specified size
 * and the specified number of rows and columns
 * ATTENTION: Only free this with free_matrix
 * 
 * @param rows Number of rows
 * @param cols Number of columns
 * @param size Size of 1 memory cell
 * @return void** 
 */
void **init_matrix(int rows, int cols, size_t size) {
    assert(rows > 0 && cols > 0);
    void **matrix = malloc(rows * sizeof(void *));
    matrix[0] = malloc(rows * cols * size);
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
void free_matrix(void **matrix) {
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
 * @brief Prints the message to the console in red and prefixis it with ERROR:
 * 
 */
__attribute__((format(printf, 1, 2))) void print_error(const char *format, ...) {
    va_list arg;
    va_start(arg, format);

    printf(BOLDRED "ERROR: ");
    vprintf(format, arg);
    printf(RESET);

    va_end(arg);
}
