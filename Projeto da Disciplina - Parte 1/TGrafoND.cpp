#include <iostream>
using namespace std;
#include "TGrafoND.h"
#include <limits>
#include <locale.h>
#include <fstream>



TGrafoND::TGrafoND( int n ){
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
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
			adj[i][j]= std::numeric_limits<float>::infinity();

}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafoND::~TGrafoND(){
	n = 0;
	m = 0;
	delete [] *adj;
	std::cout << "espa�o liberado";
}

float TGrafoND::getPorcentagemDoenca(){
  return porcentagemDoenca;
}

void TGrafoND::setPorcentagemDoenca(float novaPorcentagem){
  porcentagemDoenca = novaPorcentagem;
}

void TGrafoND::insereConexao( int v, int w, float valor){
    // testa se nao temos a aresta
    if(adj[v][w] == std::numeric_limits<float>::infinity() ){
        adj[v][w] = valor * porcentagemDoenca;
        adj[w][v] = valor * porcentagemDoenca;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafoND::removeConexao(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] != std::numeric_limits<float>::infinity() ){
        adj[v][w] = std::numeric_limits<float>::infinity();
        adj[w][v] = std::numeric_limits<float>::infinity();
        m--; // atualiza qtd arestas
    }
}

void TGrafoND::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            /*if(adj[i][w] == 1)
                std::cout << "Adj[" << i<< "," << w << "]= 1" << " ";
            else std::cout << "Adj[" << i<< "," << w << "]= 0" << " ";*/
          std::cout << "Adj[" << i<< "," << w << "]= " << adj[i][w] << " ";
    }
    cout <<"\nfim da impressao do grafo." << endl;

}

int TGrafoND::completo(){
  if(n == (m * (m - 1)) / 2){
    std::cout << "Eh completo";
    return 1;
  }

  std::cout << "NAO eh completo";
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
			aux[i][j]= std::numeric_limits<float>::infinity();

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(adj[i][j] == std::numeric_limits<float>::infinity() && i != j){
        aux[i][j] = 1.0;
      }
    }
  }

  return 1.0; //precisa mudar para retornar a matriz gerada
}



int TGrafoND::inDegree(int v){
  int count = 0;
  for(int i = 0; i < n; i++){
    if(adj[i][v] != std::numeric_limits<float>::infinity()){
      count++;
    }
  }
  return count;
}


int TGrafoND::outDegree(int v){
  int count = 0;
  for(int i = 0; i < n; i++){
    if(adj[v][i] != std::numeric_limits<float>::infinity()){
      count++;
    }
  }
  return count;
}


int TGrafoND::conexidade(){
  for(int i = 0; i < n; i++){
   if(outDegree(i) == 0 && inDegree(i) == 0){
     std::cout << "Desconexo";
     return 1;
   }
  }
  std::cout << "Conexo";
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
    nova_matriz[n][i] = std::numeric_limits<float>::infinity();
    nova_matriz[i][n] = std::numeric_limits<float>::infinity();
  }

  delete [] *adj; //talvez ainda tenha vazemento de memoria e tenha q retirar linha por linha
  adj = nova_matriz;
  n = n+1;
}

void TGrafoND::retiraVertice(int vertice){
  for(int i = 0;i < n;i++){
    if(adj[vertice][i] != std::numeric_limits<float>::infinity()){
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

//------------------------------------- Borel Funcs
int TGrafoND::getn(){
  return n;
}

int TGrafoND::getm(){
  return m;
}

float TGrafoND::acessarPosicao(int v, int w)
{
  return adj[v][w];
}