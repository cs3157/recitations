Linked Lists
============
Linked Lists are one of many different data structures that use nodes to store data in a structured format. The nodes from all these classes share a consistent similarity: they all hold some **data** and **point to** one or more other **nodes**. Other node structures include:

-   Trees
-   Heaps
-   Graphs

Singly Linked Lists
-------------------
In Lab 3, what we are asked to do is implement a singly linked list. Those of you who took Data Structures (and Algorithms) will be familiar with linked lists, and thus most of this lab is converting what you know about linked lists in Java to C. For those who have no idea what a linked list is, keep reading on.

A *singly* linked list, as opposed to a *doubly* linked list, is a node structure as shown below:  
`Node: [data|next]`  
A *doubly* linked list would have this node structure:  
`Node: [prev|data|next]`  
prev and next are variables that refer to the previous and next node in the list, respectively. data could be a pointer to or the actual data that the list is to contain. From here on out, we'll just be talking about singly linked lists.

### The Lab 3 List Structure
`[data|next-]>[data|next-]>[data|next-]>...[data|next-]>NULL`  
`head^`  
As you can see above, our linked list is just a collection of nodes. Each node has a next pointer, a `struct Node *` that points to the next element of the list. The last node points to `NULL`. data is a `void *`, a pointer to some piece of data that we do not manage. This means our list obeys _pointer semantics_, as opposed to _value semantics_. This means that our list does not manage the data the user wishes to use, it simply presents an organized and usable structure to access that data.

Making a Linked List
--------------------
By itself, our linked list is just a pointer to a node:  
<code>struct List {<br />
&nbsp;&nbsp;&nbsp;&nbsp;struct Node &#42;head;<br />
}</code><br />
It's no better than a node, really. However, what makes a linked list a *linked list* is the functions it provides. These functions present a number of default ways for a programmer to use the given list, and thus create the illusion of being able to access every node in this list, even though in our code we only list the head node.  
So lets get into these functions shall we?

### Add Front
`struct Node *addFront(struct List *list, void *data)`  
The job of this function is simple. We:

- Make a new node to store data: a pointer to some variable the user has. Set "next" of this new node appropriately.
- Change the head of the list to this node.

### Traverse List
`void traverseList(struct List *list, void (*f)(void *))`  
We visit each node in the list and call `f` on `data` as we visit each node. In order to move alonge the list, we start at the head, and then keep going to the next node until we reach the end, in which case the next node will be `NULL`.

### Flipping the Sign of a Double
`void flipSignDouble(void *data)`  
As per the name of the function, you can assume that data is a `double`. Flipping the sign of any number is pretty trivial; if we have a number called `i`, the `i = -i` will flip it's sign (or more accurately, return the flipped sign number and then store it in the same location). The difficulty in this function is that `data` is of type `void *`, so before you flip the sign, you must first cast it and then dereference it.

### Comparing Two Doubles.
`int compareDouble(const void *data1, const void *data2)`  
This function is similar to the last function. Just cast, dereference, and compare. Something you should not do though is:  
`data1 == data2`  
Doing this will almost never work, since `data1` and `data2` are pointers, and pointers are only equal when the memory address they point to are the same.

### Finding a Specific Node
`struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *))`  
This function is very similar to `traverseList` (funny, it's like this lab is building on itself). Instead of calling `f`, we are calling `compar` which takes two arguments, the `data` from the node we are currently at and `dataSought`. There is a caveat though, which is that we should return the node we are currently at if `compar` returns 0. Not a significant departure from `traverseList`, though.

### Removing the Head of a List
`void *popFront(struct List *list)`  
This function is the functional reverse of `addFront`:

- Change the head of the list to the next node.
- Unallocated the old head and return its `data`.

Be careful though, there's a particular order in which changing the head, unallocating the node, and getting and returning the data of the node must be done, otherwise you'll run into memory issues (of which valgrind will inform you).

### Removing All Nodes of a List
`void removeAllNodes(struct List *list)`  
There's a very easy way to solve this problem, and it involves two functions. So as not to completely remove the challenge of this problem, I'll let you figure them out.

### Adding a Node after another Node
`struct Node *addAfter(struct List *list, struct Node *prevNode, void *data)`  
`mylist.h` outlines this function pretty well:

- If `prevNode` is `NULL`, this function should behave just like `addFront`.
- Otherwise, assume `prevNode` to be in the list and add a new node containing `data` after `prevNode`.
    - Using the same idea as `findNode`, go through the list until you find your match.
    - Then, reroute some `next` pointers appropriately to "insert" the node you just made into the list.

### Reversing a List
`void reverseList(struct List *list)`  
Perhaps the trickiest function to write. There are two (and probably more) ways to solve this problem. I'll defer it to the internet to provide a proper explanation of them. One method is to make each node's `next` point to the previous node. If we have this list structure:  
`1[data|next]->2[data|next]->3[data|next]->...->n[data|next]->NULL`  
(where node 1 is the head) Then what we will do is this:  
`NULL<-[next|data]1<-[next|data]2<-[next|data]3<-...<-[next|data]n`  
(where node n is now the head)  
  
A perhaps simpler method is to create a temporary list. Traverse through the original list and then add each node to the front of the temporary list. The temporary list will be the reverse of the original list. Of course, there's an equivalent method that doesn't involve traversal, but still uses the same fundamental idea.

Revecho
-------
In part1, we create a library file called `libmylist.a` that contains our linked list. In this part, we use our linked list to reverse the command line arguments we are given and to find "dude" among them.  
  
Using the methods discussed above, and treating `char **argv` as a "list," we can easily reverse `argv` by adapting the two methods discussed in **Reversing a List**. Then to find "dude", we can write our own function or use the functionality of `findNode`. In the latter case we have to make a function to find "dude". We could, of course, just pass in "dude" as the `dataSought` and use `strcmp` in for `compar`, but we have to cast `strcmp` (from `<string.h>`) to the correct signature first. See K&R section 5.11 on how to do this.