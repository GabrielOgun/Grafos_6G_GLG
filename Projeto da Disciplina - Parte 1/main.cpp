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

#include "TGrafoND.h"

const std::string arquivo = "grafo.txt";
std::string* nomes;

TGrafoND leArquivo(){
    fstream file;
    string word, t, q, filename;
  
    // Arquivo de entrada
    filename = arquivo;
  
    // Abrindo o arquivo
    file.open(filename.c_str());

    file >> word;
    file >> word;

    int aux = stoi(word);
    int aux2;
    float auxf;
    string concatena;

    TGrafoND g(aux);
    
    //Faz um vetor dinamico para os nomes.
    nomes = new string[aux]; 

    for(int i = 0;i < aux;i++){
      file >> word;
      file >> concatena;
      file >> word;
      
      concatena +=" " + word;
      
      nomes[i] = concatena;
      
    }

    file >> word;
    
    // Extraindo as arestas e os pesos
    while (file >> word)
    {
      aux = stoi(word);
      file >> word;
      aux2 = stoi(word);
      file >> word;
      auxf = stof(word);

      g.insereConexao(aux, aux2, auxf);
    }
  
    file.close();
    cout << "\n>>> Leitura Concluida com sucesso!\n";
    return g;
}

void exibeArquivo(){
    fstream file;
    string word, t, q, filename;

    filename = arquivo;
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

  filename = arquivo;
  
  file.open(filename.c_str());
  if(file.is_open()){
    
    file << g->getTipoGrafo() << endl;
    file << g->getn() << endl;
    for(int i=0; i < g->getn(); i++)
    {
      file << i << ' ' << nomes[i] << endl;
    }
    file << g->getm() << endl;

    for(int v=0; v < g->getn(); v++){
      for(int w=0; w < (v + 1); w++)
      {
        if(g->acessarPosicao(v,w) != INF){
          file << v << ' ' << w << ' ' << g->acessarPosicao(v, w) << endl;
        }
      }
    }
    cout << "\n>>> Dados gravados com sucesso!\n";
    
  }
  else{
    cout << "\n** Exececao encontrada: Arquivo nao encontrado **\n";
  }
}

int main(){

  TGrafoND *grafo;
  
  char opcao;

  std::cout << "\n**** TEORIA DOS GRAUS DE SEPARACAO ~ TRANSMISSAO DE DOENCAS ****\n";

  do{
    std::cout << "__________________________________________________________________" 
              << "\nEscolha uma opcao:\n\n"
              << "a) Ler dados do arquivo.txt\n"
              << "b) Gravar dados no arquivo.txt\n"
              << "c) Inserir Pessoa\n"
              << "d) Inserir Conexao\n"
              << "e) Remover Pessoa\n"    
              << "f) Remover Conexao\n"
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
        std::cout << "Insira o nome da pessoa nova no seguinte formato: <Nome> [Espaco] <Sobrenome>: ";
        std::cin >> nomeNovo;
        std::cin >> auxnome;
        nomeNovo += " " + auxnome;
        
        for(int i = 0;i < (grafo->getn() - 1);i++){
          vetAux[i] = nomes[i];
        }

        delete[] nomes;

        nomes = vetAux;
        vetAux = nullptr;

        nomes[(grafo->getn() - 1)] = nomeNovo;
        cout << "\n>>> Pessoa Adicionada ao grafo!\n";
        break;
      }

      case 'd':{
        int aux, aux2;
        float aux3;

        std::cout << "Insira o ID de uma pessoa: ";
        std::cin >> aux;

        std::cout << "Insira o ID da outra pessoa: ";
        std::cin >> aux2;

        std::cout << "Insira a chance destas pessoas de encontrarem (0 a 100): ";
        std::cin >> aux3;
        
        grafo->insereConexao(aux, aux2, aux3);
        cout << "\n>>> Conexao Adicionada!\n";
        break;
          }

      case 'e':{
        std::cout << "\n\nInsira o ID da pessoa que deseja retirar: ";
        int vertice;
        std::cin >> vertice;
       
        grafo->removeVertice(vertice);

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
        cout << "\n>>> Pessoa removida do grafo!\n";
        break;
      }  

      case 'f':{
        int aux, aux2;
        
        std::cout << "Insira o ID de uma das pessoas da conexao: ";
        std::cin >> aux;
        
        std::cout << "Insira o ID da outra pessoa da conexao: ";
        std::cin >> aux2;
        
        grafo->removeConexao(aux, aux2);
        cout << "\n>>> Conexao Removida!\n";
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

      default:
        if(opcao != 'z')
          cout << "\n>>> Entrada Inválida! Tente Novamente...\n";
    
    }
    
  } while(opcao != 'z');

  if(nomes){
    delete grafo;
    delete[] nomes;
  }

  cout << "\n>>> Fim do Programa!";
  return 0;
}
