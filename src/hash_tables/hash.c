#include "hash.h"

/**
 * @brief It generates an intiger based on the key
 * Copied from here: http://www.cse.yorku.ca/~oz/hash.html
 * 
 * @param key The key the hash is based on
 * @return int The generated intiger
 */
int hash(const char *key) {
    int hash = 5381;
    int c;

    while ((c = *key++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
