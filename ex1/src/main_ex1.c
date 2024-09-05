#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define CAPACITY 10
#define NITEMS 0


#include "merge_binary_insertion_sort.h"
/*  Record structure creation */
struct record{      
    int id;
    char* field1;
    int field2;
    float field3;
};


static int precedes_record_int_field(const void* r1_p, const void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if(rec1_p->field2 < rec2_p->field2)
    return(-1);
  else if (rec1_p->field2 > rec2_p->field2)
    return(1);
  return(0);
}


static int precedes_record_string_field(const void* r1_p,const void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_string_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_string_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  return(strcasecmp(rec1_p->field1,rec2_p->field1));
    
  
}

static int precedes_record_float_field(const void* r1_p, const void* r2_p){
    if(r1_p == NULL){
    fprintf(stderr,"precedes_record_float_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_float_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if(rec1_p->field3 < rec2_p->field3)
    return(-1);
  else if(rec1_p->field3 > rec2_p->field3)
    return(1);
return(0);
}

void sort_records(const char *infile, const char *outfile, size_t k, size_t field){

    size_t size = sizeof(struct record);
    FILE* in;
    in = fopen(infile,"r");
    if(in == NULL){
        fprintf(stderr,"main: unable to open the file %s\n",infile);
        exit(EXIT_FAILURE);
    }
    char* read_line_p = malloc(1024);
    size_t nitems = 0;
    size_t capacity = 10;
    struct record* base = malloc(sizeof(struct record)*capacity);
    clock_t startC = clock();
    printf("\nInzio Caricamento\n");
    while (1) {
        if (fgets(read_line_p, 1024, in) == NULL) break;
        if (strlen(read_line_p) < 5) break;
        if (nitems == capacity) {
            capacity = capacity+10;    // rallente rispetto a capacity*2 ma spreca meno memoria
            base = realloc(base, sizeof(struct record)*capacity);
        }
        char* s = read_line_p + strlen(read_line_p) - 1;
        while (s[0] != ',') s--;
        base[nitems].field3 = (float)atof(s+1);
        s[0] = 0;
        while (s[0] != ',') s--;
        base[nitems].field2 = atoi(s+1);
        s[0] = 0;
        while (s[0] != ',') s--;
        base[nitems].field1 = malloc(strlen(s+1)+1);
        strcpy(base[nitems].field1, s+1);
        s[0] = 0;
        base[nitems].id = atoi(read_line_p);
        ++nitems;
    }
    clock_t endC = clock();
    printf("\nFine, tempo di caricamento = %f s",((double)(endC-startC))/CLOCKS_PER_SEC);

    int (*compar)(const void*, const void*) = NULL;
    
    switch(field){
        case 1:
            compar = precedes_record_string_field;
            break;
        case 2:
            compar = precedes_record_int_field;
            break;
        case 3:
            compar = precedes_record_float_field;
            break;

    }
    printf("\n\nnitems %lu\n\n", nitems);
    printf("\nInizio esecuzione algoritmo con k=%lu\n", k);

    clock_t start = clock();
    merge_binary_insertion_sort(base, nitems, size , k , compar); 
    clock_t end = clock();
    
    printf("\nFine, tempo di ordinamento = %f s   \n",((double)(end-start))/CLOCKS_PER_SEC);
    FILE* out;
    out = fopen(outfile, "w");

    printf("\nScrivo records su file...\n\n\n");

    for (int i=0; i<(int)nitems; ++i)
    fprintf(out, "%d,%s,%d,%lf\n", base[i].id, base[i].field1, base[i].field2, base[i].field3);
    free(read_line_p);
    for (int i=0; i<(int)nitems; ++i) free(base[i].field1);
    free(base);
   
    
    
    

}



int main(int argc, char const *argv[])
{
    if(argc !=5){
        return(EXIT_FAILURE);
    }
    sort_records(argv[1], argv[2],(size_t)atoi(argv[3]),(size_t)atoi(argv[4]));
    return (EXIT_SUCCESS);
}



