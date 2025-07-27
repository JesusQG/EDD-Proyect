#include "./node_wizard.h"

template <class t>
Node<t>::Node()
{
    left = nullptr;
    right = nullptr;
    data = 0;
}

template <class t>
Node<t>::Node(Wizard w, Node<t> *left, Node<t> *right)
{
    this->left = left;
    this->right = right;
    this->w.age = w.age;
    this->w.gender = w.gender;
    this->w.id = w.id;
    this->w.id_father = w.id_father;
    this->w.is_dead = w.is_dead;
    this->w.is_owner = w.is_owner;
    this->w.last_name = w.last_name;
    this->w.name = w.name;
    this->w.type_magic = w.type_magic;
    data = 0;
}

template <class t>
Node<t>::Node(Wizard w, Node<t> *left, Node<t> *right, t data)
{
    this->left = left;
    this->right = right;
    this->w.age = w.age;
    this->w.gender = w.gender;
    this->w.id = w.id;
    this->w.id_father = w.id_father;
    this->w.is_dead = w.is_dead;
    this->w.is_owner = w.is_owner;
    this->w.last_name = w.last_name;
    this->w.name = w.name;
    this->w.type_magic = w.type_magic;
    this->data = data;
}
template <class t>
Node<t> *Node<t>::get_children(int c)
{
    if (c == 0)
    {
        return this->left;
    }
    else
    {
        return this->right;
    }
}

template <class t>
void Node<t>::set_childrenL(Node<t> *children)
{
    this->left = children;
}

template <class t>
void Node<t>::set_childrenR(Node<t> *children)
{
    this->right = children;
}

template <class t>
bool Node<t>::alive()
{
    return this->w.is_dead == false;
}

template <class t>
void Node<t>::set_wizard(Wizard w)
{
    this->w.age = w.age;
    this->w.gender = w.gender;
    this->w.id = w.id;
    this->w.id_father = w.id_father;
    this->w.is_dead = w.is_dead;
    this->w.is_owner = w.is_owner;
    this->w.last_name = w.last_name;
    this->w.name = w.name;
    this->w.type_magic = w.type_magic;
}

template <class t>
Wizard Node<t>::get_wizard()
{
    return this->w;
}

template <class t>
bool Node<t>::not_father()
{
    return this->left == nullptr && this->right == nullptr;
}

template <class t>
void Node<t>::set_data(t data)
{
    this->data = data;
}

template <class t>
t Node<t>::get_data()
{
    return this->data;
}

template <class t>
int Node<t>::get_father()
{
    return this->w.id_father;
}