/****************
Mauricio Ivan Cortes Garcia A00816689
Victor Elizalde Muñoz A00817586
Tarea 8 - Problema 2
Analisis y Diseño de Algoritmos
Prof. Roman Martinez
****************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>

using namespace std;

int valorLetra(char letra)
{

    char aux = tolower(letra);
    return aux;
}

void PalabraArreglada(string &palindromo)
{
    string Aux;

    for(int i = 0; i < palindromo.length(); i++)
    {
        if(valorLetra(palindromo[i]) > 96 && valorLetra(palindromo[i] < 123))
        {
            Aux += toupper(palindromo[i]);
        }
    }

    palindromo = Aux;
}

void NumLetras(map<char, int> &myMap, string PalabraArreglada)
{
    for(int i = 0; i < PalabraArreglada.length(); i++)
    {
        if(myMap[PalabraArreglada[i]] == NULL)
        {
            myMap[PalabraArreglada[i]] = 1;
        }
        else
        {
            myMap[PalabraArreglada[i]]++;
        }
    }
}

void Setup(map<char, int> myMap, string &PalabraArreglada)
{
    string Aux;
    int Impar = 0;

    if(PalabraArreglada.length()%2 == 0)
    {
        for(map<char, int>::iterator it = myMap.begin(); it != myMap.end(); it++)
        {
            if((it -> second)%2 != 0)
            {
                Impar++;
            }
        }

        if(Impar == 0)
        {
            for(map<char, int>::iterator itAux = myMap.begin(); itAux != myMap.end(); itAux++)
            {
                for(int i = itAux -> second/2; i > 0; i--)
                {
                    Aux += itAux -> first;
                }
            }
        }
    }
    else
    {
        map<char, int>::iterator itImpar;

        for(map<char, int>::iterator it = myMap.begin(); it != myMap.end(); it++)
        {
            if((it -> second)%2 != 0)
            {
                Impar++;
                itImpar = it;
            }
        }

        if(Impar == 1)
        {
            for(map<char, int>::iterator itAux = myMap.begin(); itAux != myMap.end(); itAux++)
            {
                if(itAux == itImpar)//Cuando haya el impar que pivotea
                {
                    for(int i = (itImpar -> second - 1)/2; i > 0; i--)
                    {
                        Aux += itImpar -> first;
                    }
                }
                else
                {
                    for(int i = itAux -> second/2; i > 0; i--)
                    {
                        Aux += itAux -> first;
                    }
                }
            }
        }
    }

    if(Aux.length() != 0)
    {
        PalabraArreglada = Aux;
    }
    else
    {
        PalabraArreglada = "0";
    }
}

int main()
{
    vector<int> Permutaciones;

    string palindromo;
    getline(cin, palindromo);

    while(palindromo != "")
    {
        PalabraArreglada(palindromo);
        if(palindromo.length() != 0)
        {
            map<char, int> myMap;
            NumLetras(myMap,palindromo);

            Setup(myMap, palindromo);

            if(palindromo != "0")
            {
                int iArrFactoriales[palindromo.length() + 1];
                iArrFactoriales[0] = 1;

                for(int i = 1; i < palindromo.length() + 1; i++)
                {
                    iArrFactoriales[i] = iArrFactoriales[i-1]*i;
                }

                int Numerador = iArrFactoriales[palindromo.length()];

                map<char, int> myMapPerms;
                NumLetras(myMapPerms,palindromo);

                int Denominador = 1;

                for(map<char, int>::iterator it = myMapPerms.begin(); it != myMapPerms.end(); it++)
                {
                    Denominador *= iArrFactoriales[it -> second];
                }

                Permutaciones.push_back(Numerador/Denominador);
            }
            else
            {
                Permutaciones.push_back(0);
            }
        }
        else
        {
            Permutaciones.push_back(1);
        }

        getline(cin, palindromo);
    }

    for(int i = 0; i < Permutaciones.size(); i++)
    {
        cout << Permutaciones[i] << endl;
    }

    return 0;
}
