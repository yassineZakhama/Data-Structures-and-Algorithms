#ifndef _NODE_H
#define _NODE_H

template <typename T>
class Node
{
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

public:
    Node();
    Node(T value, Node<T>* next = 0, Node<T>* prev = 0);
    ~Node();
};
/*===========================================================*/
template <typename T>
Node<T>::Node()
{
    next = nullptr;
    prev = nullptr;
    value = 0;
}
template <typename T>
Node<T>::Node(T value, Node<T>* next, Node<T>* prev)
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template <typename T>
Node<T>::~Node()
{}

#endif