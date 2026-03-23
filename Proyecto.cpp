/*
Nombre: Pablo Dávila Granda
Fecha: 22/03/2026
MINI PROYECTO
Descripción: Este programa permite registrar estudiantes, sus notas, calcular promedios y 
mostrar información como el mejor y peor promedio. 
El programa utiliza arreglos para almacenar los datos de los estudiantes y sus notas, ofrece 
un menú interactivo para realizar las diferentes operaciones.

*/

#include <iostream>
#include <string>
using namespace std;

// CONSTANTES
const int MAX_ESTUDIANTES = 10;
const int NUM_NOTAS       = 4;

//ARREGLOS PARA GUARDAR LOS DATOS
string nombres[MAX_ESTUDIANTES];
float  notas[MAX_ESTUDIANTES][NUM_NOTAS];
int    totalEstudiantes = 0;

//USO DE VARIABLES 
void mostrarMenu();
void registrarEstudiante();
void mostrarEstudiantes();
void buscarEstudiante();
void mostrarMejorYPeor();
float calcularPromedio(int indice);
bool nombreValido(const string& nombre);
void pausar();

//METODO PARA INICIAR EL MENU 
int main() {
    int opcion;

    do {
        mostrarMenu();
        cout << "  Opcion: ";
        cin  >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n   Ingresa un numero valido.\n";
            pausar();
            continue;
        }
        cin.ignore(1000, '\n');

        switch (opcion) {
            case 1: registrarEstudiante(); 
            break;
            case 2: mostrarEstudiantes();  
            break;
            case 3: buscarEstudiante();    
            break;
            case 4: mostrarMejorYPeor();   
            break;
            case 0:
                cout << " Cerrando cesión"<< endl;
                
                !"\n\n";
                break;
            default:
                cout << " Opcion no valida. Intenta de nuevo."<< endl;;
                pausar();
        }
    } while (opcion != 0);

    return 0;
}

// MENU PRINCIPAL
void mostrarMenu() { 
    
    cout << "  ========================================"<< endl;
    cout << "         M E N U   P R I N C I P A L      "<< endl;
    cout << "  ========================================"<< endl;
    cout << "   Estudiantes registrados: " << totalEstudiantes << " / " << MAX_ESTUDIANTES << "\n";
    cout << "  ----------------------------------------"<< endl;
    cout << "   1. Registrar estudiante"<< endl;
    cout << "   2. Ver todos los estudiantes"<< endl;
    cout << "   3. Buscar estudiante por nombre"<< endl;
    cout << "   4. Ver mejor y peor promedio"<< endl;
    cout << "   0. Salir"<< endl;
    cout << "  ----------------------------------------"<< endl;
}

//CALCULAR PROMEDIO DEL ESTUDIANTE
float calcularPromedio(int i) {
    float suma = 0;
    for (int j = 0; j < NUM_NOTAS; j++)
        suma += notas[i][j];
    return suma / NUM_NOTAS;
}

// VALIDAR QUE EL NOMBRE NO ESTE VACIO 
bool nombreValido(const string& nombre) {
    for (char c : nombre)
        if (c != ' ') return true;
    return false;
}

// METODO PARA REGISTRAR ESTUDIANTE 
void registrarEstudiante() {
    cout << " ** REGISTRAR ESTUDIANTE ** "<< endl;

    if (totalEstudiantes >= MAX_ESTUDIANTES) {
        cout << "  Limite alcanzado (" << MAX_ESTUDIANTES << " estudiantes)."<< endl;
        pausar();
        return;
    }

    // NOMBRE
    string nombre;
    do {
        cout << "  Nombre del estudiante: ";
        getline(cin, nombre);
        if (!nombreValido(nombre))
            cout << " El nombre no puede estar vacio¡¡"<< endl;
    } while (!nombreValido(nombre));

    // NOTAS
    for (int j = 0; j < NUM_NOTAS; j++) {
        float nota;
        do {
            cout << "  Nota " << (j + 1) << " (0 - 10): ";
            cin  >> nota;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n'); 
                nota = -1;
            }
            if (nota < 0 || nota > 10)
                cout << "  [!] La nota debe estar entre 0 y 10.\n";
        } while (nota < 0 || nota > 10);
        cin.ignore(1000, '\n');
        notas[totalEstudiantes][j] = nota;
    }

    nombres[totalEstudiantes] = nombre;
    totalEstudiantes++;

    float prom = calcularPromedio(totalEstudiantes - 1);
    cout << " Estudiante registrado."<< endl;
    cout << "  Promedio: " << prom << " --> " << (prom >= 6 ? "APROBADO" : "REPROBADO") << "\n";
    pausar();
}

// METODO PARA MOSTRAR LOS ESTUDIANTES
void mostrarEstudiantes() {
    cout << " -- LISTADO DE ESTUDIANTES --"<< endl;

    if (totalEstudiantes == 0) {
        cout << "  No hay estudiantes registrados."<< endl;
        pausar();
        return;
    }

    cout << "  ---------------------------------------------------------------"<< endl;;
    cout << "   N  | Nombre                 | N1   | N2   | N3   | Promedio"<< endl;
    cout << "  ---------------------------------------------------------------"<< endl;

    for (int i = 0; i < totalEstudiantes; i++) {
        float prom = calcularPromedio(i);
        cout << "   " << (i + 1);
        if (i + 1 < 10) cout << " ";
        cout << " | ";

        // NOMBRE Y ESPACIOS PARA ALINEAR
        cout << nombres[i];
        int espacios = 22 - (int)nombres[i].length();
        for (int s = 0; s < espacios; s++) cout << " ";
        cout << " | ";

        for (int j = 0; j < NUM_NOTAS; j++) {
            cout << notas[i][j];
            if (notas[i][j] < 10) cout << " ";
            cout << "  | ";
        }

        cout << prom;
        cout << " (" << (prom >= 6 ? "APR" : "REP") << ")\n";
    }

    cout << "  ============================================"<< endl;
    pausar();
}

// METODO BUSCAR ESTUDIANTE POR NOMBRE
void buscarEstudiante() {
    cout << "  -- BUSCAR ESTUDIANTE --"<< endl;

    if (totalEstudiantes == 0) {
        cout << "  No hay estudiantes registrados. "<< endl;
        pausar();
        return;
    }
 
    cout << "  Nombre a buscar: ";
    string busqueda;
    getline(cin, busqueda); 

    bool encontrado = false;
    for (int i = 0; i < totalEstudiantes; i++) {
        if (nombres[i] == busqueda) {
            float prom = calcularPromedio(i);
            cout << "  Estudiante encontrado: "<< endl;
            cout << "  Nombre  : " << nombres[i] << "\n";
            for (int j = 0; j < NUM_NOTAS; j++)
                cout << "  Nota " << (j + 1) << "  : " << notas[i][j] << "\n";
            cout << "  Promedio: " << prom;
            cout << " --> " << (prom >= 6 ? "APROBADO" : "REPROBADO") << "\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        cout << "  No se encontro ningun estudiante .\n";

    pausar();
}

// METODO PARA MOSTRAR EL MEJOR Y PEOR PROMEDIO
void mostrarMejorYPeor() {
    cout << " ** MEJOR Y PEOR PROMEDIO **"<< endl;

    if (totalEstudiantes == 0) {
        cout << "  No hay estudiantes registrados."<< endl;
        pausar();
        return;
    }
 
    int indiceMejor = 0;
    int indicePeor  = 0;

    for (int i = 1; i < totalEstudiantes; i++) {
        if (calcularPromedio(i) > calcularPromedio(indiceMejor)) indiceMejor = i;
        if (calcularPromedio(i) < calcularPromedio(indicePeor))  indicePeor  = i;
    }

    cout << "  Mejor promedio:"<< endl;
    cout << "  Nombre  : " << nombres[indiceMejor] << "\n";
    cout << "  Promedio: " << calcularPromedio(indiceMejor) << "\n";

    cout << "  Peor promedio: "<< endl;
    cout << "  Nombre  : " << nombres[indicePeor] << "\n";
    cout << "  Promedio: " << calcularPromedio(indicePeor) << "\n";

    pausar();
}

// PAUSAR EL PROGRAMA HASTA QUE EL USUARIO DECIDA CONTINUAR
void pausar() {
    cout << "\n  Presiona Enter para continuar...";
    cin.ignore(1000, '\n');
}
