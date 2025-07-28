#include "./tree.cpp"

int main()
{
    Tree<int> Arbol;
    Arbol.getfromcsv();
    Arbol.print_inorden();
    Arbol.print_owner_alive_descendence();
    Arbol.print_wizard_spells();
}