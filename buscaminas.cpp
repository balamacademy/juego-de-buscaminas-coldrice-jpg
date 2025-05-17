#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h>  
using namespace std;

// Emojis
const string oculto = "🟦";
const string mina = "💣";
const string vacio = "⬜";
const string numero_emoji[10] = {
    u8"0️⃣", u8"1️⃣", u8"2️⃣", u8"3️⃣", u8"4️⃣", u8"5️⃣", u8"6️⃣", u8"7️⃣", u8"8️⃣", u8"9️⃣"
};

string obtenerNumeroEmoji(int n){
    if (n >= 0 && n <= 9) {
        return numero_emoji[n];
    } else {
        return to_string(n);  
    }
}


string formatearCelda(const string& contenido){
    if (contenido == "⬜" || contenido == "🟦" || contenido == "💣") {
        return contenido + " ";
    } else {
        return contenido + " ";
    }
}

// Renderizar
void mostrarTablero(const vector<vector<string>>& visible){
    system("cls");
    int filas = visible.size();
    int columnas = visible[0].size();

    // Encabezado de columnas
    cout << "   "; 
    for(int col = 0; col < columnas; ++col){
        if (col < 10) cout << " "; 
        cout << col << " ";
    }
    cout << "\n";

    // Filas
    for(int fila = 0; fila < filas; ++fila){
        if(fila < 10) cout << " "; 
        cout << fila << " ";
        for(int col = 0; col < columnas; ++col){
            cout << formatearCelda(visible[fila][col]);
        }
        cout << "\n";
    }
}

// Contar minas alrededor
int contarMinas(const vector<vector<bool>>& minas, int x, int y){
    int total = 0;
    int filas = minas.size();
    int columnas = minas[0].size();
    for(int i = x - 1; i <= x + 1; ++i){
        for(int j = y - 1; j <= y + 1; ++j){
            if(i >= 0 && j >= 0 && i < filas && j < columnas && minas[i][j]){
                total++;
            }
        }
    }
    return total;
}

// Descubrir recursivamente
void descubrir(vector<vector<bool>>& minas, vector<vector<string>>& visible, int x, int y){
    int filas = minas.size();
    int columnas = minas[0].size();

    if(x < 0 || x >= filas || y < 0 || y >= columnas) return;
    if(visible[x][y] != oculto) return;

    if(minas[x][y]){
        visible[x][y] = mina;
        return;
    }

    int conteo = contarMinas(minas, x, y);
    visible[x][y] = (conteo == 0) ? vacio : obtenerNumeroEmoji(conteo);

    if(conteo == 0){
        for(int dx = -1; dx <= 1; ++dx){
            for(int dy = -1; dy <= 1; ++dy){
                if(dx != 0 || dy != 0){
                    descubrir(minas, visible, x + dx, y + dy);
                }
            }
        }
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8); 
    srand(time(0));

    int filas, columnas;
    cout << "Ingresa el número de filas: ";
    cin >> filas;
    cout << "Ingresa el número de columnas: ";
    cin >> columnas;

    vector<vector<bool>> minas(filas, vector<bool>(columnas, false));
    vector<vector<string>> visible(filas, vector<string>(columnas, oculto));

    int numMinas = (filas * columnas) / 5;
    int colocadas = 0;

    while(colocadas < numMinas){
        int x = rand() % filas;
        int y = rand() % columnas;
        if (!minas[x][y]) {
            minas[x][y] = true;
            colocadas++;
        }
    }

    while(true){
        mostrarTablero(visible);
        int x, y;
        cout << "Ingresa la fila y columna a descubrir (ej: 2 3): ";
        cin >> x >> y;

        if(x < 0 || x >= filas || y < 0 || y >= columnas){
            cout << "❌ Coordenadas inválidas.\n";
            continue;
        }

        if(minas[x][y]){
            visible[x][y] = mina;
            mostrarTablero(visible);
            cout << "💥 ¡Pisaste una mina! Fin del juego.\n";
            break;
        }

        descubrir(minas, visible, x, y);
    }

    return 0;
}
