/*
 * Project 5: tlb.c
 * Xiao Qin.
 */
#include <stdio.h>
#include <limits.h>
#include "system.h"
#include "address.h"
#include "tlb.h"
//#define DEBUG

int main ( int argc, char *argv[] ) {
    tlb_t my_tlb; 
    page_t     page_num;
    frame_t    frame_num;

    page_num = 10;
    frame_num = 3;

    tlb_init(&my_tlb);
    tlb_display(my_tlb);
    //tlb_replacement_FIFO(page_num, frame_num, &my_tlb);
    
    return 0;
}

int tlb_init(tlb_t *tlb) {
    u_int_t i;
 
    for (i = 0; i < TLB_SIZE; i++)
        tlb->tlb_entry[i].valid = FALSE;

    return 0; /* success */
}

int tlb_display(tlb_t tlb) {
    u_int_t i;

    for (i = 0; i < TLB_SIZE; i++) { 
        printf("TLB entry %d, page num: %d, frame num: %d, ", i, tlb.tlb_entry[i].page_num, tlb.tlb_entry[i].frame_num);
        if (tlb.tlb_entry[i].valid == FALSE) 
            printf("Invalid\n");
        else printf("Valid\n");
    }

    return 0;
}

int search_tlb(page_t page_num, tlb_t tlb, bool* is_tlb_hit, frame_t* frame_num) {
    u_int_t i;
    bool found = FALSE;
    /* check for page_num in every tlb_entry */
    for (i = 0; i < TLB_SIZE; i++) { 
        printf("TLB entry %d, page num: %d, frame num: %d, ", i, tlb.tlb_entry[i].page_num, tlb.tlb_entry[i].frame_num);
        tlb_entry_t tlb_entry = tlb.tlb_entry[i];
        if (tlb_entry.page_num == page_num && tlb_entry.valid == FALSE) {
            found = TRUE;
            *frame_num = tlb_entry.frame_num;
        }
    }

    *is_tlb_hit = found;
    return 0;
}


