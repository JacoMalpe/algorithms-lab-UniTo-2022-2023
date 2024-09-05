#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "skiplist.h"

static int precedes_record_string_field(const void* r1_p, const void* r2_p) {
    if (r1_p == NULL) {
        fprintf(stderr, "precedes_record_string_field: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (r2_p == NULL) {
        fprintf(stderr, "precedes_record_string_field: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    return strcasecmp((const char*)(r1_p), (const char*)(r2_p));
}

void find_errors(const char* dictfile, const char* textfile, size_t max_height) {
    struct SkipList* list = NULL;
    new_skiplist(&list, max_height, precedes_record_string_field);
    char buffer[1024];
    int buf_size = 1024;

    FILE* dic;
    clock_t startL = clock();
    dic = fopen(dictfile, "r");
    if (dic == NULL) {
        fprintf(stderr, "find_errors: unable to open the file %s\n", dictfile);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, buf_size, dic) != NULL) {
        size_t length = strlen(buffer);
        buffer[length - 1] = '\0'; // Rimuovi il carattere di nuova riga

        char* word = strdup(buffer);
        insert_skiplist(list, word);
       
    }

    fclose(dic);
    clock_t endL = clock();
     printf("\nTempo caricamento Skiplist= %f s\n",((double)(endL-startL))/CLOCKS_PER_SEC);
    FILE* corr;
    corr = fopen(textfile, "r");
    if (corr == NULL) {
        fprintf(stderr, "find_errors: unable to open the file %s\n", textfile);
        exit(EXIT_FAILURE);
    }
    clock_t startC = clock();
    while (fgets(buffer, buf_size, corr) != NULL) {
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')
            buffer[length - 1] = '\0'; // Rimuovi il carattere di nuova riga

        char* word = strtok(buffer, " ,.:"); // Dividi la riga in parole utilizzando gli spazi e la punteggiatura come separatori
        while (word != NULL) {
            const void* item = search_skiplist(list, word);
            if (item == NULL)
                printf("\n%s ", word);

            word = strtok(NULL, " ,.:"); // Passa alla prossima parola
        }
        printf("\n");
    }
    clock_t endC = clock();
   
    printf("\nTempo esecuzione algoritmo= %f s\n\n\n",((double)(endC-startC))/CLOCKS_PER_SEC);
    fclose(corr);
    clear_skiplist(&list);
    
}

int main(int argc, char const* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <dictionary_file> <text_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t max_height = 200;
    find_errors(argv[1], argv[2], max_height);

    return EXIT_SUCCESS;
}
