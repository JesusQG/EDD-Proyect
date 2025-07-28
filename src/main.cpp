#include "./tree.cpp"

int main()
{
    cout << "\n++++++++++++++++EL HECHIZO DEL MAGO HA SIDO CREADO, BIENVENIDO AL PODER+++++++++++++++++++++++++++++++++\n";
    bool keep_me_here = true;
    while (keep_me_here)
    {
        Tree<int> Arbol;
        Arbol.getfromcsv();
        int opcion;
        cout << "\n*******ESCOGE ALGUNA DE TUS HABILIDADES MAGICAS:\n";
        cout << "1. SABER TODOS LOS MAGOS RELACIONADOS A TI \n";
        cout << "2. SABER TU SUCESION VIVA\n";
        cout << "3. SABOTEAR DATOS DE CUALQUIER MAGO\n ";
        cout << "4. AVERIGUAR HECHIZOS DE CUALQUIER MAGO\n";
        cout << "5. CERRAR HECHIZO \n";
        cout << "ESCOGE SABIAMENTE: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            Arbol.print_inorden();
            getch();
            break;
        case 2:
            Arbol.print_owner_alive_descendence();
            getch();
            break;
        case 3:
            Arbol.edit_wizard();
            getch();
            break;
        case 4:
            Arbol.print_wizard_spells();
            getch();
            break;
        case 5:
            keep_me_here = false;
            getch();
            break;
        default:
            cout << "EFECTO NO RECONOCIDO DENTRO DEL HECHIZO, VUELVE A ESCOGER: \n";
        }
    }
    cout << "\nGRACIAS POR USAR EL HECHIZO, CERRANDO...\n";
    return 0;
}