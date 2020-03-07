#pragma once
#include "data.h"


char** serialize(int nodeId, struct data_list_struct * data);

struct data_list_struct *  deserialize(int nodeId,char * str);