#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

class QLabel;

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);

    void showPixmap(const QString &path);
    void showText(const QString &text);

signals:
    void back();

public slots:
    void clear();

private:
    void createInterface();

    QLabel *m_label;
};

#endif // DISPLAYWIDGET_H
