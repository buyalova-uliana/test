#include <iostream>
#include <cstdint>
#include <cmath>
#include <assert.h>

struct node_t
{
    node_t *next;
    node_t *prev;
    int64_t value;
    
    node_t():
        next(nullptr), 
        prev(nullptr)
    {}
    
    node_t(int64_t new_value): 
        next(nullptr), 
        prev(nullptr), 
        value(new_value)
    {}
    
    node_t(const node_t& other):
        value(other.value)
    {}

    ~node_t(){}
};
