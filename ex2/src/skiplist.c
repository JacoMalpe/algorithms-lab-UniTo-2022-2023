#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#include "skiplist.h"

size_t randomLevel(size_t);

struct Node* createNode(void* item, int size) {
    struct Node* n = malloc(sizeof(struct Node));
    n->next = (struct Node**)calloc((size_t)size, sizeof(struct Node*));
    n->size = (size_t)size;
    n->item = item;
    return n;
}

void new_skiplist(struct SkipList** list, size_t max_height, int (*compar)(const void*, const void*)) {
    struct SkipList* s_list = (struct SkipList*)malloc(sizeof(struct SkipList));
    s_list->compare = compar;
    s_list->max_level = 1;
    s_list->max_height = max_height;
    s_list->heads = (struct Node**)calloc(max_height, sizeof(struct Node*));
    (*list) = s_list;
}


void clear_skiplist(struct SkipList **list){
    if(*list == NULL){
    fprintf(stderr,"clear_skiplist: SkipList pointer cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  struct Node** n = (*list)->heads;
  struct Node** tmp;

  if(n == NULL || n[0] == NULL){
    return;
  }

  while(n[0] != NULL){
    tmp = n;
    n = n[0]->next;
    free(tmp);
  }

  free(*list);
  *list = NULL;
}


void insert_skiplist(struct SkipList* list, void* item) {
    size_t new_level = randomLevel(list->max_height);
    struct Node* new_node = createNode(item, (int)new_level);

    if (new_level > list->max_level)
        list->max_level = new_level;

    struct Node** x = list->heads;
    for(int k = (int)list->max_level-1; k >= 0; k--){
    if(x[k] == NULL || list->compare(item, x[k]->item) < 0){
      if((size_t)k < new_node->size){
        new_node->next[k] = x[k];
        x[k] = new_node;
      }
    }
    else{
      x = x[k]->next;
      k++;
    }
  }
}

const void* search_skiplist(struct SkipList *list, void *item){
if(list == NULL){
    fprintf(stderr,"search_skiplist: SkipList pointer cannot be NULL\n");
    exit(EXIT_FAILURE);
  }
  struct Node** x = list->heads;
  for(int i = (int)list->max_level-1; i >= 0; i--){
    while(x[i] != NULL && list->compare(x[i]->item, item) < 0){
      x = x[i]->next;
    }
  }
  if (x[0] == NULL) return NULL;

  if(list->compare(x[0]->item, item) == 0)
    return x[0]->item;
  else
    return NULL;
}


size_t randomLevel(size_t max_height) {
    double rand_val = (double)random() / RAND_MAX;
    size_t lv1 = 1;
    srand((unsigned int)clock());
    while (lv1 < max_height && rand_val < 0.5) {
        rand_val = (double)random() / RAND_MAX;
        lv1++;
    }
    return lv1;
}
