#include "node_t.hpp"
#include <assert.h>

class list
{
    node_t *m_head;
    node_t *m_tail;
    size_t m_size;
    
    public:
    list(): 
        m_head(nullptr), 
        m_tail(nullptr), 
        m_size(0)
    {}
    
    list(int64_t node_val)
    {
        node_t* node = new node_t(node_val);
        m_head = node;
        m_tail = node;
        m_size = 1;
    }
    
    list(const list& other):
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {
        if(other.m_head == nullptr)
            return; 

        m_head = new node_t(other.m_head->value);
        m_tail = m_head;
        m_size = m_size + 1;
        for(node_t *it = other.m_head->next; it != nullptr; it = it->next)
        {
            node_t *node = new node_t(it->value);
            m_tail->next = node;
            m_tail = node;
            m_size = m_size + 1;
        }
        
    }

    ~list();
    list& operator=(const list& other);
    //size	Возвращает количество элементов в списке.(Если предполагаем, что есть поле size)
    size_t size1() const;
    //size	Возвращает количество элементов в списке.(Если предполагаем, что нет поля size)
    size_t size2() const;
    //Проверяет, пуст ли список.
    bool IsEmpty();
    // Добавляет элемент с заданным значением в начало списка.
    void push_front(int64_t node_val);
    //Удаляет элемент в начале списка.
    void pop_front();
    //Добавляет элемент в конец списка.
    void push_back(int64_t node_val);
    //Удаляет элемент в конце списка.
    void pop_back();
    //Вставляет элемент, созданный на месте, в указанное положение в списке.
    void emplace(size_t idx, int64_t node_val);
    //Удаляет все элементы списка.
    void clear();
    friend std::ostream& operator<<(std::ostream& os, const list& other);
};

std::ostream& operator<<(std::ostream& os, const list& other);