/*
 * Project 6: tlb.h
 * This is a header file of tlb.c
 * Turner Atwood with parts from Xiao Qin.
 */
#ifndef TLB_H
#define TLB_H

#include "system.h"
#include "address.h"

typedef struct {
    page_t  page_num;
    frame_t frame_num;
    bool    valid;      /* indicate if this entry is valid */
    int age;
}tlb_entry_t;

typedef struct {
    tlb_entry_t tlb_entry[TLB_SIZE]; 
    u_int_t       next_tlb_ptr;  /* next candidate entry to be replaced/used */
}tlb_t;

int tlb_init(tlb_t* tlb);
int tlb_replacement_LRU(page_t page_num, frame_t frame_num, tlb_t* tlb); //NEED  LRU
int tlb_replacement_FIFO(page_t page_num, frame_t frame_num, tlb_t* tlb);
int tlb_display(tlb_t tlb);
int tlb_update(page_t page_num, tlb_t* tlb);
int search_tlb(page_t page_num, tlb_t tlb, bool* is_tlb_hit, frame_t* frame_num);
#endif
