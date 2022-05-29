#include "iostream"
template <class T>
struct Node{
    T m_data;
    Node* m_nextNode;
};

template <class T>
class Queue
{
private:
    Node <T> *m_firstNode;
    Node <T> *m_lastNode;
    int m_size;
public:
    //no arguments c'tor
    Queue();

    //copy c'tor
    Queue(const Queue&);

    //assign right operand to left operand
    Queue<T>& operator=(const Queue<T>&);
    
    //d'tor
    ~Queue();

    //push object t to the tale of the queue
    void pushBack(const T t);

    //return the front element of the queue
    T& front() const;

    //pop out the front element of the queue,
    //(but not retuurning him)
    void popFront();

    //return how much elements in the queue
    int size() const;
    
    //iterator for non-const queues
    //(can change the data)
    class Iterator;
    
    //iterator for const queue objects
    //cannot change data
    class ConstIterator;

    //return Iterator that points the first element
    Iterator begin() ;
    
    //return Iterator that points to nullptr
    Iterator end() ;

    //return const Iterator that points the first element
    ConstIterator begin() const;

    //return const Iterator that points to nullptr
    ConstIterator end() const;
    
    //exeption for illegal function on empty queue
    //(popFront or front)
    class EmptyQueue{};
    
};
template <class T, class Condition>
Queue<T> filter(const Queue<T> queue,Condition c);

template <class T, class Transformation>
void transform(Queue<T>& queue,Transformation t);

template <class T>
Queue<T>::Queue():
m_firstNode(new Node <T>),
m_lastNode(nullptr),
m_size(0)
{
    try
    {
        m_firstNode->m_nextNode=nullptr;
        m_lastNode=m_firstNode;
    }
    catch(std::exception&)
    {
        delete m_firstNode;
        throw;
    }
}

template <class T>
Queue<T>::Queue(const Queue<T>& queue):
m_firstNode(new Node <T>),
m_lastNode(nullptr),
m_size(0)
{
    try
    {
           m_firstNode->m_nextNode=nullptr;
        m_lastNode=m_firstNode;
        for(T element: queue)
        {
            (*this).pushBack(element);
        }
    }
    catch(std::exception&)
    {
        delete m_firstNode;
        throw;
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
    if(this==&queue)
    {
        return *this;
    }
    Node<T> *previousNode=m_firstNode;
    Node<T> *nextNode=m_firstNode;
    while(nextNode)
    {
        nextNode=previousNode->m_nextNode;
        delete previousNode;
        previousNode=nextNode;
    }
    m_firstNode=new Node<T>;
    m_lastNode=nullptr;
    m_size=0;
    m_firstNode->m_nextNode=m_lastNode;
    m_lastNode=m_firstNode;
    for(T element: queue)
    {
        this->pushBack(element);
    }
    return *this;
}

template <class T>
Queue<T>::~Queue()
{
    Node<T> *previousNode=m_firstNode;
    Node<T> *nextNode=m_firstNode;
    while(nextNode)
    {
        nextNode=previousNode->m_nextNode;
        delete previousNode;
        previousNode=nextNode;
    }
}

template <class T>
void Queue<T>::pushBack(const T t)
{
    if(m_size==0)
    {
        m_firstNode->m_data=T(t);
    }
    else 
    {   
        Node<T> *newLastNode = new Node<T>;
        m_lastNode->m_nextNode=newLastNode;
        m_lastNode=newLastNode;
        newLastNode->m_nextNode=nullptr;
        m_lastNode->m_data=T(t);
    }
    m_size++;
}

template <class T>
T& Queue<T>::front() const
{
    if(m_size>0)
    {
        return m_firstNode->m_data;
    }
    else
    {
        throw EmptyQueue();
    }
}

template <class T>
void Queue<T>::popFront()
{
    if(m_size>0)
    {
        if(m_size>1)
        {
            Node<T> *tmpNode=m_firstNode;
            m_firstNode=m_firstNode->m_nextNode;
            delete tmpNode;
        }
        m_size--;
        return;
    }
    throw EmptyQueue();
}

template <class T>
int Queue<T>::size() const
{
    return m_size;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() 
{
    if(this->m_size==0)
    {    
        return (*this).end();
    }
    return Iterator (this,m_firstNode);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() 
{
    return Iterator (this,m_lastNode->m_nextNode);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    if(this->m_size==0)
    {    
        return (*this).end();
    }
    return ConstIterator (this,m_firstNode);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end () const 
{
    return ConstIterator (this,m_lastNode->m_nextNode);
}

template <class T,class Condition>
Queue<T> filter(const Queue<T> queue,Condition c)
{
    Queue<T> result;
    for (T element:queue)
    {
        if(c(element))
        {
            result.pushBack(element);
        }
    }
    return result;
}

template <class T>
class Queue<T>::Iterator
{
    Queue<T> *m_queue;
    Node<T> *m_currentNode;
    Iterator(Queue<T>* queue, Node<T> *currentNode);
    friend class Queue<T>;
public:
    //~Iterator();
    Iterator& operator++();
    Iterator operator++(int);
    T& operator*() const; 
    bool operator!=(const Iterator& iterator) const;
    bool operator==(const Iterator& iterator) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default; 
    class InvalidOperation{};
};

template <class T,class Transformation> 
void transform(Queue<T>& queue,Transformation t)
{
    for (typename Queue<T>::Iterator i = queue.begin(); i!=queue.end(); i++) 
    {    
        t(*i);
    }
}

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, Node<T> *currentNode) :
m_queue(queue), 
m_currentNode(currentNode)
{}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    m_currentNode=m_currentNode->m_nextNode;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    Iterator result = *this;
    ++(*this);
    return result;
}

template<class T>
T& Queue<T>::Iterator::operator*() const
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return this->m_currentNode!=iterator.m_currentNode;
    }
    throw InvalidOperation();
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return !(*this!=iterator);
    }
    throw InvalidOperation();
}

template <class T>
class Queue<T>::ConstIterator
{
    const Queue<T> *m_queue;
    Node<T> *m_currentNode;
    ConstIterator(const Queue<T>* queue, Node<T> *currentNode);
    friend class Queue<T>;
public:
    //~Iterator();
    ConstIterator& operator++();
    ConstIterator operator++(int);
    const T& operator*() const; 
    bool operator!=(const ConstIterator& iterator) const;
    bool operator==(const ConstIterator& iterator) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default; 
    class InvalidOperation{};
};

template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, Node<T> *currentNode) :
m_queue(queue), 
m_currentNode(currentNode)
{}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    m_currentNode=m_currentNode->m_nextNode;
    return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    Iterator result = *this;
    ++(*this);
    return result;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if(*this==this->m_queue->end())
    {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return this->m_currentNode!=iterator.m_currentNode;
    }
    throw InvalidOperation();
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return !(*this!=iterator);
    }
    throw InvalidOperation();
}
