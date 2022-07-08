#pragma once

#include"Tabelview.h"
#include"Repo.h"
#include "Service.h"
#include "Observer.h"
#include<QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <Qtableview>
#include <QLineEdit>
#include <QSlider>
#include <qicon.h>
#include <qpixmap.h>






class Window :public QWidget, public Observer {

	string tip;
	Service& s;

	QHBoxLayout* layout;
	QLabel* nr;
	int numar;


	void initGUI();

public:
	Window(Service& s, string tit, const int& numar) :s{ s }, tip{ tit }, numar{ numar }{
		this->initGUI();
	}
	virtual void update() override {
		nr->setText("Numar elemente:" + QString::number(this->s.getNumberOfProducts(this->tip)));
	}
};



class GUI :public QWidget {
	
	string title;
	Service& srv;
	vector<Produs> display;
	QHBoxLayout* lymain = new QHBoxLayout;
	QTableView* tb_view;
	MyTableModel* tb_model;

	QLineEdit* txtid;
	QLineEdit* txtnume;
	QLineEdit* txttip;
	QLineEdit* txtpret;
	QPushButton* add;
	QPushButton* filter;
	QSlider* plm;

	void initGUI();
	void connectSignals();
	void reloadList(vector<Produs>& all);

public:
	GUI(Service& srv) :srv{ srv } {
		initGUI();
		connectSignals();
		tb_model = new MyTableModel{ srv.get_all_prod() };
		display = srv.get_all_prod();
		tb_view->setModel(tb_model);
		reloadList(srv.get_all_prod());
	}
	
};
