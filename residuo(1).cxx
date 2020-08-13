/*
 * residuo.cxx
 * 
 * Copyright 2016 Gabriel Vargas <gabreta@VmGabriel96>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

double timeval_diff(struct timeval *a, struct timeval *b)
{
    return
	(double)(a->tv_sec + (double)a->tv_usec/1000000) -
	(double)(b->tv_sec + (double)b->tv_usec/1000000);
}

class clavebits
{
   private: int x;
   public: 
        clavebits& operator=(int i)
        {
            x=i; return *this;
        }
        inline unsigned bits (int k, int j)
	{
            return (x>>k)&~(~0<<j);
	}
};
typedef clavebits tipoElemento;

void intercambio (tipoElemento * a, int posa,int posb)
{
    //posa = posicion de origen
    //posb = posicion de destino
    tipoElemento t=a[posb];
    a[posb]=a[posa];
    a[posa]=t;
}

void cambioresiduos(tipoElemento * a, int izq, int der, int b)
{
    int i,j;
    tipoElemento t;
    if (der>izq && b>0)
    {
        i= izq;
        j=der;
        while(j!=i)
        {
            while(!a[i].bits(b,1) && i<j)i++;
            while( a[j].bits(b,1) && j>i)j--;
            intercambio(a, i, j);
        }
        if (!a[i].bits(b,1)) j++;
        cambioresiduos(a, izq, j-1, b-1);
        cambioresiduos(a, j, der, b-1);
    }
}

void imprimir (int * a, int n)
{
    cout <<"[ ";
    for (int i=0;i<n;i++)
    {
	cout<<a[i]<<" ";
    }
    cout <<"]"<<endl;
}

void imprimircar (char * a, int n)
{
    cout <<"[ ";
    for (int i=0;i<n;i++)
    {
	cout<<a[i]<<" ";
    }
    cout <<"]"<<endl;
}

void llenarcar (tipoElemento * a, int n)
{
    int mat[32]={00001,00010,00011,00100,00101,00110,00111,01000,01001,01010,01011,01100,01101,01110,01111,10000,10001,10010,10011,10100,10101,10110,10111,11000,11001,11010,11011,11100,11101,11110,11111};
    for (int i=0;i<=n;i++)
    {
	a[i]=mat[(int)(rand()%25)];
    }
}

int main(int argc, char **argv)
{

    for (int n=50;n<=500;n+=10)
    {
	struct timeval t_ini, t_fin;
	double secs;
	tipoElemento * car = new tipoElemento[n];

	llenarcar(car,n);

	gettimeofday(&t_ini, NULL);
	cambioresiduos(car,0,n,5);
	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
    
	delete []car;

	cout<<"Time with "<<n<<" is "<<secs<<endl;
    }
    return 0;
}
