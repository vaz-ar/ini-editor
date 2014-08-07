#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include "INI_Editor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString s_filename = argc == 2 ? argv[1] : QFileDialog::getOpenFileName(0, "Open INI File", "", "INI Files (*.ini)");

    if (s_filename.isEmpty() || !QFileInfo::exists(s_filename))
    {
        QMessageBox::critical(0, "Inexistent File", "The file provided does not exist.");
        exit(-1);
    }
    INI_Editor w_editor(s_filename);
    w_editor.show();

    return app.exec();
}
