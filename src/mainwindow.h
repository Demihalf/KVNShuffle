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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class ButtonsTableWidget;
class DisplayWidget;

enum ResType { RES_PICTURE, RES_TEXT };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void showResource(int index);
    void backToButtons();
    void startOver();
    void about();
    void settings();
    void fullscreenToggled(bool isActivated);
    void exitFullscreen();
    void aboutQt();
    void toggleBlackFullscreen();

private:
    void loadSettings();
    void loadResources();

    Ui::MainWindow *ui;
    ButtonsTableWidget *wgtButtons;
    DisplayWidget *wgtDisplay;

    bool m_wasMaximized;
    QList<QPair<ResType, QString> > m_resources;
    QString m_resDir;
    QString m_iniFile;
};

#endif // MAINWINDOW_H
