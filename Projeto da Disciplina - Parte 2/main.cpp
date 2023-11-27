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

const std::string arquivo = "grafoTeste02.txt";
std::string* nomes;

int idPessoa(TGrafoND *grafo);

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
              << "j) Apresentar a probabilidade de transmissao da doenca\n"
              << "k) Alterar a probabilidade de transmissao da doenca\n"
              << "l) Apresentar o ID de uma pessoa\n"
              << "m) Verificar se o Grafo é Euleriano\n"
              << "n) Apresentar Coloração do Grafo\n"
              << "o) Apresentar o caminho máximo\n"
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
        int aux, aux2, flag;
        float aux3;

        do{
            std::cout << "Insira 1 para inserir por ID ou 2 para inserir por nome: ";
            cin >> flag;
            cout << "\n";
        } while (flag != 1 && flag != 2);

        if(flag == 2){
            do{
                aux = idPessoa(grafo);
            } while (aux == -1);

            do{
                aux2 = idPessoa(grafo);
            } while (aux2 == -1);
        } else{
        std::cout << "Insira o ID de uma pessoa: ";
        std::cin >> aux;

        std::cout << "Insira o ID da outra pessoa: ";
        std::cin >> aux2;   
        }

        std::cout << "Insira a chance destas pessoas de encontrarem (0 a 100): ";
        std::cin >> aux3;

        grafo->insereConexao(aux, aux2, aux3);
        cout << "\n>>> Conexao Adicionada!\n";
        break;
          }

      case 'e':{
          int vertice, flag;

        do{
            std::cout << "Insira 1 para inserir por ID ou 2 para inserir por nome: ";
            cin >> flag;
            cout << "\n";
        } while (flag != 1 && flag != 2);

        if(flag == 2){
            do{
                vertice = idPessoa(grafo);
            } while(vertice == -1);
        } else{
            std::cout << "\n\nInsira o ID da pessoa que deseja retirar: ";
            std::cin >> vertice;
        }

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
        int aux, aux2, flag;

       do{
            std::cout << "Insira 1 para inserir por ID ou 2 para inserir por nome: ";
            cin >> flag;
            cout << "\n";
        } while (flag != 1 && flag != 2);

        if(flag == 2){
            do{
                aux = idPessoa(grafo);
            } while (aux == -1);

            do{
                aux2 = idPessoa(grafo);
            } while (aux2 == -1);
        } else{        
            std::cout << "Insira o ID de uma das pessoas da conexao: ";
            std::cin >> aux;

            std::cout << "Insira o ID da outra pessoa da conexao: ";
            std::cin >> aux2;
        }

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

      case 'j':{
        cout << "Probabilidade de transmissao da doenca: " << grafo->getPorcentagemDoenca() * 100 << "%\n\n";
        break;
      }      

      case 'k':{
          float novaProbabilidade;
          std::cout << "Insira a nova probabilidade (na forma decimal): ";
          std::cin >> novaProbabilidade;
          grafo->setPorcentagemDoenca(novaProbabilidade);
        cout << "\nProbabilidade alterada com sucesso!\n\n";    
        break;
      }

        case 'l':{
      int id;
      id = idPessoa(grafo);   
      if(id == -1){
          cout << "Pessoa nao encontrada\n";
      } else{
          cout << "ID: " << id << "\n";
      }
      break;
      } 

      case 'm':{
        if(grafo->isEuleriano()){
          cout << "\n>>> Grafo Euleriano!\n";
        }
        else{
          cout << "\n>>> Não é Euleriano!\n";
        }
        break;
      }

      case 'n':{
        cout << "\n";
        grafo->coloracaoPorClasse();
        cout << "\n";
        break;
      }

      case 'o':{
        int aux, aux2, flag;

        do{
            std::cout << "Insira 1 para inserir por ID ou 2 para inserir por nome: ";
            cin >> flag;
            cout << "\n";
        } while (flag != 1 && flag != 2);

        if(flag == 2){
            do{
                aux = idPessoa(grafo);
            } while (aux == -1);

            do{
                aux2 = idPessoa(grafo);
            } while (aux2 == -1);
        } else{        
            std::cout << "Insira o ID de uma das pessoas da conexao: ";
            std::cin >> aux;

            std::cout << "Insira o ID da outra pessoa da conexao: ";
            std::cin >> aux2;
        }
        
        cout << grafo->encontrarMaiorProduto(aux,aux2)/100 << "%\n\n";
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

int idPessoa(TGrafoND *grafo){
        int id = -1;
        string pessoa;
        string auxPessoa;
        cout << "Nome da pessoa que deseja ver o ID(Formato <Nome> [Espaco] <Sobrenome>): ";
        cin >> pessoa;
        cin >> auxPessoa;
        pessoa = pessoa + " " + auxPessoa;
        cout << "\n";
        for(int i = 0; i < grafo->getn(); i++){
            if(pessoa == nomes[i]){
                id = i;
            }
        }
        return id;
}