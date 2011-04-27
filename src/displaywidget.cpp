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
