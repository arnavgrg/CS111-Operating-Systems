/*
NAME: Arnav Garg
EMAIL ID: arnavgrg@ucla.edu
UID: 304911796
SLIPDAYS: 1
*/

//Import Libraries
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//Including header file for implemented functions
#include "SortedList.h"

//SortedList_insert ... insert an element into a sorted list
void SortedList_insert(SortedList_t *list, SortedListElement_t *element){
    //If element or list are NULL, return
    if ((element == NULL) || (list == NULL)) {
        return;
    } 
    //Create temporary variables for traversal
    SortedList_t *l = list;
    SortedList_t *curr = list->next;
    //If key is not null, then list pointer does not start at head
    if (l->key != NULL)
        return;
    //Traverse through linked list from the smallest value
    while (curr != list) {
        /*If element is greater than current element in LL
        break out since this is where we want to insert this element*/
        if (strcmp(curr->key, element->key) <= 0)
            break;
        //Traverse to next element
        l = curr;
        curr = curr->next;
    }
    /*Call sched_yield() if opt_yield and INSERT_YIELD before updating the 
    pointers and actually inserting the element*/
    if ((opt_yield) & (INSERT_YIELD))
        sched_yield();
    //LIST IS CIRCULAR!! End of the list goes back to beginning of the list
    /*Add element to the linked list between l and curr
    and update the elements next and previous pointers*/
    element->prev = l;
    /*If we don't go past the end of the LL Assigned element->next to point 
    to curr, and currents previous to point to the element*/
    element->next = l->next;
    //Go to l and update its next pointer to point to newly inserted element
    l->next = element; 
    //Go to curr and update its previous pointer to point to the newly inserted element
    element->next->prev = element;
    /*
    This is what it looks like after insertion
          ---->l--->element--->curr--->
    */
}

//SortedList_delete ... remove an element from a sorted list
int SortedList_delete(SortedListElement_t *element) {
    //If element is unassigned/NULL, can't delete so return 1
    if (element == NULL)
        return 1;
    /*check if it the program is trying to delete the head pointer, 
    if yes, we can't delete it so return 1*/
    if (element->key == NULL)
        return 1;
    //Save the elements current and next pointers
    SortedListElement_t *prev = element-> prev;
    SortedListElement_t *next = element-> next;
    /*If both the pointers are null, this element hasn't been added
    to the list yet/doesn't exist in the list, so delete it*/
    if ((prev == NULL) && (next == NULL))
        return 1;
    /*If previous element's next pointer does not point to element,
    or next elements previous pointer does not point to element, 
    pointers are corrupted so must return 1*/
    if ((next->prev != element) || (prev->next != element))
        return 1;
    /*e can delete the element passed in as an argument if this
    condition is satisfied*/
    if ((next->prev == element) && (prev->next == element)) {
        //If opt_yield set to 1 and DELETE_YIELD, then call sched_yield()
        if ((opt_yield) & (DELETE_YIELD))
            sched_yield();
        //Delete this element from the list
        prev->next = next;
        next->prev = prev;   
    }
    //Return 0 to indicate successful deletion
    return 0;
}

//SortedList_lookup ... search sorted list for a key
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key){
    //If list is a nullptr, return null
    if (list == NULL) {
        return NULL;
    }
    //No head pointer, so we have to return Null
    if (list->key != NULL) {
        return NULL;
    }
    //Set search to the smallest/first element in the list
    SortedListElement_t *search = list->next;
    //Traverse through linked list
    while (search != list) {
        //If the current pointers key is same as the key passed in
        //then reutnr the li
        if (strcmp(key, search->key) == 0){
            return search;
        }
        //If opt_yield & LOOKUP_YIELD, then call sched_yield() to swap threads
        if ((opt_yield) & (LOOKUP_YIELD))
            sched_yield();
        //Set search to the next pointer
        search = search->next;
    }
    //Didn't find the element, so return a null pointer
    return NULL;
}

//SortedList_length ... count elements in a sorted list
int SortedList_length(SortedList_t *list) {
    //If list is corrupted, return -1
    if (list == NULL)
        return -1;
    //List does not have a head, so return error
    if (list->key != NULL)
        return -1;
    //Initialize counter to 0
    int len = 0;
    //Set current to point to the first element in the list
    SortedList_t *current = list->next;
    //Traverse through the linked list
    while (current != list){
        /*Check if pointers are corrupted (when the previous pointer of the next 
        elemenent and next pointer of the previous element don't point to the current
        element). If yes, return -1*/
        if ((current->next->prev != current) || (current->prev->next != current))
            return -1;
        //Increment length by 1
        len += 1;
        //If opt yield & LOOKUP_yield != 0, then call the sched_yield() and allow
        //another thread to take over/continue
        if ((opt_yield) & (LOOKUP_YIELD))
            sched_yield();
        //Move to the next element in the list
        current = current->next;
    }
    //Return length
    return len;
}