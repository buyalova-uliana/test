#include "binarytree.h"
#define COUNT 1

//пользовательский конструктор, создает дерево из одеого элемента(вершины)
binary_search_tree_t::binary_search_tree_t(uint64_t root_value)
{
    m_root = new node_t(root_value);
}

void binary_search_tree_t::DeleteSubtree(node_t* node)
{
    if(node != nullptr)
    {
        DeleteSubtree(node->m_left);
        DeleteSubtree(node->m_right);
        delete node;
    }
}
node_t* binary_search_tree_t::CopySubtree(node_t* node)
{
    if(node != nullptr)
    {
        node_t* m_node = new node_t(node->m_value);
        m_node->m_left = CopySubtree(node->m_left);
        m_node->m_right = CopySubtree(node->m_right);
        return m_node;
    }
    return nullptr;
}

void binary_search_tree_t::BinarySubtreesComparison(node_t* node, node_t* other_node)
{ 
    if(true)
    {

    }
    return;
}

binary_search_tree_t::binary_search_tree_t(const binary_search_tree_t& other)
{
    CopySubtree(other.m_root);
}

binary_search_tree_t& binary_search_tree_t::operator=(const binary_search_tree_t& other)
{
    if(this == &other)
    {
        return *this;
    }
}

void binary_search_tree_t::addElement(uint64_t value)
{
    if(m_root == nullptr)
    {
        node_t* m_root = new node_t(value);
    }
    node_t* ptr_cur = m_root;
    node_t* ptr_prev;
    while(ptr_cur != nullptr)
    {
        ptr_prev = ptr_cur;
        ptr_cur = (ptr_cur->m_value <= value) ? ptr_cur->m_right : ptr_cur->m_left;
    }
    node_t* node = new node_t(value);
    (ptr_prev->m_value <= value) ? (ptr_prev->m_right = node) : (ptr_prev->m_left = node);
}

void binary_search_tree_t::findElement(uint64_t value)
{
    node_t* ptr = m_root;
    while(ptr != nullptr)
    {
        if(ptr->m_value == value)
        {
            std::cout<< "there is such element in the tree" << std::endl;
            return;
        }

        ptr = (ptr->m_value <= value) ? ptr->m_right : ptr->m_left;
    }
    std::cout<< "there is not such element in the tree" << std::endl;
    return;
}

binary_search_tree_t::~binary_search_tree_t()
{
    DeleteSubtree(m_root);
}

std::ostream& binary_search_tree_t::print_(std::ostream& os, node_t* node, int space) const
{
    // Base case
    if (node == nullptr)
        return os;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print_(os, node->m_right, space);
 
    // Print current node after space
    // count
    os << std::endl;
    for (int i = COUNT; i < space; i++)
        os << " ";
    os << node->m_value << "\n";
 
    // Process left child
    print_(os, node->m_left, space);
    return os;
}

std::ostream& operator<<(std::ostream& os, const binary_search_tree_t& obj)
{
    obj.print_(os, obj.m_root, 0);
    return os;
}


int main()
{
    binary_search_tree_t a;
    binary_search_tree_t b(5);
    for(uint64_t i = 0; i < 10; ++i)
    {
        b.addElement(i);
    }

    std::cout << b;
    a.addElement(10);
    std::cout << a;

    for(uint64_t i = 0; i < 10; ++i)
    {
        b.findElement(i);
    }
    b.findElement(15);
    b.findElement(100);


    return 0;
}