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

#include "buttonstablewidget.h"

#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>
#include <cmath>
#include <QDebug>
#include <QVariant>

ButtonsTableWidget::ButtonsTableWidget(int numOfButtons, QWidget *parent) :
    QWidget(parent)
{
    m_buttons = new QButtonGroup(this);
    lt = new QGridLayout;

    setButtonsCount(numOfButtons);

    connect(m_buttons, SIGNAL(buttonClicked(int)), SIGNAL(buttonClicked(int)));
}

void ButtonsTableWidget::clear()
{
    QLayoutItem *child;
    while (lt->count()) {
        child = lt->takeAt(0);
        delete child;
    }

    foreach (QAbstractButton *btn, m_buttons->buttons()) {
        delete btn;
    }
}

void ButtonsTableWidget::setButtonsCount(int count)
{
    clear();

    for (int i = 0; i < count; i++) {
        QPushButton *btn = new QPushButton(QString("%1").arg(i + 1));
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setProperty("table-button", QVariant(true));
        btn->setFocusPolicy(Qt::NoFocus);

        m_buttons->addButton(btn, i);
    }

    QList<QAbstractButton *> btns = m_buttons->buttons();

    int width = int(ceil(sqrt(double(count))));
    int height = ceil(double(count) / width);

    qDebug() << height << width;

    Q_ASSERT(height * width >= count);

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width && !btns.empty(); c++) {
            lt->addWidget(btns.first(), r, c);
            btns.removeFirst();
        }
    }

    setLayout(lt);
}

void ButtonsTableWidget::enableAll()
{
    foreach (QAbstractButton *btn, m_buttons->buttons()) {
        btn->setEnabled(true);
    }
}

void ButtonsTableWidget::disable(int index)
{
    m_buttons->button(index)->setEnabled(false);
}
