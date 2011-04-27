/******************************************************************************
** KVNShuffle 0.2
** Copyright (C) 2011 Valery Kharitonov <kharvd@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** If you have questions regarding the use of this file, please contact me at
** kharvd@gmail.com.
**
******************************************************************************/

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
