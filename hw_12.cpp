#include <iostream>
#include <stdint.h>
#include <cmath>
#include <assert.h>

// хотела сделать class, но не получилось, полезли конфликты
struct node_t
{
    node_t *next;
    node_t *prev;
    int64_t value;
    
    //public:
    //конструктор по умолчанию, value вообще не хотелось бы инициализировать в этом случае. Так можно?
    node_t():next(nullptr), prev(nullptr){}
    //пользовательский конструктор (создает узел с заданным значением node_val)
    node_t(int64_t new_value): next(nullptr), prev(nullptr), value(new_value){}
    //конструктор копирования
    node_t(const node_t& other)
    {
        //надо подумать, когда в этой комбинации есть nullptr
        assert((next == other.next) && (prev != other.prev));
        assert((next != other.next) && (prev == other.prev));//в предыдущих двух случаях что-то пошло не так
        if(next == other.next && prev == other.prev)// этот случай считаем самокопированием
        {
            return;
        }
        value = other.value;
    }
    //надо ли тут что-то делать? И можно ли вообще убрать деструктор?
    ~node_t(){}
    
    friend class list;
    //friend std::ostream& operator<<(std::ostream& os, const list& other);
};


class list
{
    node_t *head;
    node_t *tail;
    size_t size;
    
    public:

    //конструктор по умолчанию(нет элементов в списке)
    list(): head(nullptr), tail(nullptr), size(0){}
    //создаем список из одного элемента с заданным значением узла
    list(int64_t node_val)
    {
        //node_t node(node_val); //  next(nullptr), prev(nullptr), value(new_value)
        node_t* node = new node_t(node_val);
        head = node;
        tail = node;
        size = 1;
    }
    //конструктор копирования
    list(const list& other)
    {
        node_t* ptr_other = other.head;
        size = 0;// пока проще обнулит и посчитать заново
        head = nullptr;
        if(ptr_other == nullptr)
        {
            tail = nullptr;
            return;
        }
        node_t* tmp;
        while(ptr_other != nullptr)
        {
            ++size;
            node_t* node = new node_t(ptr_other->value);
            if(ptr_other == other.head)
            {
                head = node;
                tmp = head;
                tail = head;
                ptr_other = ptr_other->next;
                continue;
            }
            node->prev = tmp;
            tmp->next = node;
            tmp = tmp->next;

            ptr_other = ptr_other->next;
        }
        tail = tmp;
    }
    //operator=	Заменяет элементы списка копией другого списка.
    list& operator=(const list& other)
    {
        //проверка на самоприсваивание
        //можно так проверить? Если да, то не очень понимаю, почему это будет работать.
        if(this == &other)
        {
            return *this;
        }
        if((head == nullptr) && (other.head == nullptr))
        {
            assert(tail == nullptr);
            assert(size == 0);
            assert(other.tail == nullptr);
            assert(other.size == 0);
            return *this;
        }
        node_t* tmp = head;
        node_t* ptr_this = head;
        node_t* ptr_other = other.head;
        size = 0;// пока проще обнулит и посчитать заново
        //делаем этот цикл, чтобы не перевыделять память(если равно nullptr, значит дошли до хвоста)
        while((ptr_this!= nullptr) && (ptr_other != nullptr))
        {
            ++size;
            if(ptr_this == head)
            {
                assert(ptr_this->prev == nullptr);
                ptr_this->value = ptr_other->value;
                ptr_this = ptr_this->next;
                ptr_other = ptr_other->next;
                continue;
            }
            ptr_this->value = ptr_other->value;
            //по идее с указателями и так все должно быть нормально, не знаю, стоит ли это делать или поставить assert
            ptr_this->prev = tmp;
            tmp->next = ptr_this;
            tmp = tmp->next;
            ptr_this = ptr_this->next;

            ptr_other = ptr_other->next;
        }
        // надо идти до конца списка other и выделять память
        if((ptr_this == nullptr) && (ptr_other != nullptr))
        {
            while(ptr_other != nullptr)
            {
                ++size;
                //node node(ptr_other->value);
                node_t* node = new node_t(ptr_other->value);
                if(ptr_this == head)
                {
                    head = node;
                    tmp = node;
                    ptr_other = ptr_other->next;
                    continue;
                }
                node->prev = tmp;
                tmp->next = node;
                tmp = tmp->next;

                ptr_other = ptr_other->next;
            }
        }
        tail = tmp;
        //а тут надо удалить все ненужные элементы
        if((ptr_this != nullptr) && (ptr_other == nullptr))
        {
            while(ptr_this != nullptr)
            {
                ptr_this = ptr_this->next;
                delete tmp;
                tmp = ptr_this;
            }    
        }
        return *this;
    }
    
    //size	Возвращает количество элементов в списке.(Если предполагаем, что есть поле size)
    size_t Size1()
    {
        return size; 
    }

    //size	Возвращает количество элементов в списке.(Если предполагаем, что нет поля size)
    size_t Size2()
    {
        node_t* tmp = head;
        size_t cur_size = 0; 
        while(tmp != nullptr)
        {  
            tmp = tmp->next;
            ++cur_size;
        }
        return cur_size;
    }

    //Проверяет, пуст ли список.
    bool IsEmpty()
    {
        if(head == nullptr)
        {
            assert(tail == nullptr);
            return true;
        }
        return false;
    }

    // Добавляет элемент с заданным значением в начало списка.
    void push_front(int64_t node_val)
    {
        if(IsEmpty())
        {
            //node node(node_val);//next(nullptr), prev(nullptr), value(node_val)
            node_t* node = new node_t(node_val);
            head = node;
            tail = node;
            size = 1;
            return;
        }
        ++size;
        //node node(node_val); //next(nullptr), prev(nullptr), value(node_val)
        node_t* node = new node_t(node_val);
        node->next = head;
        head->prev = node;
        head = node;
    }

    //Удаляет элемент в начале списка.
    void pop_front()
    {
        if(IsEmpty())
        {
            return;
        }
        node_t* tmp = head;
        //случай, когда в списке один элемент
        if(head == tail)
        {
            head = tail = nullptr;
            size = 0;
            delete tmp;
            return;
        }
        --size;
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    }
    //Добавляет элемент в конец списка.
    void push_back(int64_t node_val)
    {
        if(IsEmpty())
        {
            node_t* node = new node_t(node_val);
            head = node;
            tail = node;
            size = 1;
            return;
        }
        ++size;
        node_t* node = new node_t(node_val);
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    //Удаляет элемент в конце списка.
    void pop_back()
    {
        if(IsEmpty())
        {
            return;
        }
        node_t* tmp = tail;
        //случай, когда в списке один элемент
        if(head == tail)
        {
            head = tail = nullptr;
            size = 0;
            delete tmp;
            return;
        }
        --size;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    }
    //Вставляет элемент, созданный на месте, в указанное положение в списке.
    void emplace(size_t idx, int64_t node_val)
    {
        //тут вопрос, что делать, если длина списка меньше, чем заданный индекс? Пока будет assert
        assert(idx <= size);//если =size, то просто поставим на последнее место
        if(idx == 0)
        {
            push_front(node_val);
            return;
        }
        if(idx == size)
        {
            push_back(node_val);
            return;
        }
        ++size;
        node_t* node = new node_t(node_val);
        node_t* tmp = head;
        for(size_t i = 0; i < idx; ++i)
        {
            tmp = tmp->next;
        }
        node->next = tmp;
        node->prev = tmp->prev;
        tmp->prev->next = node;
        tmp->prev = node; 
    }
    
    //Удаляет все элементы списка.
    void clear()
    {
        if(IsEmpty())
        {
            return;
        }
        node_t* tmp = head;
        node_t* ptr = head;
        while(ptr != nullptr)
        {
            //--size;
            ptr = ptr->next;
            delete tmp;
            tmp = ptr;
        }
        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    
   ~list()
    {
        node_t* tmp = head;
        node_t* ptr_this = head;
        while(ptr_this != nullptr)
        {
            ptr_this = ptr_this->next;
            delete tmp;
            tmp = ptr_this;
        }    
    }

    friend std::ostream& operator<<(std::ostream& os, const list& other);
};

std::ostream& operator<<(std::ostream& os, const list& other)
{
    os << "list size:" << other.size << std::endl;
    for(node_t* p = other.head; p != nullptr; )
    {
        os << p->value << " ";
        p = p->next;
    }
    os << std::endl;
    return os;
}

int main()
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

    return 0;
}