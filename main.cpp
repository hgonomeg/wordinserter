#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "wordinserter.hpp"

int main(int argc, char** argv) {
    QApplication app(argc,argv);
    QTranslator* translator = new QTranslator(&app);
    QString target_lang = QLocale::system().name(); // e.g. "de_DE"
    target_lang.truncate(target_lang.lastIndexOf('_')); // e.g. "de"

    translator->load(QString("./lang/wordinserter_%1").arg(target_lang));
    app.installTranslator(translator);
    WordInserter w;
    w.show();
    return app.exec();
}
