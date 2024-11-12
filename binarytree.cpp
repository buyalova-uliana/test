#include "binarytree.h"


//пользовательский конструктор, создает дерево из одеого элемента(вершины)
binary_search_tree_t::binary_search_tree_t(uint64_t root_value)
{
    node_t* root = new node_t(root_value);
}

void binary_search_tree_t::DeleteSubtree(node_t* node)
{
    if(node != nullptr)
    {
        DeleteSubtree(node->left);
        DeleteSubtree(node->right);
        delete node;
    }
}
node_t* binary_search_tree_t::copy_subtree(node_t* node)
{
    if(node != nullptr)
    {
        node_t* tmp = new node_t(node->value);
        tmp->left = copy_subtree(node->left);
        tmp->right = copy_subtree(node->right);
        return tmp;
    }
    return nullptr;
}

binary_search_tree_t::binary_search_tree_t(const binary_search_tree_t& other)
{
    copy_subtree(other.root);
}

// binary_search_tree_t& binary_search_tree_t::operator=(const binary_search_tree_t& other)
// {
//     return ;

// }

void binary_search_tree_t::addElement(uint64_t value)
{
    if(root == nullptr)
    {
        node_t* root = new node_t(value);
    }
    node_t* ptr_cur = root;
    node_t* ptr_prev;
    while(ptr_cur != nullptr)
    {
        ptr_prev = ptr_cur;
        ptr_cur = (ptr_cur->value < value) ? ptr_cur->right : ptr_cur->left;
    }
    node_t* node = new node_t(value);
    ptr_prev = (ptr_prev->value < value) ? ptr_cur->right : ptr_cur->left;
}

void binary_search_tree_t::findElement(uint64_t value)
{
    node_t* ptr = root;
    while(ptr != nullptr)
    {
        if(ptr->value == value)
        {
            std::cout<< "there is such element in the tree" << std::endl;
        }

        ptr = (ptr->value < value) ? ptr->right : ptr->left;
    }
    std::cout<< "there is not such element in the tree" << std::endl;
}

binary_search_tree_t::~binary_search_tree_t()
{
    DeleteSubtree(root);
}

std::ostream& binary_search_tree_t::print_(std::ostream& os, node_t* node) const
{
    if(node != nullptr)
    {
        print_(os, node->left);
        os << node->value;
        print_(os, node->right);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const binary_search_tree_t& obj)
{
    obj.print_(os, obj.root);
    return os;
}

int main()
{
    binary_search_tree_t a;
    binary_search_tree_t b(5);
    std::cout << b;


    return 0;
}