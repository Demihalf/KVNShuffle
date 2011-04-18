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
