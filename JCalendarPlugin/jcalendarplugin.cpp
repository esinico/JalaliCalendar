#include <JCalendar.h>
#include "jcalendarplugin.h"

#include <QtPlugin>

JCalendarPlugin::JCalendarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void JCalendarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool JCalendarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *JCalendarPlugin::createWidget(QWidget *parent)
{
    return new JCalendar(parent);
}

QString JCalendarPlugin::name() const
{
    return QLatin1String("JCalendar");
}

QString JCalendarPlugin::group() const
{
    return QLatin1String("");
}

QIcon JCalendarPlugin::icon() const
{
    JCalendar w;
    QPixmap pix( w.size() );
    w.render( &pix );
    return QIcon( pix.scaled( 64, 64 ) );
}

QString JCalendarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString JCalendarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool JCalendarPlugin::isContainer() const
{
    return false;
}

QString JCalendarPlugin::domXml() const
{
    return QLatin1String(
                "<ui language=\"c++\">\n"
                "	<widget class=\"JCalendar\" name=\"jCalendar\">\n"
                "		<property name=\"geometry\">\n"
                "			<rect>\n"
                "				<x>0</x>\n"
                "				<y>0</y>\n"
                "				<width>226</width>\n"
                "				<height>203</height>\n"
                "			</rect>\n"
                "		</property>\n"
                "	</widget>\n"
                "</ui>\n" );
}

QString JCalendarPlugin::includeFile() const
{
    return QLatin1String("JCalendar.h");
}

