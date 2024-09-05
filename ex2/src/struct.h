struct Node {
  struct Node **next;
  size_t size;
  void *item;
};


struct SkipList {
  struct Node **heads;
  size_t max_level;
  size_t max_height;
  int (*compare)(const void*, const void*);
};
