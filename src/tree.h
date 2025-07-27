#pragma once
#include "./node_wizard.cpp"

template <class t>
class Tree
{
private:
    Node<t> *root = nullptr;
    Node<t> *insert_private(Wizard, Node<t> *);
    Node<t> *search_private(Node<t> *, int);

public:
    Tree();
    Tree(Node<t> *);
    bool isEmpty();
    bool isLeaf(Node<t> *);
    void getfromcsv();
    void print();
    void print(Node<t> *);
    void insert(Wizard);
    Node<t> *search(int);
};
