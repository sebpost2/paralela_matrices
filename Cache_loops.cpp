#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

//CAMBIA LOS VALORES DE LAS FILAS Y COLUMNAS A UNO SOLO SI TOTAL=1, si total=0 
//Manualmente se especifica las filas y columnas de cada matriz.
bool total = 1;
int total_int = 10;
int totales[] = {500,1000,2000,2500,3500,5000,7500,10000};
int totales2[] = { 100,200,300,400,500,600,700,800 };

int  MAX = (1000 * (int)(!total)) + ((total_int) * (int)(total)),
MAX_AC = (1000 * (int)(!total)) + ((total_int) * (int)(total));
int  MAX_BF = (1000 * (int)(!total)) + ((total_int) * (int)(total)),
MAX_BC = (1000 * (int)(!total)) + ((total_int) * (int)(total));

vector<vector<int>> A; vector<vector<int>> B; vector<vector<int>> C;
int i, j, k;
int block_size[] = { 32, 64, 128, 256, 512 };

int min(int a, int b) {
    if (a >= b) {
        return b;
    }
    else {
        return a;
    }
}

void fill_m(vector<vector<int>> &A, int size) {
    A.resize(size);
    for (int i = 0; i < size; i++) {
        A[i].resize(size);
    }
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % 10;
        }
    }
}

void print(vector<vector<int>> A) {
    for (int it = 0; it < A.size(); it++) {
        std::cout << "|";
        for (int jt = 0; jt < A.size(); jt++) {
            std::cout << A[it][jt] << "|";
        }
        std::cout << std::endl;
    }
}

void blocks(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &C, int block_size) {
    //bloques, 6 bucles
    int size = MAX;

    int result, sum;
    for (int I = 0; I < size; I += block_size) {
        for (int J = 0; J < size; J += block_size) {
            for (int K = 0; K < size; K += block_size) {

                for (int i = I; i < min(I + block_size, size); i++) {
                    for (int j = J; j < min(J + block_size, size); j++) {
                        sum = 0;
                        for (int k = K; k < min(K + block_size, size); k++) {
                            result = A[i][k] * B[k][j];
                            sum += result;
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}

int main() {

    for (int i1 = 0; i1 < 8; i1++) {
        fill_m(A, totales2[i1]);

        fill_m(B, totales2[i1]);

        fill_m(C, totales2[i1]);

        cout << "Numero de elementos: " << totales2[i1] << endl;

        auto start = std::chrono::high_resolution_clock::now();

        //classic
        for (i = 0; i < A.size(); i++) {
            for (j = 0; j < B.size(); j++) {
                for (k = 0; k < C.size(); k++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }

        auto stop = std::chrono::high_resolution_clock::now();

        //print(C);

        auto duration1 =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Primer loop demoro: " << duration1.count() << std::endl;

        for (int i2 = 0; i2 < 5; i2++) {

            start = std::chrono::high_resolution_clock::now();

            blocks(A, B, C, block_size[i2]);

            stop = std::chrono::high_resolution_clock::now();

            //print(C);


            auto duration2 =
                std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "segundo loop demoro en la iteracion con "<<block_size[i2]<< " bloques : " << duration2.count() << std::endl;
        }
    }
}