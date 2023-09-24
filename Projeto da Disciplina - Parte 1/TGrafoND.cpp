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
#include "TGrafoND.h"
#include <limits>
#include <locale.h>
#include <fstream>

using namespace std;

TGrafoND::TGrafoND(int n){
    // No inicio dos tempos nao ha arestas e tipo do grafo é constante
    this->n = n;
    this->tipoGrafo = 2;
    this->m = 0;
  

    this->porcentagemDoenca = 1.0;
  
    // aloca da matriz do TGrafo
    float **adjac = new float*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new float[n];
    adj = adjac;
  
    // Inicia a matriz com zeros (Ex3. agora com 'infinitos')
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j]= INF;

}

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafoND::~TGrafoND(){
	n = 0;
	m = 0;
	delete [] *adj;
	cout << "espa�o liberado";
}

float TGrafoND::getPorcentagemDoenca(){
  return porcentagemDoenca;
}

int TGrafoND::getn(){
  return n;
}

int TGrafoND::getm(){
  return m;
}

int TGrafoND::getTipoGrafo(){
  return tipoGrafo;
}

void TGrafoND::setPorcentagemDoenca(float novaPorcentagem){
  porcentagemDoenca = novaPorcentagem;
}

void TGrafoND::setm(int newM){
  m = newM;
}

void TGrafoND::insereConexao( int v, int w, float valor){
    // testa se nao temos a aresta
    if(adj[v][w] == INF ){
        adj[v][w] = valor * porcentagemDoenca;
        adj[w][v] = valor * porcentagemDoenca;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafoND::removeConexao(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] != INF ){
        adj[v][w] = INF;
        adj[w][v] = INF;
        m--; // atualiza qtd arestas
    }
}

// remove um vertice da matriz
void TGrafoND::removeVertice(int vertice){
  for(int i = 0;i < n;i++){
    if(adj[vertice][i] != INF){
      m--;
    }
  }

  float** nova_matriz = new float*[n-1];
    for (int i = 0; i < (n-1); i++) {
        nova_matriz[i] = new float[n-1];
    }
  
  if(vertice == (n-1)){
    
   for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-1; j++) {
          nova_matriz[i][j] = adj[i][j];
        }
    }

  delete [] *adj; //talvez ainda tenha vazemento de memoria e tenha q retirar linha por linha
  adj = nova_matriz;
  } else{
   for(int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-1; j++) {
        if(i >= vertice && j >= vertice){
          nova_matriz[i][j] = adj[i+1][j+1];
        } else if(j >= vertice){
          nova_matriz[i][j] = adj[i][j+1];
        } else if(i >= vertice){
          nova_matriz[i][j] = adj[i+1][j];
        } else{
          nova_matriz[i][j] = adj[i][j];
        }
      }
    }
    delete[] *adj;
    adj = nova_matriz;
  }
  n = n-1;
}

void TGrafoND::show(){
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;

    // Largura para a formatacao do print
    int larguraCampo = 7;

    cout << std::setw(larguraCampo) << "  ";
    for (int i = 0; i < n; i++) {
        cout << std::setw(larguraCampo) << "[" << i << "]";
    }
    cout << std::endl;

    for (int i = 0; i < n; i++) {
        // Índice do vértice
        cout << std::setw(larguraCampo) << "[" << i << "]";
        
        for (int w = 0; w < n; w++) {
            // Use std::setw para definir a largura do campo
            cout << std::setw(larguraCampo) << std::fixed << std::setprecision(2) << adj[i][w];
        }
        cout << endl; // Mude de linha para a próxima linha da matriz
    }
    cout <<"\nfim da impressao do grafo." << endl;

}

int TGrafoND::completo(){
  if(n == (m * (m - 1)) / 2){
    cout << "Eh completo";
    return 1;
  }

  cout << "NAO eh completo";
  return 0;
}

float TGrafoND::complemento(){
  float **aux;
  float **auxi = new float*[n];
    for(int i = 0; i < n; i++)
    	auxi[i]= new float[n];
    aux = auxi;
    // Inicia a matriz com zeros (Ex3. agora com 'infinitos')
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			aux[i][j]= INF;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(adj[i][j] == INF && i != j){
        aux[i][j] = 1.0;
      }
    }
  }

  return 1.0; //precisa mudar para retornar a matriz gerada
}

int TGrafoND::inDegree(int v){
  int count = 0;
  for(int i = 0; i < n; i++){
    if(adj[i][v] != INF){
      count++;
    }
  }
  return count;
}

int TGrafoND::outDegree(int v){
  int count = 0;
  for(int i = 0; i < n; i++){
    if(adj[v][i] != INF){
      count++;
    }
  }
  return count;
}

int TGrafoND::conexidade(){
  for(int i = 0; i < n; i++){
   if(outDegree(i) == 0 && inDegree(i) == 0){
     cout << "Desconexo";
     return 1;
   }
  }
  cout << "Conexo";
  return 0;
}

void TGrafoND::aumentaMatriz(){
  float** nova_matriz = new float*[n+1];
    for (int i = 0; i < (n+1); i++) {
        nova_matriz[i] = new float[n+1];
    }

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          nova_matriz[i][j] = adj[i][j];
        }
    }

  for(int i = 0; i < (n + 1); i++){
    nova_matriz[n][i] = INF;
    nova_matriz[i][n] = INF;
  }

  delete [] *adj; //talvez ainda tenha vazemento de memoria e tenha q retirar linha por linha
  adj = nova_matriz;
  n = n+1;
}

float TGrafoND::acessarPosicao(int v, int w)
{
  return adj[v][w];
}