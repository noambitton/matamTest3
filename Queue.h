//
// Created by mayan on 27-May-22.
//

#ifndef HEALTHPOINTS_H_QUEUE_H
#define HEALTHPOINTS_H_QUEUE_H

#include <new>
#include <iostream>


template <class T>
class Queue
{
public:
    struct Node
    {
        T value;
        Node *next;
//
//        /**
//         * C'tor of Node
//         */
//        Node() : value(NULL), next(nullptr)
//        {};
//
//        /**
//         * C'tor of Node
//         */
//        explicit Node(T value) : value(value), next(nullptr)
//        {};
//
//        /**
//         * Copy C'tor of Node
//         * @param value of the element
//         */
//        Node(const Node& other) = default;
//
//        /**
//         * D'tor of Node
//         */
//        ~Node() = default;
//
//        /**
//         * Assignment operator of struct Node.
//         */
//        Node& operator=(const Node& other) = default;
    };
    /**
     * C'tor of Queue
     */
    Queue();

    /**
     * copy C'tor of Queue
     */
    Queue(const Queue&);

    /**
     * D'tor of Queue
     */
    ~Queue();

    /**
     * Assignment operator of Queue
     * @return reference to updated instance of the class
     */
    Queue& operator=(const Queue& other);

    /**
     * Add new copy of the element to the end of the Queue
     * @param element element to be added
     */
    void pushBack(const T& element);

    /**
     * The function return the first element in the non-const queue
     * @return reference to the first element (in the non-const queue)
     */
    T& front();

    /**
     * The function return the first element in the constant queue
     * @return const reference to the first element (in the constant queue)
     */
    const T& front() const;

    /**
     * The function remove the first element in the Queue
     */
    void popFront();

    /**
     * The function returns the size of the Queue
     * @return the size of the Queue
     */
    int size() const;

    // exception
    class EmptyQueue{};

    /**
     * Iterator for a non - const Queue instance.
     */
    class Iterator;
    /**
     * returns the pointer to the first element in the (non-const) queue
     */
    Iterator begin();
    /**
     * returns the pointer to the last element in the (non-const) queue
     */
    Iterator end();

    /**
     * Iterator for a const instance of Queue.
     */
    class ConstIterator;

    /**
     * returns the pointer to the first element in the constant queue
     */
    ConstIterator begin() const;
    /**
     * returns the pointer to the last element in the constant queue
     */
    ConstIterator end() const;

private:
    Node *m_firstElement;
    Node *m_lastElement;

    /**
    * The function check if there are no left elements in the queue
    * @return true if the there are no left elements in the queue, otherwise returns false.
    */
    bool isEmpty() const;
};

/**
 * The functions filter create and return a new Queue contains only the elements that correspond to the
 * condition of the given Condition function.
 * @tparam T class of the elements
 * @tparam Condition class of function object or pointer to a function
 * @param queue queue to be filtered
 * @param condition function object or pointer to a function that receives element and returns a
 * boolean value
 * @return
 */
/** The non - const verse of filter function */
template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition condition);

/**
 * The function goes over the elements of a queue and changes them one by one according to a given operation
 * @tparam T class of the elements
 * @tparam Condition class of function object or pointer to a function
 * @param queue Queue to be transformed
 * @param operation function object or pointer to a function that receives an element and changes it
 * @return
 */
template <class T, class Operation>
void transform(Queue<T>& queue, Operation operation/*******void (*operation)(T&)*/);


template <class T>
Queue<T>::Queue() : m_firstElement(nullptr), m_lastElement(nullptr) {}

template <class T>
Queue<T>::Queue(const Queue& other)
{
    m_firstElement = nullptr;
    m_lastElement = nullptr;

    for (typename Queue<T>::ConstIterator iterator = other.begin();
         iterator != other.end(); ++iterator) {
        pushBack(*iterator);
//        if((!(currentNode!=other.begin())) && m_firstElement == nullptr){
//            m_firstElement->value = *currentNode;
//            m_lastElement = m_firstElement;
//        }
    }
}

template <class T>
Queue<T>::~Queue()
{
    Node *toDelete = m_firstElement;
    while(!isEmpty())
    {
        m_firstElement = m_firstElement->next;
        delete(toDelete);
        toDelete = m_firstElement;
    }
    this->m_firstElement = nullptr;
    this->m_lastElement = nullptr;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (this == &other){
        return *this;
    }

    Node *toDelete = m_firstElement;
    while(!isEmpty()){
        m_firstElement = m_firstElement->next;
        delete(toDelete);
        toDelete = m_firstElement;
    }

    try {
        for (typename Queue<T>::ConstIterator currentNode = other.begin();
             currentNode != other.end(); ++currentNode) {
            pushBack(*currentNode);
        }
    }

    catch (const std::bad_alloc& memoryAllocationError) {
        delete (this);
        throw;
    }
    return *this;
}

template <class T>
void Queue<T>::pushBack(const T& element) {
    Node *newNode = new Node();
    newNode->next = nullptr;
    newNode->value = element;
    if (isEmpty()) {
        m_firstElement = newNode;
        m_lastElement = m_firstElement;
    }
    else {
        m_lastElement->next = newNode;
        m_lastElement = newNode;
    }

}

template <class T>
T& Queue<T>::front()
{
    if (isEmpty()){
        throw EmptyQueue();
    }
    return m_firstElement->value;
}

template <class T>
const T& Queue<T>::front() const {
    if (isEmpty()) {
        throw EmptyQueue();
    }
    return m_firstElement->value;
}

template <class T>
void Queue<T>::popFront()
{
    if (isEmpty()){
        throw EmptyQueue();
    }
    Node *temp = m_firstElement;
    m_firstElement = m_firstElement->next;
    delete(temp);
}

template <class T>
int Queue<T>::size() const
{
    int size = 0;
    if (isEmpty()){
        return size;
    }
    Node *tempHead = m_firstElement;
    while(tempHead != m_lastElement){
        size++;
        tempHead = tempHead->next;
    }
    return ++size;
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return (m_firstElement == nullptr);
}


template <class T>
class Queue<T>::Iterator
{
public:
    T& operator*();
    Iterator& operator++();
    Iterator operator++(int);

    bool operator!=(const Iterator& iterator);
    Iterator(const Iterator& other) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;

    class InvalidOperation{};

private:
    const Queue<T>* m_queue;
    Node *m_currentNode;
    Iterator(const Queue<T>* queue, Node *currentNode);
    friend class Queue<T>;
};

template <class T>
class Queue<T>::ConstIterator{
public:
    const T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);

    bool operator!=(const ConstIterator& iterator) const;
    ConstIterator(const ConstIterator& other) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    class InvalidOperation{};

private:
    const Queue<T>* m_queue;
    const Node *m_currentNode;
    ConstIterator(const Queue<T>* queue, const Node *currentNode);
    friend class Queue<T>;
};

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition condition)
{
    Queue<T> filteredQueue;
    for (typename Queue<T>::ConstIterator currentNode = queue.begin();
         currentNode != queue.end(); ++currentNode) {
        if (condition(*currentNode)) {
            filteredQueue.pushBack(*currentNode);
        }
    }
    return filteredQueue;
}

template <class T, class Operation>
void transform(Queue<T>& queue, Operation operation/*******void (*operation)(T&)*/) {
    for (typename Queue<T>::Iterator currentNode = queue.begin();
         currentNode != queue.end(); ++currentNode){
        operation(*currentNode);
    }
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, m_firstElement);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, nullptr);
}

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, Node* currentNode) : m_queue(queue),
                                                                         m_currentNode(currentNode) {}

template <class T>
T& Queue<T>::Iterator::operator*()
{
    if (!m_currentNode){
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return m_currentNode->value;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (m_currentNode == nullptr){
        throw Queue<T>::Iterator::InvalidOperation();
    }
    m_currentNode = m_currentNode->next;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    ++*this;
    return result;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator& iterator)
{
    return (m_currentNode != iterator.m_currentNode);
}


template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, m_firstElement);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, nullptr);
}

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, const Node *currentNode) : m_queue(queue),
                                                                                         m_currentNode(currentNode) {}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if (!m_currentNode){
        throw typename Queue<T>::ConstIterator::InvalidOperation();
    }
    return m_currentNode->value;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (m_currentNode == nullptr){
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    m_currentNode = m_currentNode->next;
    return *this;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    ConstIterator result = *this;
    ++*this;
    return result;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator& constIterator) const
{
    return (m_currentNode != constIterator.m_currentNode);
}

#endif //HEALTHPOINTS_H_QUEUE_H
