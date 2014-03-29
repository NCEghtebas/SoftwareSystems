/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d, ", current->val);
        current = current->next;
    }
    printf("\n");
}

int pop(Node **head) {
    int retval;
    Node *next_node;
    //gets value of first node in list
    Node * first= *head; 

    if (first == NULL) {
        return -1;
    }

    next_node = first->next;
    retval = first->val;
    free(first);
    //this won't change head globally
    //first = next_node 
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    Node * first = *head;
    make_node(val, first);
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *first= *head;
    Node * next= first->next;
    int i=1;
    if(first->val == val)
    {
        pop(&first); 
        *head= first;
        return i;
    }else
    {
        while (next != NULL) 
        {
            if(next->val == val)
            {
                first->next= next->next;
                pop(&next); 
                i+=1;
                return i;
            }else
            {
                first= first->next;
                next= next->next;
            }
        }
    }
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);
    test_list->next->next->next->next = make_node(5, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    print_list(test_list);
    remove_by_value(&test_list, 5);
    print_list(test_list);
    //remove_by_value(&test_list, 7);

    //reverse(&test_list);

    //print_list(test_list);
}
