#include "JCalendarButton.h"
#include "JCalendar.h"
#include <QDialog>

JCalendarButton::JCalendarButton(QWidget *parent) :
    QPushButton(parent)
{
    setText( JCalendar::today().toString() );
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void JCalendarButton::buttonClicked()
{
    QDialog dialog( this, Qt::FramelessWindowHint );
    JCalendar calendar( &dialog );
    calendar.setDate( JCalendar::Date::fromString( text() ) );

    QPoint p = mapToGlobal( QPoint() );
    p.setY( p.y() + height() );
    dialog.move( p );
    dialog.exec();
    setText( calendar.getCurrentDate().toString() );
}
