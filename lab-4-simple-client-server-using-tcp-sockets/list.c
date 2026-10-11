```c
// list/list.c
//
// Implementation for linked list.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// Allocate a new empty list
list_t *list_alloc() {
    list_t *mylist = malloc(sizeof(list_t));

    if (mylist == NULL) {
        return NULL;
    }

    mylist->head = NULL;

    return mylist;
}


// Free the entire list
void list_free(list_t *l) {
    if (l == NULL) {
        return;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        node_t *temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(l);
}


// Print the list
void list_print(list_t *l) {
    if (l == NULL) {
        printf("NULL\n");
        return;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        printf("%d->", curr->value);
        curr = curr->next;
    }

    printf("NULL\n");
}


// Return string representation of list
char *listToString(list_t *l) {
    char *buf = malloc(sizeof(char) * 10024);

    if (buf == NULL) {
        return NULL;
    }

    // Important: initialize the string
    buf[0] = '\0';

    char tbuf[20];

    if (l == NULL) {
        strcat(buf, "NULL");
        return buf;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        sprintf(tbuf, "%d->", curr->value);
        strcat(buf, tbuf);
        curr = curr->next;
    }

    strcat(buf, "NULL");

    return buf;
}


// Return length of list
int list_length(list_t *l) {
    if (l == NULL) {
        return 0;
    }

    int length = 0;
    node_t *curr = l->head;

    while (curr != NULL) {
        length++;
        curr = curr->next;
    }

    return length;
}


// Add element to back
void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *new_node = getNode(value);

    if (new_node == NULL) {
        return;
    }

    // Empty list
    if (l->head == NULL) {
        l->head = new_node;
        return;
    }

    node_t *curr = l->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
}


// Add element to front
void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *cur_node = getNode(value);

    if (cur_node == NULL) {
        return;
    }

    cur_node->next = l->head;
    l->head = cur_node;
}


// Create a new node
node_t *getNode(elem value) {
    node_t *mynode = malloc(sizeof(node_t));

    if (mynode == NULL) {
        return NULL;
    }

    mynode->value = value;
    mynode->next = NULL;

    return mynode;
}


// Add element at index
// Index starts at 1
void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL || index < 1) {
        return;
    }

    // Adding to front
    if (index == 1) {
        list_add_to_front(l, value);
        return;
    }

    node_t *curr = l->head;

    // Move to node before desired index
    for (int i = 1; i < index - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    // Index is outside the list
    if (curr == NULL) {
        return;
    }

    node_t *new_node = getNode(value);

    if (new_node == NULL) {
        return;
    }

    new_node->next = curr->next;
    curr->next = new_node;
}


// Remove element from back
elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }

    // Only one node
    if (l->head->next == NULL) {
        elem value = l->head->value;
        free(l->head);
        l->head = NULL;
        return value;
    }

    node_t *curr = l->head;

    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    elem value = curr->next->value;

    free(curr->next);
    curr->next = NULL;

    return value;
}


// Remove element from front
elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }

    node_t *temp = l->head;
    elem value = temp->value;

    l->head = temp->next;

    free(temp);

    return value;
}


// Remove element at index
// Index starts at 1
elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 1) {
        return -1;
    }

    // Remove first node
    if (index == 1) {
        return list_remove_from_front(l);
    }

    node_t *curr = l->head;

    // Move to node before target
    for (int i = 1; i < index - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    // Invalid index
    if (curr == NULL || curr->next == NULL) {
        return -1;
    }

    node_t *temp = curr->next;
    elem value = temp->value;

    curr->next = temp->next;

    free(temp);

    return value;
}


// Check if value exists in list
bool list_is_in(list_t *l, elem value) {
    if (l == NULL) {
        return false;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        if (curr->value == value) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}


// Get element at index
// Index starts at 1
elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || index < 1) {
        return -1;
    }

    node_t *curr = l->head;

    for (int i = 1; i < index && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return -1;
    }

    return curr->value;
}


// Get index of value
// Index starts at 1
int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) {
        return -1;
    }

    node_t *curr = l->head;
    int index = 1;

    while (curr != NULL) {
        if (curr->value == value) {
            return index;
        }

        curr = curr->next;
        index++;
    }

    return -1;
}
```
