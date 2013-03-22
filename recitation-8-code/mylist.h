#ifndef _MYLIST_H_
#define _MYLIST_H_

/*
 * A node in a linked list.
 */
struct Node {
    void *data;
    struct Node *next;
};

/*
 * A linked list.  
 * 'head' points to the first node in the list.
 */
struct List {
    struct Node *head;
};

/*
 * Initialize an empty list.  
 */
static inline void initList(struct List *list)
{
    list->head = 0;
}

/*
 * In all functions below, the 'list' parameter is assumed to point to
 * a valid List structure.
 */

/*
 * Create a node that holds the given data pointer,
 * and add the node to the front of the list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addFront(struct List *list, void *data);

/*
 * Create a node that holds the given data pointer,
 * and add the node to the end of the list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 *
 * Note that this function takes O(n) running time (i.e., the running
 * time is proportional to the number of nodes in the list).
 */
struct Node *addBack(struct List *list, void *data);

/*
 * Traverse the list, calling f() with each data item.
 */
void traverseList(struct List *list, void (*f)(void *));

/*
 * Traverse the list, comparing each data item with 'dataSought' using
 * 'compar' function.  ('compar' returns 0 if the data pointed to by
 * the two parameters are equal, non-zero value otherwise.)
 *
 * Returns the first node containing the matching data, 
 * NULL if not found.
 */
struct Node *findNode(struct List *list, const void *dataSought,
	int (*compar)(const void *, const void *));

/*
 * Flip the sign of the double value pointed to by 'data' by
 * multiplying -1 to it and putting the result back into the memory
 * location.
 */
void flipSignDouble(void *data);

/*
 * Compare two double values pointed to by the two pointers.
 * Return 0 if they are the same value, 1 otherwise.
 */
int compareDouble(const void *data1, const void *data2);

/*
 * Returns 1 if the list is empty, 0 otherwise.
 */
static inline int isEmptyList(struct List *list)
{
    return (list->head == 0);
}

/*
 * Remove the first node from the list, deallocate the memory for the
 * ndoe, and return the 'data' pointer that was stored in the node.
 * Returns NULL is the list is empty.
 */
void *popFront(struct List *list);

/*
 * Remove all nodes from the list, deallocating the memory for the
 * nodes.  You can implement this function using popFront().
 */
void removeAllNodes(struct List *list);

/*
 * Create a node that holds the given data pointer,
 * and add the node right after the node passed in as the 'prevNode'
 * parameter.  If 'prevNode' is NULL, this function is equivalent to
 * addFront().
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addAfter(struct List *list, 
	struct Node *prevNode, void *data);

/* 
 * Reverse the list.
 *
 * Note that this function reverses the list purely by manipulating
 * pointers.  It does NOT call malloc directly or indirectly (which
 * means that it does not call addFront() or addAfter()).
 *
 * Implementation hint: keep track of 3 consecutive nodes (previous,
 * current, next) and move them along in a while loop.  Your function
 * should start like this:


      struct Node *prv = NULL;
      struct Node *cur = list->head;
      struct Node *nxt;

      while (cur) {
          ......


 * And at the end, prv will end up pointing to the first element of
 * the reversed list.  Don't forget to assign it to list->head.
 */
void reverseList(struct List *list);

#endif /* #ifndef _MYLIST_H_ */
