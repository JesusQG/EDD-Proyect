#pragma once
#include "./node_wizard.cpp"

template <class t>
class Tree
{
private:
    Node<t> *root = nullptr;
    Node<t> *insert_private(Wizard, Node<t> *);
    Node<t> *search_private(Node<t> *, int);
    Node<t> *search_owner(Node<t> *);
    void print_alive_descendence(Node<t> *);
    void print(Node<t> *);

public:
    Tree();
    Tree(Node<t> *);
    bool isEmpty();
    bool isLeaf(Node<t> *);
    void getfromcsv();
    void print_inorden();
    void insert(Wizard);
    Node<t> *search(int);
    Node<t> *get_owner();
    void print_owner_alive_descendence();
    void edit_wizard();
    void edit_wizard(int);
};
