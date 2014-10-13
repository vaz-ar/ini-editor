#ifndef INI_EDITOR_H
#define INI_EDITOR_H

#include <QDialog>
#include <QSettings>
#include <QFormLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QScrollArea>

class INI_Editor : public QDialog
{
    Q_OBJECT


private:

    QSettings mo_settings;

    QTabWidget *mw_tab;

    bool mb_useSpacesInGroupName;


public:

    explicit INI_Editor(QString file, bool b_useSpacesInGroupName = true, QWidget *w_parent = NULL);

    ~INI_Editor();


private:

    bool replaceStringInFile(QString s_pattern, QString s_replacement, QString s_filename);


public slots:

    void saveModifications();


};

#endif // INI_EDITOR_H
