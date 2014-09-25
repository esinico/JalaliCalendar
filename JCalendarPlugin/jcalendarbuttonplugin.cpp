#include <JCalendarButton.h>
#include "jcalendarbuttonplugin.h"

#include <QtPlugin>

JCalendarButtonPlugin::JCalendarButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void JCalendarButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool JCalendarButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *JCalendarButtonPlugin::createWidget(QWidget *parent)
{
    return new JCalendarButton(parent);
}

QString JCalendarButtonPlugin::name() const
{
    return QLatin1String("JCalendarButton");
}

QString JCalendarButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon JCalendarButtonPlugin::icon() const
{
    JCalendarButton w;
    w.resize( 80, 21 );
    QPixmap pix( w.size() );
    w.render( &pix );
    return QIcon( pix.scaled( 80, 21 ) );
}

QString JCalendarButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString JCalendarButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool JCalendarButtonPlugin::isContainer() const
{
    return false;
}

QString JCalendarButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"JCalendarButton\" name=\"jCalendarButton\">\n</widget>\n");
}

QString JCalendarButtonPlugin::includeFile() const
{
    return QLatin1String("JCalendarButton.h");
}

