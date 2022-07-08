#pragma once


#include <QAbstractTableModel>
#include <vector>
#include <QBrush>
#include "Produse.h"


class MyTableModel :public QAbstractTableModel {

private:
	vector<Produs> produse;
	int valoareslider;

public:

	MyTableModel(vector<Produs> produ) :produse{ produ }, valoareslider{0} {}

	void setValoareSlider(const double& value)
	{
		this->valoareslider = value;
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& ind, int role ) const override {
		
		if (role == Qt::BackgroundRole) {

			Produs p = this->produse[ind.row()];
			if (p.getpret() <= this->valoareslider)
			{
				QBrush bg(Qt::red);
				return bg;
				}

			}
		
		
		
		
		
		
		if (role == Qt::DisplayRole) {
			if (ind.column() == 0) {
				return QString::number(produse[ind.row()].getid());
			}
			else if (ind.column()==1) {
				return QString::fromStdString(produse[ind.row()].getnume());
			}
			else if (ind.column() == 2) {
				return QString::fromStdString(produse[ind.row()].gettip());
			}
			else if (ind.column() == 3) {
				return QString::number(produse[ind.row()].getpret());
			}
			else if (ind.column() == 4) {
				return QString::number(produse[ind.row()].getnrvocale(produse[ind.row()].getnume()));
			}
		}
		return QVariant{};
	}

	void setProd(vector<Produs>& pw) {
		produse = pw;
		auto up = createIndex(0, 0);
		auto down = createIndex(rowCount(), columnCount());
		emit dataChanged(up, down);
		emit layoutChanged();
	}


	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
		{
			if (section == 0)
				return "ID";
			if (section == 1)
				return "NUME";
			if (section == 2)
				return "TIP";
			if (section == 3)
				return "PRET";
			if (section == 4)
				return "NUMAR VOCALE";
		}
		return QVariant();
	}
};