#include "Lab_10_Qt.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include "masinaGUI.h"
#include "masinaRepository.h"
#include "service.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    Test t;
    t.testAll();

    QApplication a(argc, argv);
    MasinaValidator validator;
    MasinaRepositoryFile repo{ "fisier_Lab_10_Qt.txt" };
    ListaLucru listaLucru;
    MasinaService ctr{ validator, repo, listaLucru };
 
    MasinaGUI gui{ ctr };

    gui.show();
    return a.exec();
}
