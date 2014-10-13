#include "INI_Editor.h"


INI_Editor::INI_Editor(QString file_settings, bool b_useSpacesInGroupName, QWidget *w_parent) :
    QDialog(w_parent),
    mo_settings(file_settings, QSettings::IniFormat),
    mw_tab(new QTabWidget()),
    mb_useSpacesInGroupName(b_useSpacesInGroupName)
{
    QScrollArea * w_scrollArea;
    QWidget *w_page;

    QFormLayout *w_layout;
    QPushButton *w_saveButton = new QPushButton(tr("Save modifications"));

    this->setLayout(new QVBoxLayout);

    this->layout()->addWidget(this->mw_tab);

    this->layout()->addWidget(w_saveButton);

    connect(w_saveButton,   &QPushButton::clicked,
            this,           &INI_Editor::saveModifications);

    // --- General section
    if (this->mo_settings.childKeys().size() > 0)
    {
        w_page = new QWidget();
        w_layout = new QFormLayout();

        w_scrollArea = new QScrollArea();
        w_scrollArea->setWidgetResizable(true);

        w_page->setLayout(w_layout);
        w_scrollArea->setWidget(w_page);

        this->mw_tab->addTab(w_scrollArea, "General");

        for (QString s_item : this->mo_settings.childKeys())
        {
            w_layout->addRow(s_item, new QLineEdit(this->mo_settings.value(s_item).toString()));
        }
    }

    // --- Others sections
    for (QString s_header : this->mo_settings.childGroups())
    {
        this->mo_settings.beginGroup(s_header);

        w_page = new QWidget();
        w_layout = new QFormLayout();

        w_scrollArea = new QScrollArea();
        w_scrollArea->setWidgetResizable(true);

        w_page->setLayout(w_layout);
        w_scrollArea->setWidget(w_page);

        this->mw_tab->addTab(w_scrollArea, s_header);

        for (QString s_item : this->mo_settings.childKeys())
        {
            w_layout->addRow(s_item, new QLineEdit(this->mo_settings.value(s_item).toString()));
        }

        this->mo_settings.endGroup();
    }
}


INI_Editor::~INI_Editor()
{
}


void INI_Editor::saveModifications()
{
    QLineEdit *w_line;

    QStringList lists_groups = this->mo_settings.childGroups();

    // Add an "empty" group to manage the [General] section (if it exist only)
    if (this->mo_settings.childKeys().size() > 0)
    {
        lists_groups.prepend("");
    }

    for (int i_i = 0; i_i < this->mw_tab->count(); ++i_i)
    {
        this->mo_settings.beginGroup(lists_groups.at(i_i));

        for (QObject *o_loop : this->mw_tab->widget(i_i)->children())
        {
            if (w_line = qobject_cast<QLineEdit *>(o_loop))
            {
                this->mo_settings.setValue(qobject_cast<QLabel *>(qobject_cast<QFormLayout *>(this->mw_tab->widget(i_i)->layout())->labelForField(w_line))->text(), w_line->text());
            }
        }
        this->mo_settings.endGroup();
    }

    this->mo_settings.sync();

    if (this->mb_useSpacesInGroupName)
    {
        if (!this->replaceStringInFile("%20", " ", this->mo_settings.fileName()))
        {
            QMessageBox::critical(NULL, "Error", "Error while saving INI File.");
        }
    }
}


bool INI_Editor::replaceStringInFile(QString s_pattern, QString s_replacement, QString s_filename)
{
    QFile file_ini(s_filename);

    if (!file_ini.open(QIODevice::ReadWrite))
    {
        return false;
    }

    QByteArray b_fileData = file_ini.readAll();

    file_ini.close();

    QString s_text(b_fileData);

    s_text.replace(s_pattern, s_replacement);

    if (!file_ini.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file_ini.write(s_text.toUtf8());

    file_ini.close();

    return true;
}
