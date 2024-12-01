#include <iostream>
#include <assert.h>
#include <stdint.h>

struct node_t 
{
    node_t *m_left;
    node_t *m_right;

    uint64_t m_value;

    node_t():m_left(nullptr), m_right(nullptr){}
    node_t(uint64_t node_value):m_left(nullptr), m_right(nullptr), m_value(node_value){}
};

class binary_search_tree_t 
{
    node_t* m_root;

    void DeleteSubtree(node_t* node);
    node_t* CopySubtree(node_t* node);
    //можно ли функции swap передать binary_search_tree_t& tree_1, binary_search_tree_t& tree_2? Можно ли 
    // передавать ссылки, а потом менять местами поля объектов, которые являются указателями.
    void swap(node_t* m_root, node_t* m_root_other);
    std::ostream& print_(std::ostream& os, node_t* node, int space) const;

    public:
    binary_search_tree_t(): m_root(nullptr){};
    binary_search_tree_t(uint64_t root_value);
    binary_search_tree_t(const binary_search_tree_t& other);
    binary_search_tree_t& operator=(const binary_search_tree_t& other);
   ~binary_search_tree_t();

    void addElement (uint64_t value);
    void findElement(uint64_t value);

   friend std::ostream& operator<<(std::ostream& os, const binary_search_tree_t& obj); 
};
