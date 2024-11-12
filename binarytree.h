#include <iostream>
#include <assert.h>
#include <stdint.h>

struct node_t 
{
    node_t *left;
    node_t *right;

    uint64_t value;

    node_t():left(nullptr), right(nullptr){}
    node_t(uint64_t node_value):left(nullptr), right(nullptr), value(node_value){}
};

class binary_search_tree_t 
{
    node_t* root;

    void DeleteSubtree(node_t* node);
    node_t* copy_subtree(node_t* node);
    std::ostream& print_(std::ostream& os, node_t* node) const;

    public:
    binary_search_tree_t(): root(nullptr){};
    binary_search_tree_t(uint64_t root_value);
    void addElement (uint64_t value);
    void findElement(uint64_t value);

    // По желанию
    // Конструктор копирования, оператор =
    binary_search_tree_t(const binary_search_tree_t& other);
    //binary_search_tree_t& operator=(const binary_search_tree_t& other);
   ~binary_search_tree_t();

   friend std::ostream& operator<<(std::ostream& os, const binary_search_tree_t& obj); 
};
