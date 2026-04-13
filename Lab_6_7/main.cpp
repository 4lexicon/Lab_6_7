#include "entities.h"
#include "masinaRepository.h"
#include "ui.h"
#include "service.h"
#include "validator.h"
#include "tests.h"
#include <iostream>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main() {
	Test t;
	//testRepo();
	//testAdd();
	t.testAll();

	{
		if (_CrtDumpMemoryLeaks()) {
			std::cout << "Exista memory leaks! :(\n";
		}
		else {
			std::cout << "Nu sunt Memory Leaks! :D\n";
		}
	}

	//MasinaRepository repo;
	//MasinaValidator validator;
	//MasinaService srv{ validator,  repo };
	//
	//UI ui{ srv };
	//ui.showUI();

	return 0;
}