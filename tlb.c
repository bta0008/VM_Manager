/*
 * Project 6: tlb.c
 * Turner Atwood with parts from Xiao Qin.
 */
#include <stdio.h>
#include <limits.h>
#include "system.h"
#include "address.h"
#include "tlb.h"

int tlb_init(tlb_t *tlb) {
    u_int_t i;
 
    for (i = 0; i < TLB_SIZE; i++) {
        tlb_entry_t tlbe = {0, 0, FALSE, 10000};
        tlb->tlb_entry[i] = tlbe;
    }
    tlb->next_tlb_ptr = 0;

    return 0; /* success */
}

int tlb_display(tlb_t tlb) {
    u_int_t i;

    for (i = 0; i < TLB_SIZE; i++) { 
        printf("TLB entry %d, page num: %d, age: %d, frame num: %d, ", i, tlb.tlb_entry[i].page_num, tlb.tlb_entry[i].age, tlb.tlb_entry[i].frame_num);
        if (tlb.tlb_entry[i].valid == FALSE) 
            printf("Invalid\n");
        else printf("Valid\n");
    }

    return 0;
}
/* Search for a page num in the tlb */
int search_tlb(page_t page_num, tlb_t tlb, bool* is_tlb_hit, frame_t* frame_num) {
    u_int_t i;
    *is_tlb_hit = FALSE;
    /* check for page_num in every tlb_entry */
    for (i = 0; i < TLB_SIZE; i++) { 
        tlb_entry_t tlb_entry = tlb.tlb_entry[i];
        if ((tlb_entry.page_num == page_num) && (tlb_entry.valid == TRUE)) {
            *is_tlb_hit = TRUE;
            *frame_num = tlb_entry.frame_num;
        }
    }


    return 0;
}

/* Increases the age of every element in the tlb */
/* Called after replacement occurs */
int tlb_update(page_t page_num, tlb_t* tlb) {
    u_int_t i;
    // Increment the age of every tlb entry
    for (i = 0; i < TLB_SIZE; i++) { 
        if (tlb->tlb_entry[i].page_num == page_num) {
            tlb->tlb_entry[i].age = 0;    
        } 
        tlb->tlb_entry[i].age++;
    }
    return 0;
}

/* Replace the least recently used entry */
int tlb_replacement_LRU(page_t page_num, frame_t frame_num, tlb_t* tlb) {
    u_int_t i;
    int oldest_age = 0;
    int oldest_index = 0;
    tlb_entry_t tlbe;
    // Find the oldest entry
    for (i = 0; i < TLB_SIZE; i++) {
        tlbe = tlb->tlb_entry[i];
        if (tlbe.age > oldest_age) {
            oldest_age = tlbe.age;
            oldest_index = i;
        }
    }

    tlb_entry_t new_tlbe = {page_num, frame_num, TRUE, 0};
    tlb->tlb_entry[oldest_index] = new_tlbe;

    return 0;
}

/* Replace the oldest tlb entry */
int tlb_replacement_FIFO(page_t page_num, frame_t frame_num, tlb_t* tlb) {
    tlb_entry_t new_tlbe = {page_num, frame_num, TRUE, 0};
    tlb->tlb_entry[tlb->next_tlb_ptr] = new_tlbe;
    tlb->next_tlb_ptr = (tlb->next_tlb_ptr+1)%TLB_SIZE;

    return 0;
}
