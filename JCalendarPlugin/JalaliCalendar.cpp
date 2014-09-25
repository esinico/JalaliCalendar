#include "jcalendarplugin.h"
#include "jcalendarbuttonplugin.h"
#include "JalaliCalendar.h"

JalaliCalendar::JalaliCalendar(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new JCalendarPlugin(this));
    m_widgets.append(new JCalendarButtonPlugin(this));

}

QList<QDesignerCustomWidgetInterface*> JalaliCalendar::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(JalaliCalendarPlugin, JalaliCalendar)
#endif // QT_VERSION < 0x050000
