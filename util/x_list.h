/**
 *  Simple doubly-linked list library
 * 
 */

#ifndef __X_LIST_H__
#define __X_LIST_H__

#include "x_types.h"

#define X_LIST_POISON_PREV 0xDEADBEEF
#define X_LIST_POISON_NEXT 0xFADEBABE

struct x_dlist {
    struct x_dlist *next, *prev;  
};

/** Initilize */
#define X_LIST_HEAD_INIT(__lname)   \
    { &(__lname), &(__lname) }

#define X_LIST_HEAD(_lname) \
    struct x_dlist _lname = X_LIST_HEAD_INIT(_lname) 

#define X_INIT_LIST_HEAD    \
    ({  \
        (ptr)->next = ptr;  \
        (ptr)->prev = ptr;  \
    })

/** Helpers for list */
#define x_list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define x_list_first_entry(ptr, type, member)   \
    x_list_entry((ptr)->next, type, member)

//the list is expected to be not empty.
#define x_list_last_entry(ptr, type, member)    \
    x_list_entry((ptr)->prev, type, member)

//Iterate over a list
#define x_list_for_each(pos, head)  \
    for (pos = (head)->next; pos != (head); pos = pos->next)

//Iterate over list of given type
#define x_list_for_each(pos, head, member)  \
    ({  \
        for (pos = x_list_entry((head)->next, typeof(*pos), member);    \
            &pos->member != (head);                                     \
            pos = x_list_entry(pos->member.next, typeof(*pos), member)) \
    })

//checks if the list is empty or not
static inline bool x_list_empty(struct x_dlist *head)
{
    return head->next == head;
}

/** List Operations */
static inline void __x_list_add(struct x_dlist *node,
                                struct x_dlist *prev,
                                struct x_dlist *next)
{
    node->prev = prev; node->next = next;
    prev->next = node; next->prev = node;
}

static inline void __x_list_del(struct x_dlist *prev,
                                struct x_dlist *next)
{
    prev->next = next;
    next->prev = prev;
}

/* list add interface */
static inline void x_list_add_head(struct x_dlist *node,
                            struct x_dlist *head)
{
    __x_list_add(node, head, head->next);
}

static inline void x_list_add_tail(struct x_dlist *node,
                            struct x_dlist *tnode)
{
    __x_list_add(node, tnode->prev, tnode);
}

/* list del interface */
static inline void x_list_del(struct x_dlist *node)
{
    __x_list_del(node->prev, node->next);
    node->next = (void *)X_LIST_POISON_NEXT;
    node->prev = (void *)X_LIST_POISON_PREV; 
}

#endif
