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

#include "displaywidget.h"

#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    createInterface();
}

void DisplayWidget::clear()
{
    m_label->clear();
}

void DisplayWidget::showPixmap(const QString &path)
{
    clear();

    QString iniFile = qApp->property("iniFile").toString();

    QSettings sets(iniFile, QSettings::IniFormat);
    double factor = sets.value("pic_size", 100).toDouble() / 100;

    QPixmap pic(path);
    pic = pic.scaled(parentWidget()->size() * factor, Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);

    m_label->setPixmap(pic);
}

void DisplayWidget::showText(const QString &text)
{
    clear();
    m_label->setText(text);
}

void DisplayWidget::createInterface()
{
    m_label = new QLabel();
    m_label->setObjectName("displayLabel");
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setWordWrap(true);

    QPushButton *btnBack = new QPushButton("Назад");
    connect(btnBack, SIGNAL(clicked()), SIGNAL(back()));

    QHBoxLayout *btnLt = new QHBoxLayout;
    btnLt->addStretch();
    btnLt->addWidget(btnBack);

    QVBoxLayout *mainLt = new QVBoxLayout;
    mainLt->addWidget(m_label, 1);
    mainLt->addLayout(btnLt);

    setLayout(mainLt);
}
