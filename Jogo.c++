
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

const int max_palavras = 10; //definir o tamanho maximo da lista de palavras

using namespace std;

struct Lista {
	string palavras[10];
	int cont;
};

void ler_arquivo(Lista lista[], int tam) {
	ifstream arquivo;
	string linha, palavra;
	arquivo.open("Lista.csv");
	if (!arquivo.is_open()) {
		cout << "Nao foi possivel abrir o arquivo" << endl;
	}
	else {
		for (int i = 0; i < tam; i++) {
			int pos = 0;
			getline(arquivo, linha);
			for (char c : linha) {
				if (c != ',')
					palavra += c;
				else {
					lista[i].palavras[pos] = palavra;
					palavra.clear();
					pos++;
				}
			}
			lista[i].cont = pos;
		}
	}
	arquivo.close();
}

void escreverArquivo(Lista lista[], int tam) {
	ofstream arquivo;
	arquivo.open("Lista.csv");
	if (!arquivo.is_open()) {
		cout << "Nao foi possivel abrir o arquivo" << endl;
	}
	else {
		for (int i = 0; i < tam - 1; i++) {
			for (int j = 0; j < max_palavras; j++) {
				arquivo << lista[i].palavras[j] << ",";
			}
			cout << endl;
		}
	}
	arquivo.close();
}

void addPalavras(Lista lista[], int tamanhoLista) {
	string palavra;
	int cont = 0;

	while (true) {
		cout << "Digite uma palavra (ou 'fim' para encerrar a lista): ";
		cin >> palavra;

		if (palavra == "fim") {
			break;
		}
		lista[tamanhoLista - 1].palavras[cont++] = palavra;

		if (cont == max_palavras) {
			cout << "A lista esta cheia, nao eh possivel adicionar mais palavras.\n";
			break;
		}
	}
}

Lista* aumentarVetor(Lista* vetor, int& tamanhoAtual, int novoTamanho) {
	Lista* novoVetor = new Lista[tamanhoAtual + novoTamanho];

	for (int i = 0; i < tamanhoAtual; i++) {
		novoVetor[i] = vetor[i];
	}
	delete[] vetor;
	tamanhoAtual = tamanhoAtual + novoTamanho;

	return novoVetor;
}

int contPosicao() {
	ifstream arquivo;
	arquivo.open("Lista.csv");
	int cont = 0;
	string linha;
	if (!arquivo.is_open()) {
		cout << "Nao foi possivel abrir o arquivo" << endl;
	}
	else {
		while (getline(arquivo, linha)) {
			if (linha.empty() == false) {
				cont++;
			}
		}
		arquivo.close();
	}
	return cont;
}

void verLista(Lista lista[], int tam) {
	for (int i = 0; i < tam - 1; i++) {
		cout << "Lista " << i << ":" << endl;
		for (int j = 0; j < max_palavras; j++) {
			cout << " " << lista[i].palavras[j] << endl;
		}
	}
}

void excluirLista(Lista lista[], int& tam) {
	int listaExcluir;
	cout << "Digite o numero da lista que deseja excluir: ";
	cin >> listaExcluir;

	if (listaExcluir >= 0 && listaExcluir < tam) {
		for (int i = listaExcluir; i < tam - 1; i++) {
			lista[i] = lista[i + 1];
		}

		tam--;

		cout << "Lista excluida com sucesso.\n";
	}
	else {
		cout << "Número de lista inválido.\n";
	}
}


int main()
{
	int tam = 1;
	int cont = 0;
	Lista* lista = new Lista[tam];
	int opcao = 0;
	string resposta;

	cont = contPosicao();
	cout << cont;
	while (opcao != 6) {
		cout << "\t--Caca-Palavras--" << endl;
		cout << "\t[1] Jogar" << endl;
		cout << "\t[2] Escrever lista de palavras" << endl;
		cout << "\t[3] Ver lista(s)" << endl;
		cout << "\t[4] Deletar lista(s)" << endl;
		cout << "\t[5] Sair" << endl;
		cin >> opcao;
		system("cls");

		switch (opcao) {
		case 1:
			system("cls");
			break;
		case 2:
			do {
				addPalavras(lista, tam);
				cont++;
				if (cont == tam) {
					lista = aumentarVetor(lista, tam, 1);
				}
				cout << "Deseja adicionar outra lista? (s/n): ";
				cin >> resposta;
			} while (resposta == "s");

			cout << "Lista adicionada:\n";
			for (int i = 0; i < max_palavras; i++) {
				cout << "- " << lista[cont - 1].palavras[i] << endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			verLista(lista, tam);
			system("pause");
			system("cls");
			break;
		case 4:
			excluirLista(lista, tam);
			system("pause");
			system("cls");
			break;
		case 5:
			escreverArquivo(lista, tam);
			system("pause");
			system("cls");
			break;
		default:
			system("cls");
			cout << "Opcao Invalida" << endl;
		}

	}
}
