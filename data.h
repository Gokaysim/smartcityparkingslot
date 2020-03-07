#pragma once
struct data_list_struct {
    int nodeId;
    int isEmpty;
    // 1 for right
    // -1 for left
    // 0 for both sides
    int emptyDataSentDirection;
    struct data_list_struct *next;
}data_list_struct;


void init_list();
void add_to_list(int nodeId,int isEmpty,int emptyDataSentDirection);
void add_to_top_of_list(int nodeId,int isEmpty,int emptyDataSentDirection);
struct data_list_struct * pop_n_from_list(int n);
int get_left_length_list(); 
int get_right_length_list(); 

void print_all(struct data_list_struct * listOfHeader);

void print_all_head();

void destroy_list(struct data_list_struct * listOfHeader);