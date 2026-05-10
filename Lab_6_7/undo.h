#pragma once
#include "entities.h"
#include "masinaRepository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Masina masinaAdaugata;
	MasinaRepositoryAbstract& repo;
public:
	UndoAdauga(MasinaRepositoryAbstract& repo, const Masina& m) : repo{ repo }, masinaAdaugata{ m } {}

	void doUndo() override {
		repo.sterge(masinaAdaugata.getId());
	}
};

class UndoSterge : public ActiuneUndo {
	Masina masinaStearsa;
	MasinaRepositoryAbstract& repo;
public:
	UndoSterge(MasinaRepositoryAbstract& repo, const Masina& m) :repo{ repo }, masinaStearsa{ m } {}
	void doUndo() override {
		repo.add(masinaStearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Masina masinaVeche;
	MasinaRepositoryAbstract& repo;
public:
	UndoModifica(MasinaRepositoryAbstract& repo, const Masina& m) :repo{ repo }, masinaVeche{ m } {}
	void doUndo() override {
		repo.modifica(masinaVeche.getId(), masinaVeche);
	}
};
