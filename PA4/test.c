#include "cutest/CuTest.h"
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    
void TestIfRightChildrenOrTreeBackwards(CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  bst_add(bst, "a");
  bst_add(bst, "b");
  bst_add(bst, "c");
  bst_add(bst, "d");
  bst_add(bst, "e");
  bst_add(bst, "f");
  bst_add(bst, "g");
  bst_add(bst, "h");
  bst_add(bst, "i");
  bst_add(bst, "j");
  bst_add(bst, "k");

  CuAssertPtrNotNull(tc, bst->root->right);

  bst_deleteTree(bst);
}

void TestIfNotAlwaysAdded(CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  bst_add(bst, "n");
  bst_add(bst, "e");
  bst_add(bst, "s");
  bst_add(bst, "i");
  bst_add(bst, "c");
  bst_add(bst, "p");
  bst_add(bst, "v");
  bst_add(bst, "b");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");

  CuAssertIntEquals(tc, 1, bst_contains(bst, "n"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "e"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "s"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "i"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "c"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "p"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "v"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "b"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "a"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "y"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "z"));

  bst_deleteTree(bst);
}

void TestRemoveNode(CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  bst_add(bst, "n");
  bst_add(bst, "e");
  bst_add(bst, "s");
  bst_add(bst, "i");
  bst_add(bst, "c");
  bst_add(bst, "p");
  bst_add(bst, "v");
  bst_add(bst, "b");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");

  bst_remove(bst, "a");
  bst_remove(bst, "b");
  bst_remove(bst, "n");
  bst_remove(bst, "i");
  bst_remove(bst, "e");
  bst_remove(bst, "y");
  bst_remove(bst, "v");
  bst_remove(bst, "z");
  bst_remove(bst, "s");
  bst_remove(bst, "e");
  bst_remove(bst, "c");

  CuAssertIntEquals(tc, 0, bst_contains(bst, "n"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "e"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "s"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "i"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "c"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "p"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "v"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "b"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "a"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "y"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "z"));
 
  bst_deleteTree(bst);
}


void TestCount (CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;
  
  bst_add(bst, "n");
  bst_add(bst, "e");
  bst_add(bst, "s");
  bst_add(bst, "i");
  bst_add(bst, "c");
  bst_add(bst, "p");
  bst_add(bst, "v");
  bst_add(bst, "b");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");
  
  CuAssertIntEquals(tc, 11, bst_count(bst));

  bst_deleteTree(bst);
}

void TestTotalLength (CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  bst_add(bst, "nope");
  bst_add(bst, "emu");
  bst_add(bst, "suck");
  bst_add(bst, "ice");
  bst_add(bst, "vein");

  CuAssertIntEquals(tc, 18, bst_totalLength(bst));

  bst_deleteTree(bst);
}

void TestMaxAndMin (CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  bst_add(bst, "a");
  bst_add(bst, "edsf");
  bst_add(bst, "ssdf");
  bst_add(bst, "icasd");
  bst_add(bst, "csadgf");
  bst_add(bst, "padsf");
  bst_add(bst, "vastr");
  bst_add(bst, "bsdh");
  bst_add(bst, "kwerg");
  bst_add(bst, "xwerg");
  bst_add(bst, "twerg");
  bst_add(bst, "mwer");
  bst_add(bst, "ajrey");
  bst_add(bst, "awery");
  bst_add(bst, "aawetr");
  bst_add(bst, "zqwr");
  bst_add(bst, "zwegd");
  bst_add(bst, "zqwerg");
  bst_add(bst, "uqry");

  CuAssertStrEquals(tc, "a", bst_min(bst));
  CuAssertStrEquals(tc, "zwegd", bst_max(bst));

  bst_deleteTree(bst);
}

void TestSearch (CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;

  CuAssertIntEquals(tc, 0, bst_contains(bst, "n"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "e"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "s"));

  bst_add(bst, "root");

  bst_remove(bst, "root");

  CuAssertIntEquals(tc, 0, bst_contains(bst, "root"));

  bst_add(bst, "n");
  bst_add(bst, "e");
  bst_add(bst, "s");
  bst_add(bst, "i");
  bst_add(bst, "c");
  bst_add(bst, "p");
  bst_add(bst, "v");
  bst_add(bst, "b");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");

  bst_remove(bst, "n");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "n"));

  bst_remove(bst, "a");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "a"));

  bst_remove(bst, "b");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "b"));

  bst_remove(bst, "n");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "nop"));

  bst_remove(bst, "i");
  bst_add(bst,"h");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "ifg"));

  bst_remove(bst, "e");
  bst_add(bst, "ee");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "e"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "eeeee"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "eee"));

  bst_remove(bst, "y");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "y"));

  bst_remove(bst, "v");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "v"));

  bst_remove(bst, "z");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "z"));

  bst_remove(bst, "s");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "s"));

  bst_remove(bst, "e");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "e"));

  bst_remove(bst, "c");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "c"));


  bst_deleteTree(bst);
}


void Test (CuTest *tc){
  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
  bst->root = NULL;
  
  bst_add(bst, "n");
  bst_add(bst, "e");
  bst_add(bst, "s");
  bst_add(bst, "i");
  bst_add(bst, "c");
  bst_add(bst, "p");
  bst_add(bst, "v");
  bst_add(bst, "b");
  bst_add(bst, "a");
  bst_add(bst, "y");
  bst_add(bst, "z");
  
  CuAssertStrEquals(tc, "a", bst_min(bst));
  CuAssertStrEquals(tc, "z", bst_max(bst));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "i"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "m"));

  bst_remove(bst, "a");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "a"));

  bst_remove(bst, "z");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "z"));
  
  bst_remove(bst, "q");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "q"));

  bst_remove(bst, "c");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "c"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "b"));

  bst_remove(bst, "v");
  CuAssertIntEquals(tc, 0, bst_contains(bst, "v"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "y"));
  
  bst_add(bst, "u");
  bst_add(bst, "t");
  CuAssertIntEquals(tc, 1, bst_contains(bst, "t"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "u"));
  
  bst_remove(bst, "s");
  CuAssertIntEquals(tc, 1, bst_contains(bst, "n"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "e"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "i"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "p"));
  CuAssertIntEquals(tc, 0, bst_contains(bst, "s"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "p"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "y"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "t"));
  CuAssertIntEquals(tc, 1, bst_contains(bst, "u"));
    
  bst_deleteTree(bst);
}

/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestIfRightChildrenOrTreeBackwards);
  SUITE_ADD_TEST(suite, TestIfNotAlwaysAdded);
  SUITE_ADD_TEST(suite, TestRemoveNode);
  SUITE_ADD_TEST(suite, Test);
  SUITE_ADD_TEST(suite, TestCount);
  SUITE_ADD_TEST(suite, TestTotalLength);
  SUITE_ADD_TEST(suite, TestMaxAndMin);
  SUITE_ADD_TEST(suite, TestSearch);
  return suite;
}
