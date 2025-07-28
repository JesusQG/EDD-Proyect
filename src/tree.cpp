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
    if (w.is_dead == false)
    {
        cout << "| Estado: vivo  ";
    }
    else
    {
        cout << "| Estado: muerto ";
    }
    if (w.is_owner)
    {
        cout << "| ---> Este mago es el owner";
    }
    if (w.id_father == 0)
    {
        cout << "| ---> Este mago es el creador del hechizo";
    }
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------\n";
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
    ifstream file("./bin/wizard.csv");
    if (!file.is_open())
    {
        cout << "\n No se pudo abrir el archivo, verificar la ubicacion del terminal\n";
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
    cout << "\nARBOL CREADO CORRECTAMENTE\n";
}

template <class t>
void Tree<t>::print_owner_alive_descendence()
{
    cout << "\nBuscando la descendencia viva del mago owner...\n";
    Node<t> *node = get_owner();
    if (node->not_father())
    {
        cout << "\nNo se han encontrado descendientes vivos del nodo owner\n";
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
        cout << "--------------------------------------------------------------------------------------------------\n";
    }

    print_alive_descendence(node->get_children(der));
}

template <class t>
Node<t> *Tree<t>::search(int id)
{
    return search_private(this->root, id);
}

template <class t>
Node<t> *Tree<t>::search_private(Node<t> *node, int id)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->get_wizard().id == id)
    {
        return node;
    }
    Node<t> *found = search_private(node->get_children(izq), id);
    if (found != nullptr)
        return found;
    return search_private(node->get_children(der), id);
}

template <class t>
void Tree<t>::edit_wizard()
{
    int id;
    cout << "\n EDITAR NODO\n ";
    cout << "\n Ingrese el id del nodo que desea modificar: ";
    cin >> id;
    cout << "\n";
    Node<t> *node = search(id);
    if (node == nullptr)
    {
        cout << "Error, nodo no encontrado" << endl;
        return;
    }

    string name, last_name, type_magic;
    char gender;
    int age;
    bool is_dead, is_owner;
    int id_father = node->get_wizard().id_father;
    cout << "Ingrese el nuevo nombre: ";
    cin >> ws;
    cin >> name;
    cout << "Ingrese el nuevo apellido: ";
    cin >> last_name;
    cout << "Ingrese el nuevo genero (H/M): ";
    cin >> gender;
    cout << "Ingrese la nueva edad: ";
    cin >> age;
    cout << "Esta muerto? (0 = No / 1 = Si): ";
    cin >> is_dead;
    cout << "Ingrese el nuevo tipo de magia: ";
    cin >> ws;
    getline(cin, type_magic);
    cout << "Es owner? (0 = No, 1 = Si): ";
    cin >> is_owner;

    Wizard new_wiz(id, name, last_name, gender, age, id_father, is_dead, type_magic, is_owner);
    node->set_wizard(new_wiz);

    ifstream file_in("./bin/wizard.csv");
    ofstream file_out("./bin/data_temp.csv");
    string line;
    bool found = false;
    getline(file_in, line);
    file_out << line << endl;
    while (getline(file_in, line))
    {
        stringstream ss(line);
        string item;
        getline(ss, item, ',');
        int current_id = stoi(item);

        if (current_id == id)
        {
            file_out << new_wiz.id << ","
                     << new_wiz.name << ","
                     << new_wiz.last_name << ","
                     << new_wiz.gender << ","
                     << new_wiz.age << ","
                     << new_wiz.id_father << ","
                     << new_wiz.is_dead << ","
                     << new_wiz.type_magic << ","
                     << new_wiz.is_owner << endl;
            found = true;
        }
        else
        {
            file_out << line << endl;
        }
    }
    file_in.close();
    file_out.close();
    remove("./bin/wizard.csv");
    rename("./bin/data_temp.csv", "./bin/wizard.csv");

    if (found)
        cout << "Nodo y archivo CSV modificados correctamente.\n";
    else
        cout << "No se encontró el id en el archivo CSV.\n";
}
template <class t>
void Tree<t>::print_wizard_spells()
{
    int id;
    cout << "\nCual es el mago del que desea ver los hechizos? : ";
    cin >> id;
    print_wizard_spells(id);
}

template <class t>
void Tree<t>::print_wizard_spells(int id)
{
    ifstream file("./bin/spells.csv");
    if (!file.is_open())
    {
        cout << "\nNo se pudo abrir el archivo de spells.\n";
        return;
    }
    string line;
    getline(file, line);
    bool found = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string item;
        getline(ss, item, ',');
        int id_wizard = stoi(item);
        if (id_wizard == id)
        {
            string name_spell, effect;
            getline(ss, name_spell, ',');
            getline(ss, effect, ',');
            cout << "Hechizo: " << name_spell << " | Efecto: " << effect << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Este mago no tiene hechizos registrados.\n";
    }
    file.close();
}