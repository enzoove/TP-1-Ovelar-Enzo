/*
1. Emita un listado donde para cada cliente liste los tipos de producto tal que la cantidad total de
kilos transportados es mayor a 13000.
2. Para el cliente con mayor cantidad tipos de productos que hayan superado 13000 kg en el punto
anterior, emita un listado con nombre de tipo de producto y total de kilómetros recorridos,
ordenado por total de kilómetros en forma ascendente.
Nota: No alterar el vector de nombres.
3. Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
informe cuantas entregas se hicieron para ese tip
o de producto (sin importar para que cliente).
*/

#include <iostream>
#include <fstream>
using namespace std;

const int dimClientes = 8; // Cantidad de clientes
const int dimProductos = 5; // Cantidad de productos

//Funciones ( Estan debajo del main )
void Lista_Peso_Superior_A_Parametro( float Peso[][5], string Clientes[], string Productos[] ,int &codMayor, float parametro );
void Km_Recorridos( float Distancia[][5], float KmProd[] ,string Productos[], int codMayor, int &codMayorKM );
int Cantidad_Entregas_Producto( int Entregas[][5], int codProducto );
int main()
{
    string Clientes[dimClientes]; // Nombres de los clientes
    string Productos[dimProductos]; // Nombres de los productos
    float Peso[dimClientes][dimProductos]; // Peso de las entregas segun combinacion producto-cliente
    float Distancia[dimClientes][dimProductos]; // Distancia de las entregas segun combinacion producto-cliente
    float Km_Productos_De_Cliente[dimProductos]; // Km recorridos por tipo de producto de un cliente en especifico
    int CantEntregas[dimClientes][dimProductos];// Entregas de cada producto por cliente
    ifstream Leer1, Leer2; // Para abrir los archivos de texto
    int codClienteMayor; // Punto 2
    int codProductoMayor;// Punto 3
    int i,j; float aux;// iteradores/auxiliares

    Leer1.open( "Datos.txt" );
    if( !Leer1 )
    {
        cout << "\aERROR: No se pudo abrir el archivo \"Datos.txt\"" << endl;
        return 1;
    }
    Leer2.open( "Nombres.txt" );
    if( !Leer2 )
    {
        cout << "\aERROR: No se pudo abrir el archivo \"Datos.txt\"" << endl;
        return 1;
    }

    for( i=0; i<dimClientes; i++ )
    {
        for( j=0; j<dimProductos; j++ )
        {
            Peso[i][j] = 0;
            Distancia[i][j] = 0;
            CantEntregas[i][j] = 0;
        }
    }


    while( !Leer1.eof() )
    {
        Leer1 >> i; Leer1 >> j;
        Leer1 >> aux;
        Peso[i][j] += aux;
        Leer1 >> aux;
        Distancia[i][j] += aux;
        CantEntregas[i][j] += 1;
    }
    Leer1.close();

    i=0; j=0;
    while( i<dimClientes )
    {
        Leer2 >> Clientes[i];
        i++;
    }
    while( j<dimProductos )
    {
        Leer2 >> Productos[j];
        j++;
    }
    Leer2.close();

    //1
    Lista_Peso_Superior_A_Parametro( Peso, Clientes, Productos, codClienteMayor, 13000 );

    //2
    cout << "\nKm Recorridos por producto del cliente " << Clientes[codClienteMayor] << ":" << endl;
    Km_Recorridos( Distancia, Km_Productos_De_Cliente, Productos, codClienteMayor, codProductoMayor );

    //3
    cout << "\nCantidad de entregas de " << Productos[codProductoMayor] << ": " << Cantidad_Entregas_Producto( CantEntregas, codProductoMayor ) << endl;

    return 0;
}
//Funciones
void Lista_Peso_Superior_A_Parametro( float Peso[][5], string Clientes[], string Productos[] ,int &codMayor, float parametro )
{
    int contarMax = 0;
    int max = 0;
    int i,j;
    codMayor = 0;
    cout << "Parametro actual: " << parametro << endl;
    cout << "Productos que superan el parametro de kilos transportados por cliente: " << endl;
    for( i=0;i<dimClientes; i++  )
    {
        cout << Clientes[i] << ":\t";
        for( j=0; j<dimProductos; j++ )
        {
            if( Peso[i][j] > parametro )
            {
                cout << Productos[j] << " - ";
                contarMax++;
            }

        }
        if( contarMax > max )
            {
                max = contarMax;
                codMayor = i;
            }
        contarMax = 0;
        cout << endl;
    }
}
void Km_Recorridos( float Distancia[][5], float KmProd[] ,string Productos[], int codMayor, int &codMayorKM )
{
    int i,j,auxi;
    float auxf;
    int pos[dimProductos];//Guarda el codigo de los nombres de los productos

    for( i=0; i< dimProductos; i++ )
    {
        KmProd[i] = Distancia[codMayor][i];
        pos[i] = i;
    }
   for( i=0; i<dimProductos; i++ )
    {
        auxf = KmProd[i];
        auxi = pos[i];
        j = i;

        while( j>0 && KmProd[j-1]>auxf )
        {
            KmProd[j] = KmProd[j-1];
            pos[j] = pos[j-1];
            j--;
        }
        KmProd[j] = auxf;
        pos[j] = auxi;
    }

    for( i=0; i<dimProductos; i++ )
    {
        cout << Productos[pos[i]] << " " << KmProd[i] << endl;
        if( i == dimProductos-1 )
        {
            codMayorKM = pos[i];
        }
    }
}
int Cantidad_Entregas_Producto( int Entregas[][5], int codProducto )
{
    int cant = 0;
    for( int i=0; i<dimClientes; i++ )
    {
        cant += Entregas[i][codProducto];
    }
    return cant;
}
