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

#include <ctime>

#include <QByteArray>
#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImageReader>
#include <QMessageBox>
#include <QSettings>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "buttonstablewidget.h"
#include "displaywidget.h"
#include "settingsdialog.h"
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);

    m_iniFile = qApp->property("iniFile").toString();

    loadSettings();

    qsrand(time(0));
    loadResources();

    wgtButtons = new ButtonsTableWidget(m_resources.size());
    wgtDisplay = new DisplayWidget();

    ui->stack->addWidget(wgtButtons);
    ui->stack->addWidget(wgtDisplay);

    addAction(ui->actExitFullscreen);

    connect(wgtButtons, SIGNAL(buttonClicked(int)), wgtButtons,
            SLOT(disable(int)));
    connect(wgtButtons, SIGNAL(buttonClicked(int)),
            SLOT(showResource(int)));
    connect(wgtDisplay, SIGNAL(back()), SLOT(backToButtons()));
    connect(ui->actStartOver, SIGNAL(triggered()), SLOT(startOver()));
    connect(ui->actAbout, SIGNAL(triggered()), SLOT(about()));
    connect(ui->actSettings, SIGNAL(triggered()), SLOT(settings()));
    connect(ui->actFullscreen, SIGNAL(toggled(bool)),
            SLOT(fullscreenToggled(bool)));
    connect(ui->actExitFullscreen, SIGNAL(triggered()),
            SLOT(exitFullscreen()));
    connect(ui->actAboutQt, SIGNAL(triggered()), SLOT(aboutQt()));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::loadSettings()
{
    QSettings sets(m_iniFile, QSettings::IniFormat);
    ui->lblTitle->setText(sets.value("title_text").toString());
    m_resDir = sets.value("resDir").toString();
}

void MainWindow::settings()
{
    SettingsDialog *dlg = new SettingsDialog(this);

    if (dlg->exec()) {
        loadSettings();
    }

    delete dlg;
}

void MainWindow::about()
{
    QFile f(":/about_string.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream(&f);

    QString about = stream.readAll().arg(qApp->applicationName())
            .arg(qApp->applicationVersion()).replace("\n", "");

    QMessageBox::about(this, "О программе", about);
}

void MainWindow::startOver()
{
    backToButtons();

    wgtButtons->clear();
    m_resources.clear();

    loadResources();

    wgtButtons->setButtonsCount(m_resources.size());
}

void MainWindow::backToButtons()
{
    wgtDisplay->clear();
    ui->stack->setCurrentIndex(0);
    toggleBlackFullscreen();
}

void MainWindow::showResource(int index)
{
    ui->stack->setCurrentIndex(1);

    QString resource;
    resource = m_resources.at(index).second;

    toggleBlackFullscreen();

    if (m_resources.at(index).first == RES_PICTURE) {
        wgtDisplay->showPixmap(resource);
    } else {
        wgtDisplay->showText(resource);
    }
}

void MainWindow::loadResources()
{
    // Pixmaps
    QStringList filterPics;

    foreach (QString format, QImageReader::supportedImageFormats()) {
        filterPics << "*." + format;
    }

    qDebug() << filterPics;

    QDir resDir(m_resDir);
    QStringList pics = resDir.entryList(filterPics, QDir::Files);

    foreach (QString path, pics) {
        m_resources << qMakePair(RES_PICTURE, resDir.absoluteFilePath(path));
    }

    // Texts
    QStringList txts = resDir.entryList(QStringList() << "*.txt",
                                                QDir::Files);
    foreach (QString path, txts) {
        QFile f(resDir.absoluteFilePath(path));
        f.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream stream(&f);
        stream.setCodec(QTextCodec::codecForLocale());

        m_resources.append(qMakePair(RES_TEXT, QString(stream.readAll())));
    }

    m_resources = Utility::shuffled(m_resources);
}

void MainWindow::fullscreenToggled(bool isActivated)
{
    if (isActivated) {
        m_wasMaximized = isMaximized();
        showFullScreen();
    } else {
        showNormal();
        if (m_wasMaximized) {
            showMaximized();
        }
    }
}

void MainWindow::toggleBlackFullscreen()
{
    if (ui->stack->currentIndex() == 1) {
        ui->menuBar->hide();
        ui->lblPictureTopLeft->hide();
        ui->lblPictureTopRight->hide();
        ui->lblTitle->hide();
    } else {
        ui->menuBar->show();
        ui->lblPictureTopLeft->show();
        ui->lblPictureTopRight->show();
        ui->lblTitle->show();
    }
}

void MainWindow::exitFullscreen()
{
    if (isFullScreen()) {
       ui->actFullscreen->toggle();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton btn =
            QMessageBox::question(this, "Выход", "Вы действительно хотите выйти?",
                          QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (btn == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
