#include "cutest/CuTest.h"
#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    

void TestMyMalloc0(CuTest *tc) {
  setup_heap();
  void *p1 = my_malloc(0);
  CuAssertPtrEquals(tc, NULL, p1);
  teardown_heap();
}

void TestMyMalloc1(CuTest *tc) {
  setup_heap();
  my_malloc(20);
  void * x = my_malloc(8);
  void * z = my_malloc(12);
  my_malloc(4);

  CuAssertIntEquals(tc, 44, live_data());
  CuAssertIntEquals(tc, 964, free_space());
  
  my_free(x);
  
  CuAssertIntEquals(tc, 972, free_space());
  CuAssertIntEquals(tc, 36, live_data());

  my_malloc(40);
  
  CuAssertIntEquals(tc, 76, live_data());
  CuAssertIntEquals(tc, 928, free_space());

  x = my_malloc(8);

  CuAssertIntEquals(tc, 84, live_data());
  CuAssertIntEquals(tc, 920, free_space());

  my_free(x);

  CuAssertIntEquals(tc, 928, free_space());
  CuAssertIntEquals(tc, 76, live_data());
  
  my_malloc(4); //8

  CuAssertIntEquals(tc, 84, live_data());
  CuAssertIntEquals(tc, 920, free_space());

  my_free(z);

  CuAssertIntEquals(tc, 932, free_space());
  CuAssertIntEquals(tc, 72, live_data());

  my_malloc(4);

  CuAssertIntEquals(tc, 76, live_data());
  CuAssertIntEquals(tc, 924, free_space());
  
  teardown_heap();
}

void Test(CuTest * tc){
  setup_heap();
  
  my_malloc(20);
  void* x = my_malloc(4);
  void* y = my_malloc(16);
  my_malloc(40);

  CuAssertIntEquals(tc, 80, live_data());
  CuAssertIntEquals(tc, 928, free_space());
  
  my_free(y);
  my_free(x);

  CuAssertIntEquals(tc, 60, live_data());
  CuAssertIntEquals(tc, 948, free_space());
    
  my_malloc(8);

  CuAssertIntEquals(tc, 68, live_data());
  CuAssertIntEquals(tc, 936, free_space());
  
  teardown_heap();
}

void TestFullHeap(CuTest * tc){
  setup_heap();

  void* x = my_malloc(1024);
  my_malloc(8);
  
  CuAssertIntEquals(tc, 1024, live_data());
  CuAssertIntEquals(tc, 0, free_space());

  my_free(x);
  CuAssertIntEquals(tc, 0, live_data());
  CuAssertIntEquals(tc, 1024, free_space());
  
  my_malloc(1016);
  my_malloc(8);

  CuAssertIntEquals(tc, 1016, live_data());
  CuAssertIntEquals(tc, 4, free_space());
  
  teardown_heap();
}

void TestMyFreeOnFreeEntry(CuTest * tc){
  setup_heap();
  int result = my_free(current_free_list);
  CuAssertIntEquals(tc, 0, result);
  teardown_heap();
}

void Fragmentation (CuTest * tc){
  setup_heap();
  
  void * a = my_malloc(12);
  my_malloc(12);
  void * b = my_malloc(12);
  my_malloc(12);
  void * c = my_malloc(12);
  my_malloc(12);
  void * d = my_malloc(12);
  my_malloc(12);
  void * e = my_malloc(12);
  my_malloc(12);
  void * f = my_malloc(12);
  my_malloc(12);
  void * g = my_malloc(12);
  my_malloc(12);
  void * h = my_malloc(12);
  my_malloc(12);
  void * i = my_malloc(12);
  my_malloc(12);
  void * j = my_malloc(12);
  my_malloc(12);
  void * k = my_malloc(12);
  my_malloc(12);
  void * l = my_malloc(12);
  my_malloc(12);
  void * m = my_malloc(12);
  my_malloc(12);
  void * n = my_malloc(12);
  my_malloc(12);
  void * o = my_malloc(12);
  my_malloc(12);
  void * p = my_malloc(12);
  my_malloc(12);
  void * q = my_malloc(12);
  my_malloc(12);
  void * r = my_malloc(12);
  my_malloc(12);
  void * s = my_malloc(12);
  my_malloc(12);
  void * t = my_malloc(12);
  my_malloc(12);
  void * u = my_malloc(12);
  my_malloc(12);
  void * v = my_malloc(12);
  my_malloc(12);
  void * w = my_malloc(12);
  my_malloc(12);
  void * x = my_malloc(12);
  my_malloc(12);
  void * y = my_malloc(12);
  my_malloc(12);
  void * z = my_malloc(12);
  my_malloc(204);

  my_free(a);
  my_free(b);
  my_free(c);
  my_free(d);
  my_free(e);
  my_free(f);
  my_free(g);
  my_free(h);
  my_free(i);
  my_free(j);
  my_free(k);
  my_free(l);
  my_free(m);
  my_free(n);
  my_free(o);
  my_free(p);
  my_free(q);
  my_free(r);
  my_free(s);
  my_free(t);
  my_free(u);
  my_free(v);
  my_free(w);
  my_free(x);
  my_free(y);
  my_free(z); 

  CuAssertIntEquals(tc, 508, live_data());  
  CuAssertIntEquals(tc, 312, free_space());

  void* test = my_malloc(10000);

  CuAssertPtrEquals(tc, NULL, test);
    
  teardown_heap();
}

/*
 * Note that as you add new testing functions, you need to add them to the
 * list below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  //SUITE_ADD_TEST(suite, TestMyMalloc0);
  //SUITE_ADD_TEST(suite, TestMyMalloc1);
  //SUITE_ADD_TEST(suite, Test);
  //SUITE_ADD_TEST(suite, TestFullHeap);
  SUITE_ADD_TEST(suite, Fragmentation);
  //SUITE_ADD_TEST(suite, TestMyFreeOnFreeEntry);
  return suite;
}
