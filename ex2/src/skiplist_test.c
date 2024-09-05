#include <stdio.h>
#include "unity.h"
#include "skiplist.h"

//precedence relation used in tests
static int compar_int(const void* i1_p, const void* i2_p){
  int* int1_p = (int*)i1_p;
  int* int2_p = (int*)i2_p;
  if(*int1_p > *int2_p)
    return 1;
  if (*int1_p == *int2_p)
    return 0;
  return -1;
}

//Data elements that are initialized before each test
static int i1, i2, i3;
static struct SkipList *list;

void setUp(){
  i1 = -27;
  i2 = 0;
  i3 = 11;
  new_skiplist(&list, 5, compar_int);
}

void tearDown(){
  clear_skiplist(&list);
}

void test_skiplist_insert_search_one_el_present(){
  insert_skiplist(list, &i1);
  TEST_ASSERT_EQUAL_INT(-27, *(int*)search_skiplist(list, &i1));
}

void test_skiplist_insert_search_one_el_not_present(){
  insert_skiplist(list, &i1);
  TEST_ASSERT_NULL(search_skiplist(list, &i2));
}

void test_skiplist_insert_search_three_el(){
  int expected[] = {-27, 0, 11};
  insert_skiplist(list, &i1);
  insert_skiplist(list, &i2);
  insert_skiplist(list, &i3);
  int arr[3];
  arr[0] = *(int*)search_skiplist(list, &i1);
  arr[1] = *(int*)search_skiplist(list, &i2);
  arr[2] = *(int*)search_skiplist(list, &i3);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_skiplist_insert_search_three_el_equal(){
  TEST_ASSERT_NULL(search_skiplist(list, &i1));
}

int main(void) {

  //test session
  UNITY_BEGIN();
  
  RUN_TEST(test_skiplist_insert_search_one_el_present);
  RUN_TEST(test_skiplist_insert_search_one_el_not_present);
  RUN_TEST(test_skiplist_insert_search_three_el);
  RUN_TEST(test_skiplist_insert_search_three_el_equal);
  
  return UNITY_END();
}