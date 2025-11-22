#include <iostream>
#include <thread>   // ?? añadido
using namespace std;

bool compara(char* ini, char* fin, char* palabra) {
    for (char* p = palabra; *p; p++) {
        if (ini > fin)
            return false;
        if (*p != *ini)
            return false;
        ini++;
    }
    return true;
}

int contar(char(*mat)[10], char* palabra)
{
    char* ini = *mat;
    char* fin = *(mat + 9) + 9;
    int contador = 0;

    for (char* p = ini; p < fin; p++)
        if (compara(p, fin, palabra))
            contador++;
    return contador;
}

// función que usará cada hilo
void tarea(char (*mat)[10], char* palabra, int* resultado) {
    *resultado = contar(mat, palabra);
}

int main()
{
    char mat[10][10] = {
        {'C','A','S','A','D','O','R','A','D','O'},
        {'D','C','A','S','A','D','O','A','S','A'},
        {'D','O','R','A','D','O','C','A','S','A'},
        {'A','S','A','D','O','R','A','D','O','S'},
        {'C','A','S','A','D','O','C','A','S','A'},
        {'A','D','O','A','S','A','D','O','S','O'},
        {'A','S','A','C','C','A','S','A','D','O'},
        {'A','S','A','A','S','A','C','A','S','A'},
        {'C','A','S','A','D','O','A','S','A','D'},
        {'D','O','R','A','D','O','A','S','A','C'},
    };

    char palabras[][10] = { "CASADO", "ASADO","DORADO","CASA","ASA" };

    int resultados[5] = { 0 };       // para guardar los contadores
    thread h[5];               // un hilo por palabra

    for (int i = 0; i < 5; i++) {
        h[i] = thread(tarea, mat, palabras[i], &resultados[i]);

    }

    // Esperar a cada hilo
    for (int i = 0; i < 5; i++) {
        h[i].join();
    }

    // Mostrar resultados
    for (int i = 0; i < 5; i++) {
        cout << "La palabra " << palabras[i]
            << " aparece " << resultados[i] << " veces" << endl;
    }

    return 0;
}