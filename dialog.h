#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSettings>
#include <QLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QLabel>


class Dialog : public QDialog
{
    Q_OBJECT


public:

    explicit Dialog(QString file);

    ~Dialog();


private:

    QSettings m_settings;
};

#endif // DIALOG_H
