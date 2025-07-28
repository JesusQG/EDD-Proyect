ESTRUCTURA
- CARPETA BIN
  Contiene los datos que se utilizan en el programa; un archivo .csv para los magos y una aparte para los hechizos que logran hacer cada uno.
  Tambien contiene el ejecutable 
- CARPETA SRC
  En esta carpeta se encuentra el codigo necesario para manejar los datos de los archivos .csv y permite cumplir una serie de requerimientos solicitados.
  Las estrcucturas dinamicas de datos se definen e implementan en esta carpeta, encontrandose un archivo .h y otro .cpp (asociados a la definicion e
  implementacion respectivamente). Finalmente, se encuentra el archivo main.cpp, el cual es el objeto de compilacion
  
PRECACUCIONES
  * Para avanzar al menu despues de seleccionar una opcion y esta finalize, se debe presionar el teclado.
  * Antes de modificar un nodo revise los tipos de datos, ya que luego al reobtener los datos estos pueden no ser acorde al .csv
  * Sientase libre de modificar los archivos csv, pero recuerde que si desea agregar un nuevo mago, su padre ya debe existir, caso
   contrario NO sera tomado en cuenta (A menos que este sea el primer nodo, caso que no se maneja debido a los datos ya suministrados).
