#include "entities.h"
#include "masinaRepository.h"
#include "ui.h"
#include "service.h"
#include "validator.h"
#include "ListaLucru.h"
#include "tests.h"
#include <iostream>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main() {
	Test t;
	//testRepo();
	//testAdd(); 
	t.testAll(); 


	if (_CrtDumpMemoryLeaks()) {
		std::cout << "Exista memory leaks! :(\n";
	}
	else {
		std::cout << "Nu sunt Memory Leaks! :D\n";
	}

	{
		//MasinaRepositoryFile repo("C:\\Users\\User\\Desktop\\OOP\\Lab_9\\Lab_9\\fisier_Lab_9.txt");
		//MasinaRepositoryNou repo(0.5);
		//MasinaValidator validator;
		//ListaLucru listaLucru;
		//MasinaService srv{ validator,  repo , listaLucru };

		//UI ui{ srv };
		//ui.showUI();
	}
	if (_CrtDumpMemoryLeaks()) {
		std::cout << "Exista memory leaks! :(\n";
	}
	else {
		std::cout << "Nu sunt Memory Leaks! :D\n";
	}

	return 0;
}