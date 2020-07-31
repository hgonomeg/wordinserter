#include <QApplication>
#include "wordinserter.hpp"

int main(int argc, char** argv) {
    QApplication app(argc,argv);
    WordInserter w;
    w.show();
    return app.exec();
}