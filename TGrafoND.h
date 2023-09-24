/*
Implementa�o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza�o de um grafo dirigido.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

class TGrafoND{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
    float porcentagemDoenca;
		float **adj; //matriz de adjac�ncia
	public:
		TGrafoND( int n);
    float getPorcentagemDoenca();
    void setPorcentagemDoenca(float novaPorcentagem);
		void insereConexao(int v, int w, float valor);
		void removeConexao(int v, int w);
		void show();
//-------------------------------- Minhas funcs
    int completo();
    float complemento();
    int inDegree(int v);
    int outDegree(int v);
    int conexidade();
    void aumentaMatriz();
    void retiraVertice(int vertice);
//-------------------------------- Borel funcs
    int getn();
    int getm();
    float acessarPosicao(int v, int w);
		~TGrafoND();		
};


#endif
