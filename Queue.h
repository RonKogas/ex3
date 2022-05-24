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
    Queue();
    Queue(const Queue&);
    Queue<T>& operator=(const Queue<T>&);
    ~Queue();
    void pushback(const T t);
    T& front() const;
    void popFront();
    int size() const;
    class Iterator;
    class constIterator;
    Iterator begin() ;
    Iterator end() ;
    constIterator begin() const;
    constIterator end() const;
    
};
template <class T, class Condition>
Queue<T> filter(const Queue<T> queue,Condition c);

template <class T, class Transformation>
void transform(Queue<T> queue,Transformation t);

template <class T>
Queue<T>::Queue():
m_firstNode(new Node <T>),
m_lastNode(nullptr),
m_size(0)
{
    m_firstNode->m_nextNode=nullptr;
    m_lastNode=m_firstNode;
}

template <class T>
Queue<T>::Queue(const Queue<T>& queue):
m_firstNode(new Node <T>),
m_lastNode(nullptr),
m_size(0)
{
    m_firstNode->m_nextNode=nullptr;
    m_lastNode=m_firstNode;
    for(T element: queue)
    {
        (*this).pushback(element);
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
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
        this->pushback(element);
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
void Queue<T>::pushback(const T t)
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
        return m_firstNode->m_data;// must be changed
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
    }
}

template <class T>
int Queue<T>::size() const
{
    return m_size;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() 
{
    return Iterator (this,m_firstNode);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() 
{
    return Iterator (this,m_lastNode->m_nextNode);
}

template <class T>
typename Queue<T>::constIterator Queue<T>::begin() const
{
    return constIterator (this,m_firstNode);
}

template <class T>
typename Queue<T>::constIterator Queue<T>::end () const 
{
    return constIterator (this,m_lastNode->m_nextNode);
}

template <class T,class Condition>
Queue<T> filter(const Queue<T> queue,Condition c)
{
    Queue<T> result;
    for (T element:queue)
    {
        if(c(element))
        {
            result.pushback(element);
        }
    }
    return result;
}

template <class T,class Transformation>
void transform(Queue<T> queue,Transformation t)
{
    for (T& element: queue) 
    {    
        element=t(element);
    }
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
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default; 
};

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, Node<T> *currentNode) :
m_queue(queue), 
m_currentNode(currentNode)
{}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    m_currentNode=m_currentNode->m_nextNode;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    ++this;
    return result;
}

template<class T>
T& Queue<T>::Iterator::operator*() const
{
    return m_currentNode->m_data;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return this->m_currentNode!=iterator.m_currentNode;
    }
    return false;
}

template <class T>
class Queue<T>::constIterator
{
    const Queue<T> *m_queue;
    Node<T> *m_currentNode;
    constIterator(const Queue<T>* queue, Node<T> *currentNode);
    friend class Queue<T>;
public:
    //~Iterator();
    constIterator& operator++();
    constIterator operator++(int);
    const T& operator*() const; 
    bool operator!=(const constIterator& iterator) const;
    constIterator(const constIterator&) = default;
    constIterator& operator=(const constIterator&) = default; 
};

template<class T>
Queue<T>::constIterator::constIterator(const Queue<T>* queue, Node<T> *currentNode) :
m_queue(queue), 
m_currentNode(currentNode)
{}

template<class T>
typename Queue<T>::constIterator& Queue<T>::constIterator::operator++()
{
    m_currentNode=m_currentNode->m_nextNode;
    return *this;
}

template<class T>
typename Queue<T>::constIterator Queue<T>::constIterator::operator++(int)
{
    Iterator result = *this;
    ++this;
    return result;
}

template<class T>
const T& Queue<T>::constIterator::operator*() const
{
    return m_currentNode->m_data;
}

template<class T>
bool Queue<T>::constIterator::operator!=(const constIterator& iterator) const
{
    if(this->m_queue==iterator.m_queue)
    {
        return this->m_currentNode!=iterator.m_currentNode;
    }
    return false;
}
