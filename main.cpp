#include "UI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    auto rp = Repo{ "suciu.txt" };
    auto srv = Service{ rp };
    auto gu = GUI{ srv };
    gu.show();

    return QApplication::exec();
}
