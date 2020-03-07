#include "test.h"
#include "data.h"
#include <stdio.h>
#include "serialize.h"

int main(){
   printf("ddd\n");
}
void test()
{
   add_to_list(1,0,1);
    add_to_list(1,1,1);    
    add_to_list(2,1,1);    
    add_to_list(3,1,1);
    add_to_list(4,0,0);
    

    struct data_list_struct * d= pop_n_from_list(5);
    destroy_list(d);
   // char ** c = serialize(1,d);
   // deserialize(1,c[1]);
   // printf("%s \n",c[0]);
   // printf("%s \n",c[1]);
}


void t(){
     init_list();

    add_to_list(1,0,1);
    add_to_list(1,1,1);    
    add_to_list(2,1,1);    
    add_to_list(3,1,1);

    int v = get_right_length_list();        
    
    printf("%d \n",v);

    
    print_all_head();

    struct data_list_struct * d= pop_n_from_list(2);
    print_all_head();

    print_all(d);
}