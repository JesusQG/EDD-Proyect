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
void Tree<t>::print()
{
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
    cout << node->get_wizard().id << " , " << node->get_wizard().name << endl;
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

    if (node == nullptr) // arbol vacio, insertar nodo en la raiz
    {
        return new Node<t>(wi, nullptr, nullptr);
    }
    else
    {
        int father = wi.id_father;
        if (node->get_father() != father)
        {
            // Cambia a usar el nuevo método search
            node = search(father);
            if (node == nullptr)
                return nullptr; // No se encontró el padre
            if (node->get_children(izq) == nullptr)
            {
                node->set_childrenL(new Node<t>(wi, nullptr, nullptr));
            }
            else
            {
                node->set_childrenR(new Node<t>(wi, nullptr, nullptr));
            }
        }
        else
        {
            if (node->get_children(izq) == nullptr)
            {
                Node<t> *newnode = new Node<t>(wi, nullptr, nullptr);
                node->set_childrenL(newnode);
            }
            else
            {
                Node<t> *newnode = new Node<t>(wi, nullptr, nullptr);
                node->set_childrenR(newnode);
            }
        }
    }
    return this->root;
}

template <class t>
void Tree<t>::getfromcsv()
{
    ifstream file("./bin/data.csv"); // se debe ubicar en la carpeta "PROYECTO" para abrir correctamente
    if (!file.is_open())
    {
        cout << "\n No se pudo abrir el archivo\n";
    }
    string line;
    getline(file, line); // Saltar encabezado

    while (getline(file, line))
    {
        if (line.empty())
            continue; // Saltar líneas vacías

        stringstream ss(line);
        string item;

        int id, age, id_father;
        char gender;
        bool is_dead, is_owner;
        string name, last_name, type_magic;

        // Leer y convertir cada campo
        getline(ss, item, ',');
        if (item.empty())
            continue; // Saltar si el campo está vacío
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
    cout << "\n El arbol ha sido creado\n";
}
