#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab_10_Qt.h"

class Lab_10_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Lab_10_Qt(QWidget *parent = nullptr);
    ~Lab_10_Qt();

private:
    Ui::Lab_10_QtClass ui;
};

