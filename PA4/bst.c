#include "bst.h"
#include <stdio.h>
#include <string.h>

/**
 *  bst_findHelper - finds a Node in the tree
 *
 *  Parameters:
 *    BSTNode* node2find - the node to find
 *    BSTNode* prevNode - the previouss node

 *  Return value: If the node was found or not by a 1 or 0 respectively.
 */
int bst_findHelper(struct BSTNode* node2find, struct BSTNode* prevNode){

  //Compares the strings
  int val = strcmp(node2find->key, prevNode->key);

  //If the node's key is smaller than previos node
  if (val < 0){

    //If prevNode's left node is empty then return false
    if(prevNode->left == NULL){
      return 0;
    }

    //Else call the function again with the left node
    else{
      return bst_findHelper(node2find, prevNode->left);
    }
  }

  //If the node's key is bigger than previous node
  if (val > 0){

    //If prevNode's right node is empty then return false
    if(prevNode->right == NULL){
      return 0;
    }

    //Else call the function again with the right node
    else{
      return  bst_findHelper(node2find, prevNode->right);
    }
  }

  else{
    //Else the keys match then return 1 to say it was found
    return 1;
  }
}

/**
 *  bst_addHelper - Adds a Node to the tree
 *
 *  Parameters:
 *    BSTNode* newNode - the node to add
 *    BSTNode* prevNode - the previos node
 *
 *  Return value: If the key is already there
 */
int bst_addHelper(struct BSTNode* newNode, struct BSTNode* prevNode){

  //Compares the strings
  int val = strcmp(newNode->key, prevNode->key);
  
  //If the new node's key is smaller than previos node
  if (val < 0){

    //If prevNode's left node is empty then add the node there
    if(prevNode->left == NULL){
    prevNode->left = newNode;

    //Return after adding the node 
    return 0;
    }

    //Else call the function again with the left node
    else{
      return bst_addHelper(newNode, prevNode->left);
    }
  }

  //If the new node's key is bigger than previous node
  else if (val > 0){
    
    //If prevNode's right node is empty then add the node there
    if(prevNode->right == NULL){
      prevNode->right = newNode;

      //Return after adding the node
      return 0;
    }
    
    //Else call the function again with the right node
    else{
      return bst_addHelper(newNode, prevNode->right);	
    }
  }

  else{
    //Else the keys match and return without adding the node 
    return 1;
  }
}

/**
 *  bst_deleteTreeHelper - Deletes all nodes in a tree
 *
 *  Parameters:
 *    struct BSTNode* node - The node to delete.
 *
 */
 void bst_deleteTreeHelper (struct BSTNode* node){
   //go left
   if (node->left){
     bst_deleteTreeHelper(node->left);
   }

   //go right
   if (node->right){
     bst_deleteTreeHelper(node->right);
   }

   //Free node
   free(node->key);
   free(node);
   node = NULL;
 }

/**
 *  deleteNode - deletes a node depending on the amount of childs it has
 *
 *  Parameters:
 *    BSTNode* node2del - The node to delete
 *
 */
void deleteNode (struct BST* bst, struct BSTNode* node2del, struct BSTNode* pointerInParent){
  struct BSTNode* temp = NULL;
  struct BSTNode* replacement = node2del->right;
  int left = 0;
  int right = 0;

  //if Pointerinparent is null do nothing
  if(!(pointerInParent)){

  }

  //elseIf the node2del is left of PIP
  else if(pointerInParent->left == node2del){
    left = 1;
  }

  //Else its right
  else{
    right = 1;
  }

  //Case if no childs
  if (!(node2del->left) && !(node2del->right)){
    free(node2del->key);
    free(node2del);
    
    //If removing root
    if(node2del == bst->root){
      bst->root = NULL;
    }

    //Set appropiate pointer to null
    else if(left){
      pointerInParent->left = NULL;
    }
    else{
      pointerInParent->right = NULL;
    }
    return;
  }

  //Case if 1 child on left
  else if ((node2del->left) && !(node2del->right)){
    //Set temp to node2del
    temp = node2del;

    //If removing root
    if(node2del == bst->root){
      bst->root = node2del->left;
    }

    //Replace node2del with child in PIP
    else if(left){
      pointerInParent->left = node2del->left;
    }
    else{
      pointerInParent->right = node2del->left;
    }

    //Free node2del/temp
    free(temp->key);
    free(temp);
    return;
  }

  //Case if 1 child on right
  else if (!(node2del->left) && (node2del->right)){
    //Set temp to node2del
    temp = node2del;

    //If removing root
    if(node2del == bst->root){
      bst->root = node2del->right;
    }

    //Replace node2del with child in PIP
    else if(left){
      pointerInParent->left = node2del->right;
    }
    else{
      pointerInParent->right = node2del->right;
    }

    //Free node2del/temp
    free(temp->key);
    free(temp);
    return;
    ++right; //ignore, used to get rid of warning
  }

  //Case if 2 childs
  else {
    
    //Go left till there is no more
    while(replacement->left){
      temp = replacement;
      replacement = replacement->left;
    }
    
    //Switch left's
    replacement->left = node2del->left;

    //If the replacement wasn't the child immediately to the right
    if (node2del->right != replacement){
      replacement->right = node2del->right;

      //Removes replacement node from tree
      temp->left = NULL;
    }

    //If removing root then replace root with replacement
    if(!(pointerInParent)){
      bst->root = replacement;
    }

    //Replace node2del with replacement in PIP
    else if(left){
      pointerInParent->left = replacement;
    }
    else{
      pointerInParent->right = replacement;
    }

    //Free memory
    free(node2del->key);
    free(node2del);
  }
}

/**
 *  bst_removeHelper - Removes a node from tree if it exists and if so
 *                     calls a function to delete the node
 *
 *  Parameters:
 *    BSTNode* node2rem - the node to remove
 *    BSTNode* prevNode - the previos node
 */
void bst_removeHelper(struct BST* bst, struct BSTNode* node2Rem, struct BSTNode* prevNode,
struct BSTNode* pointerInParent){
  //Compares the strings
  int val = strcmp(node2Rem->key, prevNode->key);

  //If the new node's key is smaller than previos node
  if (val < 0){

    //If prevNode's left node is empty then node doesn't exist
    if(prevNode->left == NULL){

      //Return without removing node
      return;
    }

    //Else call the function again with the left node
    else{
      bst_removeHelper(bst, node2Rem, prevNode->left, prevNode);
    }
  }

  //If the new node's key is bigger than previous node
  else if (val > 0){

    //If prevNode's right node is empty then node doesn't exist
    if(prevNode->right == NULL){

      //Return without removing node
      return;
    }

    //Else call the function again with the right node
    else{
      bst_removeHelper(bst, node2Rem, prevNode->right, prevNode);
    }
  }

  else{
    //Else the keys match then remove node2Rem
    deleteNode(bst, prevNode, pointerInParent);
  }
}

/**
 *  bst_makeNode - Makes a New Node for the Tree
 *
 *  Parameters:
 *    char* key - They string to store
 *    BSTNode* left - the left node
 *    BSTNode* right - the right node 

 *  Return value: The new node made
 */
struct BSTNode* bst_makeNode(char* key, struct BSTNode* left,
			     struct BSTNode* right) {
  //Initiallizes Values
  struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  node->key = strdup(key);
  node->left = left;
  node->right = right;

  //Returns Node
  return node;  
}

/**
 *  bst_add - Makes a new node from key and calls helper function
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree
 *    char* key - the sting for the new node
 */
void bst_add(struct BST* bst, char* key){
  //Makes a new node with key
  struct BSTNode* newNode = bst_makeNode(key, NULL, NULL);
  int retval = 0; //return value
  
  //If tree has a root
  if(bst->root){
  //Calls the helper function which adds node to tree
   retval = bst_addHelper(newNode, bst->root);
  }

  else{
    bst->root = newNode;
  }

  //If node already there then delete newNode
  if(retval == 1){
    free(newNode->key);
    free(newNode);
  }
}

/**
 *  bst_remove - Makes a new node from key and calls helper function
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree
 *    char* key - the string of the node to be removed
 */
void bst_remove(struct BST* bst, char* key){
  //Checks for empty tree
  if(!(bst->root)){
    return;
  }
  
  //Makes a new node with key
  struct BSTNode* node2Rem = bst_makeNode(key, NULL, NULL);

  //Calls the helper function which removes node from tree
  bst_removeHelper(bst, node2Rem, bst->root, NULL);

  free(node2Rem->key);
  free(node2Rem);
}

/**
 *  bst_contains - Calls function to find a key then returns 1 if found,
 *                 0 otherwise.
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree.
 *    char* - The key to find in the tree
 *
 *  Return value: True or false on whether it found it or not
 */
int bst_contains(struct BST* bst, char* key){
  //Checks for empty tree
  if(!(bst->root)){
    return 0;
  }
  
  //Make a node with key
  struct BSTNode* node2find = bst_makeNode(key, NULL, NULL);
  int retval; //hold return value

  //Calls the helper funcion to find node and returns whether it was found or not
  retval =  bst_findHelper(node2find, bst->root);

  //frees temp node
  free(node2find->key);
  free(node2find);
  return retval;
}


/**
 *  bst_min - finds the key of the smallest (leftmost) node in this bst.
 *
 *  Parameters:
 *    struct BST* bst - tree whose smallest node we're looking for.
 *
 *  Return value: smallest key in the tree, or
 *    empty string if tree is empty.
 */
char* bst_min(struct BST* bst){
  //Node to hold root
  struct BSTNode* node = bst->root;

  //Condition if tree is empty or not
  if (node) {
    //Loop to go left until there is no more nodes
    while (node->left) {
      node = node->left;
    }

    //Return smallest key
    return node->key;
  }

  //Tree empty case
  else {
    return NULL;
  }
}
  
/**
 *  bst_max - finds the key of the largest (rightmost) node in this bst.
 *
 *  Parameters:
 *    struct BST* bst - tree whose largest node we're looking for.
 *
 *  Return value: largest key in the tree, or
 *    empty string if tree is empty.
 */
char* bst_max(struct BST* bst) {
  struct BSTNode* node = bst->root;
  if (node) {
    while (node->right) {
      node = node->right;
    }
    return node->key;
  } else {
    return NULL;
  }
}

/**
 *  bst_count - Calls count is assembly to find out total nodes in tree
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree
 *
 *  Return value: Number of nodes in tree
 */
int bst_count(struct BST* bst){

  //calls count function in assembly and returns value
  return count(bst->root);;
}

/**
 *  bst_totalLength - Calls total length in assembley to find total length
 *                    of all keys in tree
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree
 *
 *  Return value: Total lenght of all keys in tree
 */
int bst_totalLength(struct BST* bst){

  //calls totalLength function in assembly and returns value
  return totalLength(bst->root);
}

/**
 *  bst_deletesTree - Calls function to delete all nodes if tree isn't
 *                    empty and frees tree.
 *
 *  Parameters:
 *    struct BST* bst - The binary search tree to delete.
 *
 */
void bst_deleteTree(struct BST* bst){
  //Node to hold root
  struct BSTNode* node = bst->root;

  //Condition if tree is empty or not
  if (node) {
    bst_deleteTreeHelper(node);
  }

  //Free tree
  free(bst);
}
