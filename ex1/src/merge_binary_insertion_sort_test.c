#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "merge_binary_insertion_sort.h"

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

void test_merge_sort_null_array() {
  int* arr = NULL;
  merge(arr, 0, 0, sizeof(int), compar_int);
  TEST_ASSERT_NULL(arr);
}

void test_binary_insertion_sort_null_array() {
  int* arr = NULL;
  insertionSort(arr, 0, sizeof(int), compar_int);
  TEST_ASSERT_NULL(arr);
}

void test_merge_binary_insertion_sort_null_array() {
  int* arr = NULL;
  size_t k = 17;
  merge_binary_insertion_sort(arr, 0, sizeof(int), k, compar_int);
  TEST_ASSERT_NULL(arr);
}

void test_merge_sort_in_order_array() {
  int arr[] = {-176, 0, 9};
  int expected[] = {-176, 0, 9};
  merge(arr, 0, 2, sizeof(int), compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_binary_insertion_sort_in_order_array() {
  int arr[] = {-176, 0, 9};
  int expected[] = {-176, 0, 9};
  insertionSort(arr, 3, sizeof(int), compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_merge_binary_insertion_sort_in_order_array() {
  int arr[] = {-176, 0, 9};
  int expected[] = {-176, 0, 9};
  size_t k = 17;
  merge_binary_insertion_sort(arr, 3, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}


void test_binary_insertion_sort_two_el_equal_array() {
  int arr[] = {0, 22, 0};
  int expected[] = {0, 0, 22};
  insertionSort(arr, 3, sizeof(int), compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_merge_binary_insertion_two_el_equal_array() {
  int arr[] = {0, 22, 0};
  int expected[] = {0, 0, 22};
  size_t k = 17;
  merge_binary_insertion_sort(arr, 3, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}


void test_binary_insertion_sort_reverse_order_array() {
  int arr[] = {9, 0, -176};
  int expected[] = {-176, 0, 9};
  insertionSort(arr, 3, sizeof(int), compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_merge_binary_insertion_sort_reverse_order_array() {
  int arr[] = {9, 0, -176};
  int expected[] = {-176, 0, 9};
  size_t k = 17;
  merge_binary_insertion_sort(arr, 3, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}


void test_binary_insertion_sort_no_order_array() {
  int arr[] = {0, 9, -176};
  int expected[] = {-176, 0, 9};
  insertionSort(arr, 3, sizeof(int), compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_merge_binary_insertion_sort_no_order_array() {
  int arr[] = {0, 9, -176};
  int expected[] = {-176, 0, 9};
  size_t k = 17;
  merge_binary_insertion_sort(arr, 3, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 3);
}

void test_merge_binary_insertion_sort_k_equal_zero() {
  int arr[] = {-17, -114, 177, 153, -7, 153, -14};
  int expected[] = {-114, -17, -14, -7, 153, 153, 177};
  size_t k = 0;
  merge_binary_insertion_sort(arr, 7, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 7);
}

void test_merge_binary_insertion_sort_k_equal_one() {
  int arr[] = {-17, -114, 177, 153, -7, 153, -14};
  int expected[] = {-114, -17, -14, -7, 153, 153, 177};
  size_t k = 1;
  merge_binary_insertion_sort(arr, 7, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 7);
}

void test_merge_binary_insertion_sort_k_equal_five() {
  int arr[] = {-17, -114, 177, 153, -7, 153, -14};
  int expected[] = {-114, -17, -14, -7, 153, 153, 177};
  size_t k = 5;
  merge_binary_insertion_sort(arr, 7, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 7);
}

void test_merge_binary_insertion_sort_k_equal_nine_hundred() {
  int arr[] = {-17, -114, 177, 153, -7, 153, -14};
  int expected[] = {-114, -17, -14, -7, 153, 153, 177};
  size_t k = 900;
  merge_binary_insertion_sort(arr, 7, sizeof(int), k, compar_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 7);
}

int main(void) {

  //test session
  UNITY_BEGIN();
  
  RUN_TEST(test_merge_sort_null_array);
  RUN_TEST(test_binary_insertion_sort_null_array);
  RUN_TEST(test_merge_binary_insertion_sort_null_array);
  RUN_TEST(test_merge_sort_in_order_array);
  RUN_TEST(test_binary_insertion_sort_in_order_array);
  RUN_TEST(test_merge_binary_insertion_sort_in_order_array);
  RUN_TEST(test_binary_insertion_sort_two_el_equal_array);
  RUN_TEST(test_merge_binary_insertion_two_el_equal_array);
  RUN_TEST(test_binary_insertion_sort_reverse_order_array);
  RUN_TEST(test_merge_binary_insertion_sort_reverse_order_array);
  RUN_TEST(test_binary_insertion_sort_no_order_array);
  RUN_TEST(test_merge_binary_insertion_sort_no_order_array);
  RUN_TEST(test_merge_binary_insertion_sort_k_equal_zero);
  RUN_TEST(test_merge_binary_insertion_sort_k_equal_one);
  RUN_TEST(test_merge_binary_insertion_sort_k_equal_five);
  RUN_TEST(test_merge_binary_insertion_sort_k_equal_nine_hundred);
  

  return UNITY_END();
}