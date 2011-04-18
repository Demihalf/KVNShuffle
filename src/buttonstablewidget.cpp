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
