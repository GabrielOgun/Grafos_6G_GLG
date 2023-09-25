/*
//-----------------Projeto Parte 1 ------------------//
Implementacao  Teoria de Graus de Separacao 
- Transmissao Doenças,usando Matriz de Adjacência e 
métodos para utilizaçao de um grafo Não Dirigido.
//---------------------------------------------------//

Profº IVAN CARLOS ALCANTARA DE OLIVEIRA
Integrantes:
  Gabriel Kury Fonseca - 32153848
  Gabriel Marques Gonçalves Almeida - 32066724
  Leoanrdo Borim Silva - 32154410
*/

#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

const float INF = std::numeric_limits<float>::infinity();

class TGrafoND{
	private:
		int n; // quantidade de vertices
		int m; // quantidade de arestas
	    int tipoGrafo; // Armazena a o tipo do grafo
	    float porcentagemDoenca; // Porcentagem que define a capacidade da doenca ser transmitida
		float **adj; //matriz de adjacencia
	public:
		TGrafoND( int n);
	    float getPorcentagemDoenca();
	    int getn();
	    int getm();
	    int getTipoGrafo();
	    void setPorcentagemDoenca(float novaPorcentagem);
	    void setm(int m);
		void insereConexao(int v, int w, float valor);
		void removeConexao(int v, int w);
	    void removeVertice(int vertice);
		void show();
	    int completo();
	    float complemento();
	    int inDegree(int v);
	    int outDegree(int v);
	    int conexidade();
	    void aumentaMatriz();
	    float acessarPosicao(int v, int w);
	~TGrafoND();		
};


#endif
