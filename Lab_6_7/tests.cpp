#include "tests.h"
#include "entities.h"
#include "masinaRepository.h"
#include "ui.h"
#include "service.h"
#include <iostream>
#include <assert.h>

void Test::testRepo() {
	MasinaRepository repo;
	MasinaValidator validator;
	MasinaService srv{ validator, repo };

	srv.add("1", "AA11AAA", "Dacia", "Logan", "Sedan");
	srv.add("2", "BB22BBB", "dada", "jijijili", "oijoijoi");
	srv.add("3", "CC33CCC", "ioi", "oifoes", "uhesif");
	srv.add("4", "DD44DDD", "oijoioes", "ifoiesufs", "fheskfhes");
	srv.add("5", "EE55EEE", "oidjoaoid", "mlijwe", "hfeioies");
	srv.add("6", "FF66FFF", "haiwwid", "ihdaiw", "dwaydwa");
	srv.add("7", "GG77GGG", "odwaoiwa", "daoiwaa", "idaiwao");
	srv.add("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad");


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
	assert((srv.cauta(Masina("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad"))).getId() == "8");
	assert((srv.cauta(Masina("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad"))).getNrInmatriculare() == "HH88HHH");
	assert((srv.cauta(Masina("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad"))).getProducator() == "lkdjwadjwa");
	assert((srv.cauta(Masina("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad"))).getModel() == "daoidwa");
	assert((srv.cauta(Masina("8", "HH88HHH", "lkdjwadjwa", "daoidwa", "kjdhwad"))).getTip() == "kjdhwad");
	
}


void Test::testAll() {
	testRepo();
	
}