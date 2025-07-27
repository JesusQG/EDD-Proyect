#include "./tree.h"

template <class t>
Tree<t>::Tree()
{
    this->root = nullptr;
}

template <class t>
bool Tree<t>::isEmpty()
{
    return this->root == nullptr;
}

template <class t>
bool Tree<t>::isLeaf(Node<t> *node)
{
    return node->get_children(0) == nullptr && node->get_children(1) == nullptr;
}

template <class t>
void Tree<t>::print_inorden()
{
    cout << "\nImprimiendo arbol en inorden:\n";
    print(this->root);
    return;
}

template <class t>
void Tree<t>::print(Node<t> *node)
{
    if (node == nullptr)
    {
        return;
    }
    print(node->get_children(izq));
    Wizard w = node->get_wizard();
    cout << "ID: " << w.id
         << " | Padre: " << w.id_father
         << " | Nombre y Apellido: " << w.name << " " << w.last_name
         << " | Magia: " << w.type_magic;
    if (w.is_owner)
    {
        cout << "| ---> Este mago es el owner";
    }
    cout << endl;
    print(node->get_children(der));
}

template <class t>
Tree<t>::Tree(Node<t> *node)
{
    this->root = node;
}

template <class t>
void Tree<t>::insert(Wizard wi)
{
    root = insert_private(wi, root);
    return;
}

template <class t>
Node<t> *Tree<t>::search(int id_father)
{
    return search_private(this->root, id_father);
}

template <class t>
Node<t> *Tree<t>::search_private(Node<t> *node, int id_father)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->get_wizard().id == id_father)
    {
        return node;
    }
    Node<t> *found = search_private(node->get_children(izq), id_father);
    if (found != nullptr)
        return found;
    return search_private(node->get_children(der), id_father);
}

template <class t>
Node<t> *Tree<t>::insert_private(Wizard wi, Node<t> *node)
{
    if (node == nullptr)
    {
        return new Node<t>(wi, nullptr, nullptr);
    }
    if (node->get_wizard().id == wi.id_father)
    {
        if (node->get_children(izq) == nullptr)
        {
            node->set_childrenL(new Node<t>(wi, nullptr, nullptr));
        }
        else if (node->get_children(der) == nullptr)
        {
            node->set_childrenR(new Node<t>(wi, nullptr, nullptr));
        }
        return node;
    }
    if (node->get_children(izq) != nullptr)
        insert_private(wi, node->get_children(izq));
    if (node->get_children(der) != nullptr)
        insert_private(wi, node->get_children(der));

    return node;
}

template <class t>
void Tree<t>::getfromcsv()
{
    ifstream file("./bin/data.csv");
    if (!file.is_open())
    {
        cout << "\n No se pudo abrir el archivo\n";
    }
    string line;
    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string item;
        int id, age, id_father;
        char gender;
        bool is_dead, is_owner;
        string name, last_name, type_magic;
        getline(ss, item, ',');
        if (item.empty())
            continue;
        id = stoi(item);
        getline(ss, name, ',');
        getline(ss, last_name, ',');
        getline(ss, item, ',');
        gender = item.empty() ? ' ' : item[0];
        getline(ss, item, ',');
        age = item.empty() ? 0 : stoi(item);
        getline(ss, item, ',');
        id_father = item.empty() ? 0 : stoi(item);
        getline(ss, item, ',');
        is_dead = item.empty() ? 0 : stoi(item);
        getline(ss, type_magic, ',');
        getline(ss, item, ',');
        is_owner = item.empty() ? 0 : stoi(item);

        Wizard w(id, name, last_name, gender, age, id_father, is_dead, type_magic, is_owner);
        insert(w);
    }

    file.close();
    cout << "\nEl arbol ha sido creado correctamente\n";
}

template <class t>
void Tree<t>::print_owner_alive_descendence()
{
    cout << "\nBuscando la descendencia vivia del mago owner...\n";
    Node<t> *node = get_owner();
    if (node->not_father())
    {
        cout << "\nEl owner del hechizo no tiene descendientes vivos\n";
        return;
    }
    else
    {
        print_alive_descendence(node->get_children(izq));
        print_alive_descendence(node->get_children(der));
    }
    return;
}

template <class t>
Node<t> *Tree<t>::get_owner()
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (root->get_wizard().is_owner == true)
        {
            return root;
        }
        else
        {
            Node<t> *owner = search_owner(root);
            return owner;
        }
    }
}

template <class t>
Node<t> *Tree<t>::search_owner(Node<t> *node)
{
    if (node == nullptr)
        return nullptr;
    if (node->get_wizard().is_owner)
        return node;
    Node<t> *found = search_owner(node->get_children(izq));
    if (found != nullptr)
        return found;
    return search_owner(node->get_children(der));
}

template <class t>
void Tree<t>::print_alive_descendence(Node<t> *node)
{
    if (node == nullptr)
        return;
    print_alive_descendence(node->get_children(izq));
    if (node->alive())
    {
        Wizard w = node->get_wizard();
        cout << "ID: " << w.id
             << " | Padre: " << w.id_father
             << " | Nombre y Apellido: " << w.name << " " << w.last_name
             << " | Magia: " << w.type_magic << endl;
    }

    print_alive_descendence(node->get_children(der));
}