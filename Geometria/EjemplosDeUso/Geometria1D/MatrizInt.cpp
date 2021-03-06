//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices densas de valores enteros                            //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// P�gina:   http://www.mmc.igeofcu.unam.mx/acl                                             //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los t�rminos de la Licencia P�blica General de GNU seg�n es                         //
// publicada por la Free Software Foundation, bien de la versi�n 2 de                       //
// dicha Licencia o bien (seg�n su elecci�n) de cualquier versi�n                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea �til, pero SIN                   //
// NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. V�ase la                        //
// Licencia P�blica General de GNU para m�s detalles.                                       //
//                                                                                          //
// Deber�a haber recibido una copia de la Licencia P�blica General junto                    //
// con este programa. Si no ha sido as�, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#include <stdlib.h>
#include "MatrizInt.hpp"


// Constructor de la clase
// Genera una matriz del tama�o expecificado por el n�mero renglones y de columnas e inicializado al valor indicado
// @param ren N�mero de renglones de la matriz
// @param col N�mero de columnas de la matriz
// @param nmb Nombre de la matriz
// @param val Valor por omisi�n para inicializar la matriz
MatrizInt::MatrizInt(const int ren, const int col, const char *nmb, int val)
{
   int i, j;
   M = new int *[ren];
   if (!M) faltaMemoria();
   for (i = 0; i < ren; i++)
   {
      M[i] = new int[col];
      if (!M[i]) faltaMemoria();
   }

   Col = col;
   Ren = ren;
   Tipo_Matriz = MATRIZ_ENTERA_DENSA;
   asignaNombre(nmb);

   // inicializa
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) M[i][j] = val;
   }
}

/// Libera la memoria solicitada para la matriz
void MatrizInt::liberaMemoria(void)
{
   if (M)
   {
      for (int i = 0; i < Ren; i++)
      {
         delete []M[i];
         M[i] = NULL;
      }
      delete []M;
   }
   M = NULL;
}


// Inicializa la matriz al valor val indicado
// @param val Valor por omisi�n para inicializar la matriz
void MatrizInt::inicializa(const int val)
{
#ifdef DEPURAR
   // Revisa que la matriz este inicializada
   if (!M)
   {
      printf("Error la matriz no ha sido inicializada");
      return;
   }
#endif
   int i, j;
   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++) M[i][j] = val;
   }
}

#ifdef DEPURAR

// Asigna el valor indicado en el renglo y columna solicitado
// @param ren Renglon
// @param col Columna
// @param val Valor
void MatrizInt::asigna(const int ren, const int col, const int val)
{
   if (ren < 0 || ren >= Ren || col < 0 || col >= Col)
   {
      printf("Error indices desbordados (%d, %d)\n", ren,col);
      exit(1);
   }
   M[ren][col] = val;
}


// Retorna el valor del renglon y columna solicitado
// @param ren Renglon
// @param col Columna
// @return Valor
int MatrizInt::retorna(const int ren, const int col)
{
   if (ren < 0 || ren >= Ren || col < 0 || col >= Col)
   {
      printf("Error indices desbordados (%d, %d)\n", ren,col);
      exit(1);
   }
   return M[ren][col];
}
#endif


// Retorna el m�ximo tama�o en todas las columnas que sean distintos de cero
// @return M�ximo tama�o de columnas ocupadas en la matriz
int MatrizInt::maximoTamanoColumnaOcupado(void)
{
   int i, j, k, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      k = 0;
      for (j = 0; j < columnas(); j++)
      {
         if (retorna(i,j) != 0) k ++;
      }
      if (k > max) max = k;
   }
   return max;
}


// Retorna el n�mero de entradas distintas de cero en la matriz
// @return N�mero de entradas distintas de cero en la matriz
int MatrizInt::entradasDistintasCero(void)
{
   int i, j, max = 0;
   for (i = 0; i < renglones(); i++)
   {
      for (j = 0; j < columnas(); j++)
      {
         if (retorna(i,j) != 0) max ++;
      }
   }
   return max;
}


// Visualiza la matriz
void MatrizInt::visualiza(void)
{
   visualizaInformacion();

   int i, j;
   Ctrl_visualizacion cv;

   for (i = 0; i < Ren; i++)
   {
      for (j = 0; j < Col; j++)
      {
         cv.visualiza(retorna(i,j));
      }
      printf("\n");
   }
   printf("\n");
}
