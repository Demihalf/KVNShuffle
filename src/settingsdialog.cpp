#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(saveSettings()));

    m_iniFile = qApp->property("iniFile").toString();

    QSettings sets(m_iniFile, QSettings::IniFormat);
    ui->txtTitle->setText(sets.value("title_text").toString());
    ui->spinPicSize->setValue(sets.value("pic_size", 100).toInt());
}

void SettingsDialog::saveSettings()
{
    QSettings sets(m_iniFile, QSettings::IniFormat);
    sets.setValue("title_text", ui->txtTitle->document()->toPlainText());
    sets.setValue("pic_size", ui->spinPicSize->value());
    accept();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
