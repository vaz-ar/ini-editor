#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

#include "INI_Editor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString s_filename;

    if (argc == 2)
    {
        s_filename = argv[1];
    }
    else
    {
        s_filename = QFileDialog::getOpenFileName(0, "Open INI File", "", "INI Files (*.ini)");

    }

    if(s_filename.isEmpty())
        exit(-1);


    INI_Editor w_editor(s_filename);
    w_editor.show();

    return app.exec();
}
