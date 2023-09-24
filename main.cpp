#include "TGrafoND.h"

/*
struct GrafoENomes {
    TGrafoND grafo;
    std::string* nomes;
};
*/

std::string* nomes;

TGrafoND leArquivo(){
    fstream file;
    string word, t, q, filename;
 
    // filename of the file
    filename = "grafo.txt";
 
    // opening file
    file.open(filename.c_str());

    file >> word;
    file >> word;

    int aux = stoi(word);
    int aux2;
    float auxf;
    string concatena;

    TGrafoND g(aux);
    nomes = new string[aux]; //Faz um vetor dinamico para os nomes. NAO ESQUECER DO DELETE[]

    for(int i = 0;i < aux;i++){
      file >> word;
      file >> concatena;
      file >> word;
      
      concatena +=" " + word;
      
      nomes[i] = concatena;
      
      //concatena = "";
    }

    file >> word;
    
    // extracting words from the file
    while (file >> word)
    {
      aux = stoi(word);
      file >> word;
      aux2 = stoi(word);
      file >> word;
      auxf = stof(word);

      g.insereConexao(aux, aux2, auxf);
    }
  
  //GrafoENomes resultado = {g, nomes};
    file.close();
    return g;
}

void exibeArquivo(){
    fstream file;
    string word, t, q, filename;
 
    // filename of the file
    filename = "grafo.txt";
 
    // opening file
    file.open(filename.c_str());

    file >> word;
    std::cout << "\n\nTipo do grafo: " << word;
    
    file >> word;
    std::cout << "\nNumero de vertices: " << word;

    int aux = stoi(word);

    std::cout << "\nAbaixo segue: <ID do vertice> [Espaco] <rotulo|nome>\n";
  
    for(int i = 0;i < aux;i++){
      file >> word;
      std::cout << word << " ";
      file >> word;
      std::cout << word << " ";
      file >> word;
      std::cout << word <<"\n";
    }

    file >> word;

    std::cout << "Numero de arestas: " << word
              << "\nAbaixo segue: <aresta> [espaco] <aresta> [espaco] <peso da aresta>\n";

    aux = stoi(word);
    for(int i = 0;i < aux;i++){
      file >> word;
      std::cout << word << " ";
      file >> word;
      std::cout << word << " ";
      file >> word;
      std::cout << word << "\n";
    }
    file.close();
}

void gravarArquivo(TGrafoND* g){
  ofstream file;
  string word, t, q, filename;

  filename = "grafo.txt";
  
  file.open(filename.c_str());
  if(file.is_open()){
    //colocar o primeiro item do txt
    file << "2" << endl;
    file << g->getn() << endl;
    for(int i=0; i < g->getn(); i++)
    {
      file << i << ' ' << nomes[i] << endl;
    }
    file << g->getm() << endl;

    for(int v=0; v < g->getn(); v++){
      for(int w=0; w < (v + 1); w++)
      {
        if(g->acessarPosicao(v,w) != std::numeric_limits<float>::infinity()){
          file << v << ' ' << w << ' ' << g->acessarPosicao(v, w) << endl;
        }
      }
    }
    
  }  
}


int main(){

  TGrafoND *grafo;
  
  char opcao;

  std::cout << "TEORIA DOS APERTOS DE MAO ~ VERSAO SAUDE\n";

  do{
    std::cout << "_________________________________________" 
              << "\nEscolha uma opcao:\n\n"
              << "a) Ler dados do arquivo.txt\n"
              << "b) Gravar dados no arquivo.txt\n"
              << "c) Inserir vertice\n"
              << "d) Inserir aresta\n"
              << "e) Remover vertice\n"    
              << "f) Remover aresta\n"
              << "g) Mostrar conteudo do arquivo\n"
              << "h) Mostrar Grafo\n"
              << "i) Apresentar a conexidade do grafo\n"
              << "z) Encerrar aplicacao\n\n";

    std::cout << "Sua opcao: ";
    std::cin >> opcao;

    switch(opcao){
      case 'a': {
        grafo = new TGrafoND (leArquivo()); 
        break;
      }
      
      case 'b': {
        gravarArquivo(grafo);
        break;
      }
        
      case 'c':{
        grafo->aumentaMatriz();
        string* vetAux = new string[grafo->getn()];
        string nomeNovo;
        string auxnome;
        std::cout << "Insira o nome da pessoa nova no seguinte formato: <Nome> [Espaco] <Sobrenome>";
        std::cin >> nomeNovo;
        std::cin >> auxnome;
        nomeNovo += " " + auxnome;
        //std::cout << "\n\nNome: " << nomeNovo << " vet: " << vetAux[(grafo->getn() - 1)] << "\n\n";
        for(int i = 0;i < (grafo->getn() - 1);i++){
          vetAux[i] = nomes[i];
        }

        delete[] nomes;

        nomes = vetAux;
        vetAux = nullptr;

        nomes[(grafo->getn() - 1)] = nomeNovo;
        
        break;
      }

      case 'd':{
        int aux, aux2;
        float aux3;

        std::cout << "Insira o ID de uma pessoa";
        std::cin >> aux;

        std::cout << "Insira o ID da outra pessoa";
        std::cin >> aux2;

        std::cout << "Insira a chance destas pessoas de encontrarem (0 a 100)";
        std::cin >> aux3;
        
        grafo->insereConexao(aux, aux2, aux3);
        break;
          }

      case 'e':{
        std::cout << "\n\nInsira o ID do vértice que deseja retirar ";
        int vertice;
        std::cin >> vertice;
       
        grafo->retiraVertice(vertice);

        string* vetAux = new string[grafo->getn()];
        
        if(vertice == grafo->getn()){
          for(int i = 0;i < grafo->getn();i++){
            vetAux[i] = nomes[i];
          }

        delete[] nomes;

        nomes = vetAux;
        vetAux = nullptr;          
        } else{
          for(int i = 0;i < grafo->getn();i++){
            if(i < vertice){
              vetAux[i] = nomes[i];
            } else{
              vetAux[i] = nomes[i+1];
            }
          }
          delete[] nomes;
          nomes = vetAux;
          vetAux = nullptr;          
        }        
        break;
      }  

      case 'f':{
        int aux, aux2;
        
        std::cout << "Insira um dos pontos da aresta.";
        std::cin >> aux;
        
        std::cout << "Insira o outro ponto da aresta.";
        std::cin >> aux2;
        
        grafo->removeConexao(aux, aux2);
        break;
      }

      case 'g':{
        exibeArquivo();
        break;
     }

      case 'h':
        grafo->show();
        break;

      case 'i':{
        grafo->conexidade();
        break;
      }
    
    }
    
  } while(opcao != 'z');

  if(nomes){
    delete grafo;
    delete[] nomes;
  }
    return 0;
}