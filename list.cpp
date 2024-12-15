#include "list.hpp"

list::~list()
{
    node_t* tmp = m_head;
    node_t* ptr_this = m_head;
    while(ptr_this != nullptr)
    {
        ptr_this = ptr_this->next;
        delete tmp;
        tmp = ptr_this;
    }    
}

list& list::operator=(const list& other)
{
    if(this == &other)
    {
        return *this;
    }
    if((m_head == nullptr) && (other.m_head == nullptr))
    {
        return *this;
    }
    node_t* ptr_this = m_head;
    node_t* ptr_other = other.m_head;

    while((ptr_this != nullptr) && 
        (ptr_other != nullptr))
    {
        ptr_this->value = ptr_other->value;
        
        ptr_this = ptr_this->next;
        ptr_other = ptr_other->next;
    }
    //размеры совпали
    if((ptr_other == nullptr) &&
        (ptr_this == nullptr))
        return *this;
    
    //текущий список больше чем копируемый
    if(ptr_other == nullptr)
    {
        m_size = other.size1();
        m_tail = ptr_this->prev;
        if(m_tail != nullptr)
            m_tail->next = nullptr;
        else
            m_tail = m_head;

        while(ptr_this != nullptr)
        {
            node_t *tmp = ptr_this;
            ptr_this = ptr_this->next;
            
            delete tmp;
        }    
    }   
    // копируемый список больше
    else
    {
        if(IsEmpty())
        {
            m_head = new node_t(ptr_other->value);
            m_tail = m_head;
            m_size = m_size + 1;
            
            ptr_other = ptr_other->next;
        }
        for(; ptr_other != nullptr; ptr_other = ptr_other->next)
        {
            node_t* node = new node_t(ptr_other->value);
            m_tail->next = node;
            m_tail = node;
            m_size = m_size + 1;
        }
    }
    return *this;
}

//size	Возвращает количество элементов в списке.(Если предполагаем, что есть поле size)
size_t list::size1() const
{
    return m_size; 
}

//size	Возвращает количество элементов в списке.(Если предполагаем, что нет поля size)
size_t list::size2() const
{
    node_t* tmp = m_head;
    size_t size = 0; 
    while(tmp != nullptr)
    {  
        tmp = tmp->next;
        ++size;
    }
    return size;
}

//Проверяет, пуст ли список.
bool list::IsEmpty()
{
    if(m_head == nullptr)
    {
        assert(m_tail == nullptr);
        return true;
    }
    return false;
}

// Добавляет элемент с заданным значением в начало списка.
void list::push_front(int64_t node_val)
{
    if(IsEmpty())
    {
        node_t* node = new node_t(node_val);
        m_head = node;
        m_tail = node;
        m_size = 1;
        return;
    }
    
    node_t* node = new node_t(node_val);
    node->next = m_head;
    m_head->prev = node;
    m_head = node;

    m_size = m_size + 1;
}

//Удаляет элемент в начале списка.
void list::pop_front()
{
    if(IsEmpty())
    {
        throw "pop_front function is called for empty list";
        return;
    }
    //случай, когда в списке один элемент
    if(m_head == m_tail)
    {
        delete m_head;
        m_head = m_tail = nullptr;
        m_size = 0;
        return;
    }
    node_t* tmp = m_head;

    m_head = m_head->next;
    m_head->prev = nullptr;
    delete tmp;
    m_size = m_size - 1;
}

//Добавляет элемент в конец списка.
void list::push_back(int64_t node_val)
{
    if(IsEmpty())
    {
        node_t* node = new node_t(node_val);
        m_head = node;
        m_tail = node;
        m_size = 1;
        return;
    }
    node_t* node = new node_t(node_val);
    m_tail->next = node;
    node->prev = m_tail;
    m_tail = node;
    
    m_size = m_size + 1;
}

//Удаляет элемент в конце списка.
void list::pop_back()
{
    if(IsEmpty())
    {
        throw "pop_front function is called for empty list";
        return;
    }
    //случай, когда в списке один элемент
    if(m_head == m_tail)
    {
        delete m_head;

        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
        return;
    }
    node_t* tmp = m_tail;
    m_tail = m_tail->prev;
    m_tail->next = nullptr;
    delete tmp;
    m_size = m_size - 1;
}

//Вставляет элемент, созданный на месте, в указанное положение в списке.
void list::emplace(size_t idx, int64_t node_val)
{
    //тут вопрос, что делать, если длина списка меньше, чем заданный индекс? Пока будет assert
    assert(idx <= m_size);//если =size, то просто поставим на последнее место
    if(idx > m_size)
        throw "The emplace function was called on an index that is outside the bounds of the list";
    if(idx == 0)
    {
        push_front(node_val);
        return;
    }
    if(idx == m_size)
    {
        push_back(node_val);
        return;
    }

    node_t* tmp = m_head;
    for(size_t i = 0; i < idx; ++i)
    {
        tmp = tmp->next;
    }
    node_t* node = new node_t(node_val);
    node->next = tmp;
    node->prev = tmp->prev;
    tmp->prev->next = node;
    tmp->prev = node; 
    m_size = m_size + 1;
}

//Удаляет все элементы списка.
void list::clear()
{
    if(IsEmpty())
    {
        return;
    }
    node_t* tmp = m_head;
    node_t* ptr = m_head;
    while(ptr != nullptr)
    {
        ptr = ptr->next;
        delete tmp;
        tmp = ptr;
    }
    m_head = nullptr;
    m_tail = nullptr;
    
    m_size = 0;
}

std::ostream& operator<<(std::ostream& os, const list& other)
{
    os << "list size:" << other.m_size << std::endl;
    for(node_t* p = other.m_head; p != nullptr; )
    {
        os << p->value << " ";
        p = p->next;
    }
    os << std::endl;
    return os;
}

int main()
{
    try
    {
        list a;
        list c(a);
        std::cout << c;
        std::cout << std::endl;

        list b(5);
        std::cout << b;
        std::cout << std::endl;
        for(int i = 0; i < 6; ++i)
        {
            b.push_front(i);
        }
        std::cout << b;
        std::cout << std::endl;

        list d(b);
        std::cout << d;
        std::cout << std::endl;

        // std::cout<< d.Size1() << std::endl;
        // std::cout<< d.Size2() << std::endl;

        // std::cout<< c.Size1() << std::endl;
        // std::cout<< c.Size2() << std::endl;

        // std::cout << "IsEmpty" << std::endl;
        // std::cout<< d.IsEmpty() << std::endl;
        // std::cout<< c.IsEmpty() << std::endl;

        // std::cout << "operator= " << std::endl;
        // c = a;
        // std::cout << c;
        // std::cout << std::endl;
        // a = d;
        // std::cout << a;
        // std::cout << std::endl;
        // std::cout << d;
        // std::cout << std::endl;
        d.pop_front();
        d.pop_front();
        d.pop_front();
        d.pop_front();
        d.pop_front();
        d.pop_front();
        std::cout << d;
        std::cout << std::endl;
        d.pop_front();
        d.pop_front();
        std::cout << d;
        std::cout << std::endl;

        for(int i = 0; i < 8; ++i)
        {
            d.push_back(i);
        }
        std::cout << d;
        std::cout << std::endl;

        d.pop_back();
        std::cout << d;
        std::cout << std::endl;

        d.emplace(1, 10);
        std::cout << d;
        std::cout << std::endl;

        d.emplace(3, 10);
        std::cout << d;
        std::cout << std::endl;

        d.emplace(9, 10);
        std::cout << d;
        std::cout << std::endl;

        // for(int i = 0; i < 7; ++i)
        // {
        //     d.pop_back();
        // }
        // std::cout << d;
        // std::cout << std::endl;

        // d.pop_back();
        // std::cout << d;
        // std::cout << std::endl;

        // d.clear();
        // std::cout << d;
        // std::cout << std::endl;

        // d.clear();
        // std::cout << d;
        // std::cout << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what();
    }
    catch(...)
    {
        std::cerr << "Something went wrong";
    }
    return 0;
}