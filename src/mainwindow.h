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

    static const QString iniFile;
};

template <class T>
QList<T> shuffled(QList<T> list)
{
    int newPos;

    for (int i = 0; i < list.size(); i++) {
        newPos = qrand() % list.size();
        qSwap(list[i], list[newPos]);
    }

    return list;
}

#endif // MAINWINDOW_H
