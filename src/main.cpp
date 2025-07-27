#include "./tree.cpp"

int main()
{
    Tree<int> Arbol;
    Arbol.getfromcsv();
    Arbol.print_inorden();
    Arbol.print_owner_alive_descendence();
    Arbol.edit_wizard();
    cout << "Arbol luego de editar nodo:\n ";
    Arbol.print_inorden();
}