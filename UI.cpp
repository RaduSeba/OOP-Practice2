#include "UI.h"




void GUI::initGUI() {
	setLayout(lymain);


	tb_view = new QTableView;
	lymain->addWidget(tb_view);


	QWidget* wdg_right = new QWidget;
	QVBoxLayout* ly_right = new QVBoxLayout;

	wdg_right->setLayout(ly_right);

	QWidget* form_wdg = new QWidget;
	QFormLayout* form_lay = new QFormLayout;
	form_wdg->setLayout(form_lay);


	QLabel* lbId = new QLabel("Id");

	QLabel* lbNume = new QLabel("Nume");
	QLabel* lbtip = new QLabel("Tip");
	QLabel* lbpret = new QLabel("Pret");

	txtid = new QLineEdit;
	txtnume = new QLineEdit;
	txttip = new QLineEdit;
	txtpret = new QLineEdit;

	form_lay->addRow(lbId, txtid);
	form_lay->addRow(lbNume, txtnume);
	form_lay->addRow(lbtip, txttip);
	form_lay->addRow(lbpret, txtpret);

	ly_right->addWidget(form_wdg);

	add = new QPushButton("ADD");
	ly_right->addWidget(add);

	lymain->addWidget(wdg_right);


	filter = new QPushButton("Filtreaza pret");
	lymain->addWidget(filter);

	plm = new QSlider;
	plm->setMinimum(1);
	plm->setMaximum(100);
	lymain->addWidget(plm);

	map<string, int> tipuri;

	for (const auto& d : srv.get_all_prod())
	{
		tipuri[d.gettip()]++;
	}


	for (auto d : tipuri)
	{
		Window* gui = new Window{ this->srv,d.first,this->srv.getNumberOfProducts(d.first) };
		this->srv.addObserver(gui);
		gui->show();
	}
	

	




}


void GUI::connectSignals() {


	QObject::connect(plm, &QSlider::valueChanged, [=]() {
		txtpret->setText(QString::number(plm->value()));
		double value = plm->value();
		tb_model->setValoareSlider(value);
		reloadList(srv.get_all_prod());


		});

	QObject::connect(tb_view->selectionModel(), &QItemSelectionModel::selectionChanged, [=]() {
		if (tb_view->selectionModel()->selectedIndexes().empty()) {
			txtid->setText("");
			txtnume->setText("");
			txttip->setText("");
			txtpret->setText("");
			return;
		}

		auto sel = tb_view->selectionModel()->selectedIndexes().at(0);
		int row = sel.row();
		auto elem = display[row];

		txtid->setText(QString::number(elem.getid()));
		txtnume->setText(QString::fromStdString(elem.getnume()));
		txttip->setText(QString::fromStdString(elem.gettip()));
		txtpret->setText(QString::number(elem.getpret()));


		});


	QObject::connect(add, &QPushButton::clicked, [=]() {
		string tip = txttip->text().toStdString();
		
		try {
			int id = to_nr(txtid->text().toStdString());
			string nume = txtnume->text().toStdString();
			double pret = to_d(txtpret->text().toStdString());

			srv.add(id, nume, tip, pret);
			reloadList(srv.get_all_prod());
		}
		catch (ValidationException& ve)
		{
			QMessageBox::warning(this, "BA", QString::fromStdString(ve.getMesaj()));
		}
		catch (DuplicatIdException& c) {
			QMessageBox::warning(this, "Ba", QString::fromStdString(c.getmesajid()));
		}


		if (this->srv.getNumberOfProducts(tip)==1)
		{
			Window* gui = new Window{ this->srv,tip,1 };
			this->srv.addObserver(gui);
			gui->show();
		}

		});




}

void GUI::reloadList(vector<Produs>& v) {
	sort(v.begin(), v.end(), [](Produs& p1, Produs& p2) {
		return p1.getpret() > p2.getpret();
		});






	display = v;
	tb_model->setProd(v);
	
}


void Window::initGUI() {

	this->setWindowTitle(QString::fromStdString(this->tip));
	this->layout = new QHBoxLayout;
	this->setLayout(layout);
	this->nr = new QLabel{};
	this->layout->addWidget(nr);
	this->layout->addSpacing(100);
	this->update();
}