#ifndef JCALENDARBUTTON_H
#define JCALENDARBUTTON_H

#include <QPushButton>

class JCalendarButton : public QPushButton
{
    Q_OBJECT

public:
    JCalendarButton(QWidget *parent = 0);

private slots:
    void buttonClicked();
};

#endif
