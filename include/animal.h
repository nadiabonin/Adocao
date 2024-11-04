#pragma once

enum StatusAnimal {
	Disponivel = 'D',
	Adotado = 'A',
};

struct Animal {
	int ID;
	char nome_animal[50];
	char raca[50];
	char descricao[250];
	enum StatusAnimal status;
};

int incluirAnimal();
int adotarAnimal();
int exluirAnimal(int id);

