#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Wizard
{
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    string type_magic;
    bool is_owner;

    // Constructor por defecto
    Wizard() : id(-999), name(""), last_name(""), gender(' '), age(0), id_father(-999), is_dead(false), type_magic(""), is_owner(false) {}

    // Constructor personalizado
    Wizard(int id, string name, string last_name, char gender, int age, int id_father, bool is_dead, string type_magic, bool is_owner) : id(id), name(name), last_name(last_name), gender(gender), age(age), id_father(id_father), is_dead(is_dead), type_magic(type_magic), is_owner(is_owner) {}
};

template <class t>
class Node
{
private:
    Wizard w;
    Node<t> *left;
    Node<t> *right;
    t data;

public:
    Node();
    Node(Wizard, Node<t> *, Node<t> *);
    Node(Wizard, Node<t> *, Node<t> *, t data);
    Node<t> *get_children(int);
    void set_wizard(Wizard);
    Wizard get_wizard();
    bool not_father();
    void set_data(t);
    t get_data();
    void set_childrenL(Node<t> *);
    void set_childrenR(Node<t> *);
    bool wizard_alive();
};