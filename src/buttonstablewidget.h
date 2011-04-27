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

#ifndef BUTTONSTABLEWIDGET_H
#define BUTTONSTABLEWIDGET_H

#include <QWidget>

class QButtonGroup;
class QGridLayout;

// Represents buttons with numbers aligned in the table
class ButtonsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonsTableWidget(int numOfButtons, QWidget *parent = 0);

    void setButtonsCount(int count);
    void clear();

signals:
    void buttonClicked(int);

public slots:
    void disable(int index);
    void enableAll();

private:
    QButtonGroup *m_buttons;
    QGridLayout *lt;
};

#endif // BUTTONSTABLEWIDGET_H
