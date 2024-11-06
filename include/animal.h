// #pragma once

enum StatusAnimal {
	Disponivel = 'D',
	Adotado = 'A',
};

enum gatooucachorro {
	cachorro = 'C',
	gato = 'G',
};

struct Animal {
	int ID;
	enum gatooucachorro especie; 
	char nome[50];
	char raca[50];
	char descricao[250];
	enum StatusAnimal status;
};

extern void MenuAnimal();
