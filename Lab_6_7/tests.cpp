#include "tests.h"
#include "entities.h"
#include "masinaRepository.h"
#include "ui.h"
#include "service.h"
#include "ListaLucru.h"
#include "DTO.h"
#include <iostream>
#include <fstream>
#include <assert.h>


void Test::testRepo() {
	MasinaRepository repo;
	MasinaValidator validator;
	ListaLucru listaLucru;
	MasinaService srv{ validator, repo , listaLucru};

	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "dada", "jijijili", "oijoijoi");
	srv.add("3", "CC33CCC", "ioi", "oifoes", "uhesif");
	srv.add("4", "DD44DDD", "oijoioes", "ifoiesufs", "fheskfhes");
	srv.add("5", "EE55EEE", "oidjoaoid", "mlijwe", "hfeioies");
	srv.add("6", "FF66FFF", "haiwwid", "ihdaiw", "dwaydwa");
	srv.add("7", "GG77GGG", "odwaoiwa", "daoiwaa", "idaiwao");
	srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");
	//
	try {
		srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");
		assert(false);
	}
	catch (const RepoException& re) {
		std::cout << re.getMessage();
		assert(true);
	}
	//


	//
	Masina masinaFail("garbageValue", "garbageValue", "garbageValue", "garbageValue", "garbageValue");
	try {
		validator.valideaza(masinaFail);
		assert(false);
	}
	catch (const ValidatorException& ve) {
		std::cout << ve.getMessage();
		assert(true);
	}
	//
	

	//
	Masina masinaFail2("", "", "", "", "");
	try {
		validator.valideaza(masinaFail2);
		assert(false);
	}
	catch (const ValidatorException& ve) {
		std::cout << ve.getMessage();
		assert(true);
	}
	//

	//
	Masina masinaFail3("", "00aa000", "", "", "");
	try {
		validator.valideaza(masinaFail3);
		assert(false);
	}
	catch (const ValidatorException& ve) {
		std::cout << ve.getMessage();
		assert(true);
	}
	//

	try {
		srv.sterge("garbageValue");
		assert(false);
	}
	catch (const RepoException& re) {
		std::cout << re.getMessage();
		assert(true);
	}
	//

	//
	try {
		srv.modifica("9", "ZZ99ZZZ", "lkdjwadjwa", "daoidwa", "kjdhwad");;
		assert(false);
	}
	catch (const RepoException& re) {
		std::cout << re.getMessage();
		assert(true);
	}
	//
	
	//
	try {
		srv.cauta("9");
		assert(false);
	}
	catch (const RepoException& re) {
		std::cout << re.getMessage();
		assert(true);
	}
	//

	assert(repo.getAll().size() == 8);
	srv.modifica("8", "ZZ99ZZZ", "z", "z", "z");
	for(const Masina& m : repo.getAll())
		if (m.getId() == "8") {
			if (m.getNrInmatriculare() == "ZZ99ZZZ" &&
				m.getProducator() == "z" &&
				m.getModel() == "z" &&
				m.getTip() == "z"
				) {
				assert(true);
			}
		}

	srv.modifica("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");
	for (const Masina& m : repo.getAll())
		if (m.getId() == "8") {
			if (m.getNrInmatriculare() == "HH88HHH" &&
				m.getProducator() == "lkdjwadjwa" &&
				m.getModel() == "daoidwa" &&
				m.getTip() == "kjdhwad"
				) {
				assert(true);
			}
		}
	srv.sterge("8");
	assert(repo.getAll().size() == 7);
	srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");
	assert(repo.getAll().size() == 8);

	// era si mai simplu ???
	assert((srv.cauta("8").getId()) == "8");
	assert((srv.cauta("8").getNrInmatriculare()) == "HH88HHH");
	assert((srv.cauta("8").getProducator()) == "lkdjwadjwa");
	assert((srv.cauta("8").getModel()) == "daoidwa");
	assert((srv.cauta("8").getTip()) == "kjdhwad");
	
}

void Test::testService() {
	MasinaRepository repo;
	MasinaValidator validator;
	ListaLucru listaLucru;
	MasinaService srv{ validator, repo , listaLucru};

	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "Dacia", "Logan", "T");
	srv.add("3", "CC33CCC", "Dacia", "Logan", "T");
	srv.add("4", "DD44DDD", "Lamborghini", "Aventador", "Rapida");
	srv.add("5", "EE55EEE", "Lamborghini", "Huracan", "Rapida");

	std::vector<Masina> masiniFiltrateModel = srv.filtreazaGeneral("model", "Logan"); // 08 gaz
	assert(masiniFiltrateModel.size() == 3);
	for (const Masina& m : masiniFiltrateModel) {
		assert(m.getModel() == "Logan");
	}

	std::vector<Masina> masiniFiltrateTip = srv.filtreazaGeneral("tip", "Rapida");
	assert(masiniFiltrateTip.size() == 2);
	for (const Masina& m : masiniFiltrateTip) {
		assert(m.getTip() == "Rapida");
	}

	std::vector<Masina> masiniFiltrateFail = srv.filtreazaGeneral("garbageValue", "garbageValue");
	assert(masiniFiltrateFail.empty());

	// SORTARI

	// Nr - crescator
	std::vector<Masina> masiniSortateNrCrescator = srv.sorteazaGeneral("nr", true);
	assert(masiniSortateNrCrescator.size() == 5);
	for (size_t i = 0; i < masiniSortateNrCrescator.size() - 1; i++) {
		assert(masiniSortateNrCrescator.at(i).getNrInmatriculare() <= masiniSortateNrCrescator.at(i + 1).getNrInmatriculare());
	}

	// Nr - descrescator
	std::vector<Masina> masiniSortateNrDescrescator = srv.sorteazaGeneral("nr", false);
	assert(masiniSortateNrDescrescator.size() == 5);
	for (size_t i = 0; i < masiniSortateNrDescrescator.size() - 1; i++) {
		assert(masiniSortateNrDescrescator.at(i).getNrInmatriculare() >= masiniSortateNrDescrescator.at(i + 1).getNrInmatriculare());
	}

	// Tip - crescator
	std::vector<Masina> masiniSortateTipCrescator = srv.sorteazaGeneral("tip", true);
	assert(masiniSortateTipCrescator.size() == 5);
	for (size_t i = 0; i < masiniSortateTipCrescator.size() - 1; i++) {
		assert(masiniSortateTipCrescator.at(i).getTip() <= masiniSortateTipCrescator.at(i + 1).getTip());
	}

	// Tip - descrescator
	std::vector<Masina> masiniSortateTipDescrescator = srv.sorteazaGeneral("tip", false);
	assert(masiniSortateTipDescrescator.size() == 5);
	for (size_t i = 0; i < masiniSortateTipDescrescator.size() - 1; i++) {
		assert(masiniSortateTipDescrescator.at(i).getTip() >= masiniSortateTipDescrescator.at(i + 1).getTip());
	}

	// Producator + Model - crescator
	std::vector<Masina> masiniSortatePMCrescator = srv.sorteazaGeneral("pm", true);
	assert(masiniSortatePMCrescator.size() == 5);
	for (size_t i = 0; i < masiniSortatePMCrescator.size() - 1; i++) {
		if (masiniSortatePMCrescator.at(i).getProducator() == masiniSortatePMCrescator.at(i + 1).getProducator()) {
			assert(masiniSortatePMCrescator.at(i).getModel() <= masiniSortatePMCrescator.at(i + 1).getModel());
		}
		else {
			assert(masiniSortatePMCrescator.at(i).getProducator() <= masiniSortatePMCrescator.at(i + 1).getProducator());
		}
	}

	// Producator + Model - descrescator
	std::vector<Masina> masiniSortatePMDescrescator = srv.sorteazaGeneral("pm", false);
	assert(masiniSortatePMDescrescator.size() == 5);
	for (size_t i = 0; i < masiniSortatePMDescrescator.size() - 1; i++) {
		if (masiniSortatePMDescrescator.at(i).getProducator() == masiniSortatePMDescrescator.at(i + 1).getProducator()) {
			assert(masiniSortatePMDescrescator.at(i).getModel() >= masiniSortatePMDescrescator.at(i + 1).getModel());
		}
		else {
			assert(masiniSortatePMDescrescator.at(i).getProducator() >= masiniSortatePMDescrescator.at(i + 1).getProducator());
		}
	}

	// FAIL
	const std::vector<Masina>& toateMasinile = srv.getAll();

	std::vector<Masina> masiniSortateFail = srv.sorteazaGeneral("garbageValue", true);
	const size_t sizeFail = masiniSortateFail.size();
	assert(sizeFail == 5);
	for (size_t i = 0; i < sizeFail; i++) {
		assert(masiniSortateFail.at(i) == toateMasinile.at(i));
	}

	std::vector<Masina> masiniSortateFail2 = srv.sorteazaGeneral("garbageValue", false);
	const size_t sizeFail2 = masiniSortateFail2.size();
	assert(sizeFail2 == 5);
	for (size_t i = 0; i < sizeFail2; i++) {
		assert(masiniSortateFail2.at(i) == toateMasinile.at(i));
	}

	std::vector<Masina> masiniSortateFail3 = srv.sorteazaGeneral("garbageValue", false);
	const size_t sizeFail3 = masiniSortateFail3.size();
	assert(sizeFail3 == 5);
	for (size_t i = 0; i < sizeFail3; i++) {
		assert(masiniSortateFail3.at(i) == toateMasinile.at(i));
	}
	// FAIL


	Masina masinaDeTest("test", "test", "test", "test", "test");
	masinaDeTest = masinaDeTest; // test autoatribuire

	assert(masinaDeTest.getId() == "test");
	assert(masinaDeTest.getNrInmatriculare() == "test");
	assert(masinaDeTest.getProducator() == "test");
	assert(masinaDeTest.getModel() == "test");
	assert(masinaDeTest.getTip() == "test");

	Masina masinaDeTest2 = std::move(masinaDeTest);

	assert(masinaDeTest2.getId() == "test");
	assert(masinaDeTest2.getNrInmatriculare() == "test");
	assert(masinaDeTest2.getProducator() == "test");
	assert(masinaDeTest2.getModel() == "test");
	assert(masinaDeTest2.getTip() == "test");

	assert(masinaDeTest.getId() == "");
	assert(masinaDeTest.getNrInmatriculare() == "");
	assert(masinaDeTest.getProducator() == "");
	assert(masinaDeTest.getModel() == "");
	assert(masinaDeTest.getTip() == "");

	masinaDeTest2 = std::move(masinaDeTest2); // automutare

	assert(masinaDeTest2.getId() == "test");
	assert(masinaDeTest2.getNrInmatriculare() == "test");
	assert(masinaDeTest2.getProducator() == "test");
	assert(masinaDeTest2.getModel() == "test");
	assert(masinaDeTest2.getTip() == "test");

	masinaDeTest = masinaDeTest2;
	assert(masinaDeTest.getId() == "test");
	assert(masinaDeTest.getNrInmatriculare() == "test");
	assert(masinaDeTest.getProducator() == "test");
	assert(masinaDeTest.getModel() == "test");
	assert(masinaDeTest.getTip() == "test");

	assert(masinaDeTest2.getId() == "test");
	assert(masinaDeTest2.getNrInmatriculare() == "test");
	assert(masinaDeTest2.getProducator() == "test");
	assert(masinaDeTest2.getModel() == "test");
	assert(masinaDeTest2.getTip() == "test");

}

void Test::testListaLucru() {
	MasinaRepository repo;
	MasinaValidator validator;
	ListaLucru listaLucru;
	MasinaService srv{ validator, repo , listaLucru };

	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "dada", "jijijili", "oijoijoi");
	srv.add("3", "CC33CCC", "ioi", "oifoes", "uhesif");
	srv.add("4", "DD44DDD", "oijoioes", "ifoiesufs", "fheskfhes");
	srv.add("5", "EE55EEE", "oidjoaoid", "mlijwe", "hfeioies");
	srv.add("6", "FF66FFF", "haiwwid", "ihdaiw", "dwaydwa");
	srv.add("7", "GG77GGG", "odwaoiwa", "daoiwaa", "idaiwao");
	srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");

	srv.adaugaInLista("AA11AAA");
	assert(srv.getAllLista().size() == 1);
	assert(srv.getAllLista().at(0).getNrInmatriculare() == "AA11AAA");
	
	std::string numeFisier = "fisierTest_iteratia8";
	srv.exportaListaCSV(numeFisier);

	numeFisier += ".csv";

	std::ifstream fin(numeFisier);
	assert(fin.is_open());

	std::string linie;
	std::getline(fin, linie);
	assert(linie.find("AA11AAA") != std::string::npos);
	fin.close();

	
	std::remove(numeFisier.c_str()); // sterge fisierul

	//assert cand nu se poate deschide
	std::string numeInvalid = "Z:/folder_invalid/test.csv";
	try {
		srv.exportaListaCSV(numeInvalid);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage().find("Nu s-a putut deschide") != std::string::npos);
	}



	//
	srv.adaugaInLista("BB22BBB");
	assert(srv.getAllLista().size() == 2);
	assert(srv.getAllLista().at(0).getNrInmatriculare() == "AA11AAA");
	assert(srv.getAllLista().at(1).getNrInmatriculare() == "BB22BBB");

	try {
		srv.adaugaInLista("garbageValue");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage().find("Masina specificata nu exista") != std::string::npos);
	}

	srv.golesteLista();
	assert(srv.getAllLista().size() == 0);

	srv.adaugaInLista("BB22BBB");
	srv.genereazaListaAleatorie(5);
	assert(srv.getAllLista().size() == 6);

	srv.golesteLista();
	assert(srv.getAllLista().size() == 0);

	srv.genereazaListaAleatorie(-1); // -1 pentru ca e size_t, dar puteam pune si un int foarte mare
	assert(srv.getAllLista().size() == 8);

	

}

void Test::testDTO() {
	MasinaRepository repo;
	MasinaValidator validator;
	ListaLucru listaLucru;
	MasinaService srv{ validator, repo , listaLucru};

	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "dada", "jijijili", "oijoijoi");
	srv.add("3", "CC33CCC", "ioi", "oifoes", "uhesif");
	srv.add("4", "DD44DDD", "oijoioes", "ifoiesufs", "fheskfhes");
	srv.add("5", "EE55EEE", "oidjoaoid", "mlijwe", "hfeioies");
	srv.add("6", "FF66FFF", "haiwwid", "ihdaiw", "dwaydwa");
	srv.add("7", "GG77GGG", "odwaoiwa", "daoiwaa", "idaiwao");
	srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");

	// pentru ce exista

	std::map<std::string, DTO> dtoTest = srv.frecventaProducator("Dacia");
	assert(dtoTest["Dacia"].getCheie() == "Dacia");
	assert(dtoTest["Dacia"].getValoare() == 1);

	// pentru ce NU exista

	std::map<std::string, DTO> dtoTest2 = srv.frecventaProducator("randomValue");
	assert(dtoTest2["randomValue"].getCheie() == "randomValue");
	assert(dtoTest2["randomValue"].getValoare() == 0);
}

void Test::testUndo() {
	//std::ofstream fout("C:\\Users\\User\\Desktop\\OOP\\Lab_9\\Lab_9\\Lab_9_fisier_test.txt"); // C:\\Users\\User\\Desktop\\OOP\\Lab_9\\Lab_9\\Lab_9_fisier_test.txt
	std::string numeFisier = "Lab_9_fisier_test.txt";
	std::ofstream fout(numeFisier);
	assert(fout.is_open());
	fout.close();

	std::string numeFail = "Z:/folder_invalid/test.txt";
	try {
		MasinaRepositoryFile repoFail(numeFail);
		assert(false);
	}
	catch(const RepoException& re){
		assert(true);
		assert(re.getMessage().find("Error open:") != std::string::npos);
	}

	std::ofstream foutFail(numeFail);
	assert(!foutFail.is_open());
	///////////////////////////////
	MasinaRepositoryFile repo1(numeFisier);
	//MasinaRepository repo;	
	MasinaValidator validator;
	ListaLucru listaLucru;
	MasinaService srv1{ validator, repo1 , listaLucru };
	srv1.add("0", "tt00ttt", "test", "test", "test");
	//fout.close();
	MasinaRepositoryFile repo(numeFisier);
	MasinaService srv{ validator, repo , listaLucru };
	assert(repo.getAll().size() == 1);
	assert(repo.getAll().at(0).getId() == "0");
	assert(repo.getAll().at(0).getNrInmatriculare() == "tt00ttt");
	assert(repo.getAll().at(0).getProducator() == "test");
	assert(repo.getAll().at(0).getModel() == "test");
	assert(repo.getAll().at(0).getTip() == "test");

	try {
		srv.undo();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage().find("Nu exista operatie pentru undo\n") != std::string::npos);
	}
	///////////////
	srv.sterge("0"); // pentru masina test
	///////////////
	assert(repo.getAll().size() == 0);
	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "dada", "jijijili", "oijoijoi");
	assert(srv.cautaNrInmatriculare("AA11AAA").getId() == "1");
	assert(srv.cautaNrInmatriculare("AA11AAA").getProducator() == "Dacia");
	assert(srv.cautaNrInmatriculare("AA11AAA").getModel() == "Logan");
	assert(srv.cautaNrInmatriculare("AA11AAA").getTip() == "Sedan");
	try {
		srv.cautaNrInmatriculare("garbageValue");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage().find("Masina specificata nu exista") != std::string::npos);
	}

	assert(repo.getAll().size() == 2);
	srv.sterge("2");
	assert(repo.getAll().size() == 1);
	srv.undo();
	assert(repo.getAll().size() == 2);
	srv.undo();
	assert(repo.getAll().size() == 1);
	assert(repo.getAll().at(0).getId() == "1");
	assert(repo.getAll().at(0).getNrInmatriculare() == "AA11AAA");
	srv.modifica("1", "ZZ99ZZZ", "z", "z", "z");
	assert(repo.getAll().size() == 1);

	for (const Masina& m : repo.getAll()) {
		if (m.getId() == "1") {
			assert(m.getNrInmatriculare() == "ZZ99ZZZ");
			assert(m.getProducator() == "z");
			assert(m.getModel() == "z");
			assert(m.getTip() == "z");
		}
	}

	srv.undo();

	for (const Masina& m : repo.getAll()) {
		if (m.getId() == "1") {
			assert(m.getNrInmatriculare() == "AA11AAA");
			assert(m.getProducator() == "Dacia");
			assert(m.getModel() == "Logan");
			assert(m.getTip() == "Sedan");
			//std::cout << m.getNrInmatriculare() << " "<<
			//	 m.getProducator() << " " <<
			//	 m.getModel() << " "	  <<
			//	 m.getTip() << "\n";
		}
	}


	std::remove(numeFisier.c_str()); // sterge fisierul

}

void Test::testAll() {
	testRepo();
	testService(); // mai mult pentru filtrare si sortare
	testListaLucru();
	testDTO();
	testUndo();
}