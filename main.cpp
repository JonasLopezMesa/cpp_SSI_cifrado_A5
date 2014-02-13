//
//  main.cpp
//  1
//
//  Created by jonas on 26/02/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//
#include <iostream>
using namespace std;

int clave[64] = {0,1,0,0,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,1,0,0,1,1,1,0,1,0};
int mensaje[228] = {};
int frame_number[22] = {1,1,1,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1};
int secuencia_cifrante[228] = {0};
struct REGISTRO1 {
    int iden = 1;
    int sizep = 4;
    int sizev = 19;
        int vpolinomio[4] = {0,1,2,5};
    int bit_clock = 10;
    int tapon[4] = {13,16,17,18};
    int registrov[19] = {0};
};

struct REGISTRO2 {
    int iden = 2;
    int sizev = 22;
    int sizep = 2;
        int vpolinomio[2] = {0,1};
    int bit_clock = 11;
    int tapon[2] = {20,21};
    int registrov[22] = {0};
};

struct REGISTRO3 {
    int iden = 3;
    int sizev = 23;
    int sizep = 4;
        int vpolinomio[4] = {0,1,2,15};
    int bit_clock = 12;
    int tapon[4] = {7,20,21,22};
    int registrov[23] = {0};
};

void imprimir(REGISTRO1& rr1, REGISTRO2& rr2, REGISTRO3& rr3){
    cout << "    ";
    for (int i = 0; i < 19; i++) {
        if (i == rr1.bit_clock || i == rr1.bit_clock+1 ) {
            cout << "|";
        }
        cout << rr1.registrov[i];
        
    }
    cout << endl;
    
    cout << " ";
    for (int i = 0; i < 22; i++) {
        if (i == rr2.bit_clock || i == rr2.bit_clock+1 ) {
            cout << "|";
        }
        cout << rr2.registrov[i];
    }
    cout << endl;
    
    
    for (int i = 0; i < 23; i++) {
        if (i == rr3.bit_clock || i == rr3.bit_clock+1 ) {
            cout << "|";
        }
        cout << rr3.registrov[i];
    }
    cout << endl;
    cout << endl;
}

void funcion_mayoria(int c1, int c2, int c3, int* resultado){
    if (c1 == 0 && c2 == 0 && c3 == 0) {
        resultado[0] = 1;
        resultado[1] = 1;
        resultado[2] = 1;
        
    }
    if (c1 == 0 && c2 == 0 && c3 == 1) {
        resultado[0] = 1;
        resultado[1] = 1;
        resultado[2] = 0;
        
    }
    if (c1 == 0 && c2 == 1 && c3 == 0) {
        resultado[0] = 1;
        resultado[1] = 0;
        resultado[2] = 1;

    }
    if (c1 == 0 && c2 == 1 && c3 == 1) {
        resultado[0] = 0;
        resultado[1] = 1;
        resultado[2] = 1;

    }
    if (c1 == 1 && c2 == 0 && c3 == 0) {
        resultado[0] = 0;
        resultado[1] = 1;
        resultado[2] = 1;

    }
    if (c1 == 1 && c2 == 0 && c3 == 1) {
        resultado[0] = 1;
        resultado[1] = 0;
        resultado[2] = 1;

    }
    if (c1 == 1 && c2 == 1 && c3 == 0) {
        resultado[0] = 1;
        resultado[1] = 1;
        resultado[2] = 0;

    }
    if (c1 == 1 && c2 == 1 && c3 == 1) {
        resultado[0] = 1;
        resultado[1] = 1;
        resultado[2] = 1;

    }
}

int main()
{
    REGISTRO1 rr1;
    REGISTRO2 rr2;
    REGISTRO3 rr3;
    
    int opcion;
    cout << "1. A5/1 Completo. " << endl;
    cout << "2. Sin inicialización. " << endl;
    cin >> opcion;
    if (opcion == 1) {
        //PASO 1
        ////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////inicializar a 0////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < rr1.sizev; i++) {
            rr1.registrov[i] = 0;
        }
        for (int i = 0; i < rr2.sizev; i++) {
            rr2.registrov[i] = 0;
        }
        for (int i = 0; i < rr3.sizev; i++) {
            rr3.registrov[i] = 0;
        }
        cout << "registros inicializados a 0." << endl;
        //PASO 2
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////inicializar clave///////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        int r1 = 0,r2 = 0,r3 = 0;
        for (int i = 0; i < 64; i++) {
            r1 = rr1.registrov[rr1.vpolinomio[0]];
            
            for (int j = 1; j < rr1.sizep; j++) {
                r1 = r1^rr1.registrov[rr1.vpolinomio[j]];
            }
            r1 = r1^clave[i];
            int tmp1[19];
            tmp1[18] = 0;
            for (int i = 0; i < rr1.sizev; i++) {
                tmp1[i] = rr1.registrov[i+1];
            }
            for (int i = 0; i < rr1.sizev; i++) {
                rr1.registrov[i] = tmp1[i];
            };
            rr1.registrov[18] = r1;
        }
        for (int i = 0; i < 64; i++) {
            r2 = rr2.registrov[rr2.vpolinomio[0]];
            for (int j = 1; j < rr2.sizep; j++) {
                r2 = r2^rr2.registrov[rr2.vpolinomio[j]];
            }
            r2 = r2^clave[i];
            int tmp2[22];
            tmp2[21] = 0;
            for (int i = 0; i < 22; i++) {
                tmp2[i] = rr2.registrov[i+1];
            }
            for (int i = 0; i < 22; i++) {
                rr2.registrov[i] = tmp2[i];
            }
            //despl(registro1, registro2, registro3, 2);
            rr2.registrov[21] = r2;
        }
        for (int i = 0; i < 64; i++) {
            r3 = rr3.registrov[rr3.vpolinomio[0]];
            for (int j = 1; j < rr3.sizep; j++) {
                r3 = r3^rr3.registrov[rr3.vpolinomio[j]];
            }
            r3 = r3^clave[i];
            int tmp3[23];
            tmp3[22] = 0;
            for (int i = 0; i < 23; i++) {
                tmp3[i] = rr3.registrov[i+1];
            }
            for (int i = 0; i < 23; i++) {
                rr3.registrov[i] = tmp3[i];
            }
            //despl(registro1, registro2, registro3, 3);
            rr3.registrov[22] = r3;
        }
        cout << "clave inicializada." << endl;
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////mostrar por pantalla////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        imprimir(rr1,rr2,rr3);
        //PASO 3
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////introducir frame_number/////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        r1 = 0,r2 = 0,r3 = 0;
        for (int i = 0; i < 22; i++) {
            r1 = rr1.registrov[rr1.vpolinomio[0]];
            
            for (int j = 1; j < rr1.sizep; j++) {
                r1 = r1^rr1.registrov[rr1.vpolinomio[j]];
            }
            r1 = r1^frame_number[i];
            int tmp1[19];
            tmp1[18] = 0;
            for (int i = 0; i < rr1.sizev; i++) {
                tmp1[i] = rr1.registrov[i+1];
            }
            for (int i = 0; i < rr1.sizev; i++) {
                rr1.registrov[i] = tmp1[i];
            };
            rr1.registrov[18] = r1;
            
            
            r2 = rr2.registrov[rr2.vpolinomio[0]];
            for (int j = 1; j < rr2.sizep; j++) {
                r2 = r2^rr2.registrov[rr2.vpolinomio[j]];
            }
            r2 = r2^frame_number[i];
            int tmp2[22];
            tmp2[21] = 0;
            for (int i = 0; i < 22; i++) {
                tmp2[i] = rr2.registrov[i+1];
            }
            for (int i = 0; i < 22; i++) {
                rr2.registrov[i] = tmp2[i];
            }
            rr2.registrov[21] = r2;
            
            
            r3 = rr3.registrov[rr3.vpolinomio[0]];
            for (int j = 1; j < rr3.sizep; j++) {
                r3 = r3^rr3.registrov[rr3.vpolinomio[j]];
            }
            r3 = r3^frame_number[i];
            int tmp3[23];
            tmp3[22] = 0;
            for (int i = 0; i < 23; i++) {
                tmp3[i] = rr3.registrov[i+1];
            }
            for (int i = 0; i < 23; i++) {
                rr3.registrov[i] = tmp3[i];
            }
            rr3.registrov[22] = r3;
        }
        cout << "Frame number introducido." << endl;
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////mostrar por pantalla////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        imprimir(rr1,rr2,rr3);
        //PASO 4
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////Mezcla de Bits//////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        int resultado[3];
        r1 = 0,r2 = 0,r3 = 0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 3 ; j++) {
                resultado[j] = 0;
            }
            
            funcion_mayoria(rr1.registrov[rr1.bit_clock], rr2.registrov[rr2.bit_clock], rr3.registrov[rr3.bit_clock], resultado);
            
            if (resultado[0] == 1) {
                r1 = rr1.registrov[rr1.vpolinomio[0]];
                for (int j = 1; j < rr1.sizep; j++) {
                    r1 = r1^rr1.registrov[rr1.vpolinomio[j]];
                }
                int tmp1[19];
                tmp1[18] = 0;
                for (int i = 0; i < rr1.sizev; i++) {
                    tmp1[i] = rr1.registrov[i+1];
                }
                for (int i = 0; i < rr1.sizev; i++) {
                    rr1.registrov[i] = tmp1[i];
                };
                rr1.registrov[18] = r1;
            }
            
            if (resultado[1] == 1) {
                r2 = rr2.registrov[rr2.vpolinomio[0]];
                for (int j = 1; j < rr2.sizep; j++) {
                    r2 = r2^rr2.registrov[rr2.vpolinomio[j]];
                }
                int tmp2[22];
                tmp2[21] = 0;
                for (int i = 0; i < 22; i++) {
                    tmp2[i] = rr2.registrov[i+1];
                }
                for (int i = 0; i < 22; i++) {
                    rr2.registrov[i] = tmp2[i];
                }
                rr2.registrov[21] = r2;
            }
            
            if (resultado[2] == 1) {
                r3 = rr3.registrov[rr3.vpolinomio[0]];
                for (int j = 1; j < rr3.sizep; j++) {
                    r3 = r3^rr3.registrov[rr3.vpolinomio[j]];
                }
                int tmp3[23];
                tmp3[22] = 0;
                for (int i = 0; i < 23; i++) {
                    tmp3[i] = rr3.registrov[i+1];
                }
                for (int i = 0; i < 23; i++) {
                    rr3.registrov[i] = tmp3[i];
                }
                rr3.registrov[22] = r3;
            }
            
            
        }
        cout << "Realizada la mezcla de bits." << endl;
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////mostrar por pantalla////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        imprimir(rr1,rr2,rr3);
        //PASO 5
        ////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////Generar secuencia cifrante////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        r1 = 0,r2 = 0,r3 = 0;
        for (int i = 0; i < 228; i++) {
            
            for (int j = 0; j < 3 ; j++) {
                resultado[j] = 0;
            }
            int medio = 0;
            medio = rr2.registrov[0] ^ rr3.registrov[0];
            secuencia_cifrante[i] = rr1.registrov[0] ^ medio;
            funcion_mayoria(rr1.registrov[rr1.bit_clock], rr2.registrov[rr2.bit_clock], rr3.registrov[rr3.bit_clock], resultado);
            
            if (resultado[0] == 1) {
                r1 = rr1.registrov[rr1.vpolinomio[0]];
                for (int j = 1; j < rr1.sizep; j++) {
                    r1 = r1^rr1.registrov[rr1.vpolinomio[j]];
                }
                //r1 = r1^frame_number[i];
                int tmp1[19];
                tmp1[18] = 0;
                for (int i = 0; i < rr1.sizev; i++) {
                    tmp1[i] = rr1.registrov[i+1];
                }
                for (int i = 0; i < rr1.sizev; i++) {
                    rr1.registrov[i] = tmp1[i];
                };
                rr1.registrov[18] = r1;
                
                //}
            }
            
            if (resultado[1] == 1) {
                //for (int i = 0; i < 22; i++) {
                r2 = rr2.registrov[rr2.vpolinomio[0]];
                for (int j = 1; j < rr2.sizep; j++) {
                    r2 = r2^rr2.registrov[rr2.vpolinomio[j]];
                }
                //r2 = r2^frame_number[i];
                int tmp2[22];
                tmp2[21] = 0;
                for (int i = 0; i < 22; i++) {
                    tmp2[i] = rr2.registrov[i+1];
                }
                for (int i = 0; i < 22; i++) {
                    rr2.registrov[i] = tmp2[i];
                }
                //despl(registro1, registro2, registro3, 2);
                rr2.registrov[21] = r2;
                //}
            }
            
            
            if (resultado[2] == 1) {
                //for (int i = 0; i < 22; i++) {
                r3 = rr3.registrov[rr3.vpolinomio[0]];
                for (int j = 1; j < rr3.sizep; j++) {
                    r3 = r3^rr3.registrov[rr3.vpolinomio[j]];
                }
                //r3 = r3^frame_number[i];
                int tmp3[23];
                tmp3[22] = 0;
                for (int i = 0; i < 23; i++) {
                    tmp3[i] = rr3.registrov[i+1];
                }
                for (int i = 0; i < 23; i++) {
                    rr3.registrov[i] = tmp3[i];
                }
                //despl(registro1, registro2, registro3, 3);
                rr3.registrov[22] = r3;
            }
            /*cout << "REGISRO 2: ";
             for (int i = 0; i < 22; i++) {
             cout << rr2.registrov[i];
             }
             cout << endl;
             cout << "REGISRO 3: ";
             for (int i = 0; i < 23; i++) {
             cout << rr3.registrov[i];
             }
             cout << endl;
             cout << "i: " << i << " , rr2.size: " << rr2.sizev << " , rr3.size: " << rr3.sizev << endl;*/
        }
        ////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////mostrar por pantalla////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////
        imprimir(rr1,rr2,rr3);
        
        cout << "SECUENCIA CIFRANTE: " << endl;
        for (int i = 0; i < 228; i++) {
            cout << secuencia_cifrante[i];
        }
        cout << endl;
        cout << endl;
    }
    else if (opcion == 2) {
        //SEMILLAS
        int rm1[] = {1,0,0,1,0,0,0,1,0,0,0,1,1,0,1,0,0,0,1};
        int rm2[] = {0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0};
        int rm3[] = {1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1};
        //INTRODUCIR SEMILLAS EN LOS REGISTROS
        for (int i = 0 ; i < rr1.sizev; i++) {
            rr1.registrov[i] = rm1[i];
        }
        for (int i = 0 ; i < rr2.sizev; i++) {
            rr2.registrov[i] = rm2[i];
        }
        for (int i = 0 ; i < rr3.sizev; i++) {
            rr3.registrov[i] = rm3[i];
        }
        
        int resultado[3];
        int r1 = 0,r2 = 0,r3 = 0;
        for (int i = 0; i < 6; i++) {
            cout << endl;
            imprimir(rr1,rr2,rr3);
            
            for (int j = 0; j < 3 ; j++) {
                resultado[j] = 0;
            }
            /////////////////// XOR de los últimos elementos para calcular la secuencia cifrante
            int medio = 0;
            medio = rr2.registrov[0] ^ rr3.registrov[0];
            secuencia_cifrante[i] = rr1.registrov[0] ^ medio;
            cout << "Secuencia Cifrante: "<< secuencia_cifrante[i] << endl;
            ////////////////////////////////////////////////
            //Cálculo de la función mayoría
            funcion_mayoria(rr1.registrov[rr1.bit_clock], rr2.registrov[rr2.bit_clock], rr3.registrov[rr3.bit_clock], resultado);
            ////////////////////////////////////////////////
            cout << "Se mueven los registros: ";
            if (resultado[0] == 1) {
                cout << " 1,";
                //XOR de cada uno de los elementos dados por el polinomio
                r1 = rr1.registrov[rr1.vpolinomio[0]];
                for (int j = 1; j < rr1.sizep; j++) {
                    r1 = r1^rr1.registrov[rr1.vpolinomio[j]];
                }
                ////////////////////////////////////////////////
                //Se ruedan todos los elementos del vector
                int tmp1[19];
                tmp1[18] = 0;
                for (int i = 0; i < rr1.sizev; i++) {
                    tmp1[i] = rr1.registrov[i+1];
                }
                for (int i = 0; i < rr1.sizev; i++) {
                    rr1.registrov[i] = tmp1[i];
                };
                ////////////////////////////////////////////////
                //se pone el resultado de el XOR de los elementos dados por el polinomio en la última posición.
                rr1.registrov[18] = r1;
            }
            if (resultado[1] == 1) {
                cout << " 2,";
                r2 = rr2.registrov[rr2.vpolinomio[0]];
                for (int j = 1; j < rr2.sizep; j++) {
                    r2 = r2^rr2.registrov[rr2.vpolinomio[j]];
                }
                int tmp2[22];
                tmp2[21] = 0;
                for (int i = 0; i < 22; i++) {
                    tmp2[i] = rr2.registrov[i+1];
                }
                for (int i = 0; i < 22; i++) {
                    rr2.registrov[i] = tmp2[i];
                }
                rr2.registrov[21] = r2;
            }
            if (resultado[2] == 1) {
                cout << " 3.";
                r3 = rr3.registrov[rr3.vpolinomio[0]];
                for (int j = 1; j < rr3.sizep; j++) {
                    r3 = r3^rr3.registrov[rr3.vpolinomio[j]];
                }
                int tmp3[23];
                tmp3[22] = 0;
                for (int i = 0; i < 23; i++) {
                    tmp3[i] = rr3.registrov[i+1];
                }
                for (int i = 0; i < 23; i++) {
                    rr3.registrov[i] = tmp3[i];
                }
                rr3.registrov[22] = r3;
            }
            cout << endl;
        }
        //imprimir(rr1,rr2,rr3);
        cout << endl << endl;
        cout << "SECUENCIA CIFRANTE: " << endl;
        for (int i = 0; i < 228; i++) {
            cout << secuencia_cifrante[i];
        }
        cout << endl;
        cout << endl;
    }
}

