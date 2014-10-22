#include "JCalendar.h"
#include "ui_JCalendar.h"
#include <QDate>

JCalendar::JCalendar(QWidget *i_parent) :
    QWidget(i_parent),
    m_ui(new Ui::JCalendar)
{
    m_ui->setupUi(this);
    m_b[ 0 ] = m_ui->b1;
    m_b[ 1 ] = m_ui->b2;
    m_b[ 2 ] = m_ui->b3;
    m_b[ 3 ] = m_ui->b4;
    m_b[ 4 ] = m_ui->b5;
    m_b[ 5 ] = m_ui->b6;
    m_b[ 6 ] = m_ui->b7;
    m_b[ 7 ] = m_ui->b8;
    m_b[ 8 ] = m_ui->b9;
    m_b[ 9 ] = m_ui->b10;
    m_b[ 10 ] = m_ui->b11;
    m_b[ 11 ] = m_ui->b12;
    m_b[ 12 ] = m_ui->b13;
    m_b[ 13 ] = m_ui->b14;
    m_b[ 14 ] = m_ui->b15;
    m_b[ 15 ] = m_ui->b16;
    m_b[ 16 ] = m_ui->b17;
    m_b[ 17 ] = m_ui->b18;
    m_b[ 18 ] = m_ui->b19;
    m_b[ 19 ] = m_ui->b20;
    m_b[ 20 ] = m_ui->b21;
    m_b[ 21 ] = m_ui->b22;
    m_b[ 22 ] = m_ui->b23;
    m_b[ 23 ] = m_ui->b24;
    m_b[ 24 ] = m_ui->b25;
    m_b[ 25 ] = m_ui->b26;
    m_b[ 26 ] = m_ui->b27;
    m_b[ 27 ] = m_ui->b28;
    m_b[ 28 ] = m_ui->b29;
    m_b[ 29 ] = m_ui->b30;
    m_b[ 30 ] = m_ui->b31;
    m_b[ 31 ] = m_ui->b32;
    m_b[ 32 ] = m_ui->b33;
    m_b[ 33 ] = m_ui->b34;
    m_b[ 34 ] = m_ui->b35;
    m_b[ 35 ] = m_ui->b36;
    m_b[ 36 ] = m_ui->b37;
    m_b[ 37 ] = m_ui->b38;
    m_b[ 38 ] = m_ui->b39;
    m_b[ 39 ] = m_ui->b40;
    m_b[ 40 ] = m_ui->b41;
    m_b[ 41 ] = m_ui->b42;
    m_w[ 0 ] = m_ui->w1;
    m_w[ 1 ] = m_ui->w2;
    m_w[ 2 ] = m_ui->w3;
    m_w[ 3 ] = m_ui->w4;
    m_w[ 4 ] = m_ui->w5;
    m_w[ 5 ] = m_ui->w6;

    m_currentB = 0;

    for( int i=0; i<42; ++i )
        connect( m_b[ i ], SIGNAL(clicked(bool)), this, SLOT(bClicked(bool)));

    m_currentDate.Year = 0;
    m_currentDate.Month = 0;
    m_currentDate.Day = 0;
    setDate( today() );
    m_ui->TextDate->selectAll();
    m_ui->TextDate->setFocus();
}

JCalendar::~JCalendar()
{
    delete m_ui;
}

bool JCalendar::isLeap(int i_year)
{
    int mod;
    mod = i_year % 33;
    if ( i_year <= 1472 && i_year >= 1343 )
    {
        if ( mod == 1 || mod == 5 || mod == 9 || mod == 13 || mod == 17 || mod == 22 || mod == 26 || mod == 23 )
           return true;
        else
            return false;
    }
    if ( i_year <= 1342 && i_year >= 1244 )
    {
        if ( mod == 1 || mod == 5 || mod ==9 || mod == 13 || mod == 17 || mod == 22 || mod == 26 || mod == 23 )
           return true;
        else
            return false;
    }
    return false;
}

bool JCalendar::isValid(Date &i_date)
{
    if( i_date.Year < 1244 || i_date.Year > 1472 || i_date.Month < 1 || i_date.Month > 12 || i_date.Day < 1 || i_date.Day > 31 )
        return false;

    if( i_date.Month > 6 && i_date.Day > 30 )
        return false;

    if( i_date.Month == 12 && !isLeap( i_date.Year ) && i_date.Day > 29 )
        return false;

    return true;
}

bool JCalendar::isValid(const QString &i_date)
{
    Date date = Date::fromString( i_date );
    return isValid( date );
}

int idiv( int a, int b )
{
    return a / b;
}

JCalendar::Date JCalendar::toJalali(Date &i_date)
{
    JCalendar::Date date;

    QList< int > gDaysInMonth;
    QList< int > jDaysInMonth ;
    gDaysInMonth << 31 << 28 << 31 << 30 << 31 << 30 << 31 << 31 << 30 << 31 << 30 << 31;
    jDaysInMonth << 31 << 31 << 31 << 31 << 31 << 31 << 30 << 30 << 30 << 30 << 30 << 29;
    int  gy = i_date.Year - 1600;
    int  gm = i_date.Month - 1;
    int  gd = i_date.Day - 1;
    int  gDayNo = 365 * gy + idiv( gy + 3 , 4 ) - idiv( gy + 99 , 100 ) + idiv( gy + 399 , 400 );
    for( int i=0; i < gm; ++i ){
        gDayNo += gDaysInMonth[ i ];
    }
    if( gm>1 && ( ( gy % 4 == 0 && gy % 100 != 0 ) || ( gy % 400 == 0 ) ) )
        gDayNo++;//leap and after Feb
    gDayNo += gd;

    int jDayNo = gDayNo - 79;
    int  jNp = idiv( jDayNo, 12053 ); // 12053 = 365*33 + 32/4
    jDayNo = jDayNo % 12053;
    int jY = 979 + 33 * jNp + 4 * idiv( jDayNo, 1461 );// 1461 = 365*4 + 4/4
    jDayNo %= 1461;

    if ( jDayNo >= 366 ) {
        jY += idiv( jDayNo - 1, 365 );
        jDayNo = ( jDayNo - 1 ) % 365;
    }
    int ii = 0;
    for ( int i = 0; i < 11 && jDayNo >= jDaysInMonth[ i ]; ++i ){
        jDayNo -= jDaysInMonth[ i ];
        ii = i;
    }
    int  jM = ii + 2;
    int  jD = jDayNo + 1;

    date.Year = jY;
    date.Month = jM;
    date.Day = jD;

    return date;
}

JCalendar::Date JCalendar::toGregorian(Date &i_date)
{
    JCalendar::Date date;
    //set Date
    int Year;
    int Month;
    int Day;

    Year=i_date.Year;//Jalali Year
    Month=i_date.Month;//Jalali Month
    Day=i_date.Day;//Jalali Day

    QList <int> miladiDate;
    QList <int> farvardin1st;
    //set default value
    miladiDate<<1<<1<<1;
    farvardin1st<<1<<1<<1;

    int miladiYear;
    int marchDayDiff;
    int dayCount;
    QList<int> miladiMonth;
    miladiMonth<<30<<31<<30<<31<<31<<30<<31<<30<<31<<31<<28<<31;

    miladiYear = Year + 621;

    //Detemining the Farvardin the First
    if (QDate::isLeapYear(miladiYear)){
        //this is a Miladi leap year so Shamsi is leap too so the 1st of Farvardin is March 20 (3/20)
        farvardin1st[1] =3; // change default values
        farvardin1st[2]= 20;
        marchDayDiff = 12;


    }else{
        //this is not a Miladi leap year so Shamsi is not leap too so the 1st of Farvardin is March 21 (3/21)
        farvardin1st[1] = 3;
        farvardin1st[2] =21;
        marchDayDiff = 11;
    }

    if (QDate::isLeapYear(miladiYear+1)){

        miladiMonth[10] = miladiMonth[10] + 1; //Adding one day to Feb

    }
    //Calculate the day count for input shamsi date from 1st Farvadin

    if (Month >=1 && Month<=6){

        dayCount = ((Month-1) * 31) + Day;

    }else{

        dayCount =(6 * 31) + ((Month - 7) * 30) + Day;
    }

    //Finding the correspond miladi month and day
    int remainDay = 0;
    if (dayCount <=marchDayDiff){
        //So we are in 20(for leap year) or 21for none leap year) to 31 march
        miladiDate[2] = dayCount + (31 - marchDayDiff);
        miladiDate[1] = 3;
        miladiDate[0] = miladiYear;

    }else{
         remainDay = dayCount - marchDayDiff;

    }

    int i;
    i=0;//starting from April

    while (remainDay>miladiMonth[i]){
        remainDay = remainDay - miladiMonth[i];
        i = i+1;
    }
    miladiDate[2] = remainDay;
    if (i>8){
        // We are in the next Miladi Year
        miladiDate[1] = i - 8;
        miladiDate[0] =  miladiYear + 1;
    }else{
        miladiDate[1] = i + 4;
        miladiDate[0] =  miladiYear;

    }

    date.Year = miladiDate[ 0 ];
    date.Month = miladiDate[ 1 ];
    date.Day = miladiDate[ 2 ];

    return date;
}

int JCalendar::getDayCount(int i_year)
{
    if( isLeap( i_year ) )
        return 6 * 31 + 6 * 30;
    return 6 * 31 + 5 * 30 + 29;
}

int JCalendar::getDayCount(int i_year, int i_moon)
{
    if( i_year < 1244 || i_year > 1472 || i_moon < 1 || i_moon > 12 )
        return 0;
    if( i_moon <= 6 )
        return 31;
    if( i_moon == 12 )
    {
        if( isLeap( i_year ) )
            return 30;
        return 29;
    }
    return 30;
}

int JCalendar::sumOfDaysJalali(Date &i_date)
{
    QList< int > jDaysInMonth ;
    jDaysInMonth << 31 << 31 << 31 << 31 << 31 << 31 << 30 << 30 << 30 << 30 << 30 << 29;
    int sum = i_date.Day - 1;
    for( int i=0; i<i_date.Month; ++i )
        sum += jDaysInMonth[ i ];
    return sum;
}

int JCalendar::sumOfDaysGregorian(Date &i_date)
{
    QList< int > gDaysInMonth;
    gDaysInMonth << 31 << 28 << 31 << 30 << 31 << 30 << 31 << 31 << 30 << 31 << 30 << 31;
    int sum = i_date.Day - 1;
    for( int i=0; i<i_date.Month; ++i )
        sum += gDaysInMonth[ i ];
    return sum;
}

JCalendar::Date JCalendar::today()
{
    Date date;
    QDate d = QDate::currentDate();
    date.Year = d.year();
    date.Month = d.month();
    date.Day = d.day();
    return toJalali( date );
}

int JCalendar::getDayOfWeek(JCalendar::Date &i_date)
{
    Date date = toGregorian( i_date );
    QDate qDate( date.Year, date.Month,date.Day );
    int dayOfWeek = qDate.dayOfWeek();
    dayOfWeek += 2;
    if( dayOfWeek > 7 )
        dayOfWeek -= 7;
    return dayOfWeek;
}

QString JCalendar::getDayOfWeekName(JCalendar::Date &i_date)
{
    int dayOfWeek = getDayOfWeek( i_date );
    if( dayOfWeek == 1 )
        return QString::fromUtf8("شنبه");
    if( dayOfWeek == 2 )
        return QString::fromUtf8("یک شنبه");
    if( dayOfWeek == 3 )
        return QString::fromUtf8("دو شنبه");
    if( dayOfWeek == 4 )
        return QString::fromUtf8("سه شنبه");
    if( dayOfWeek == 5 )
        return QString::fromUtf8("چهار شنبه");
    if( dayOfWeek == 6 )
        return QString::fromUtf8("پنج شنبه");
    if( dayOfWeek == 7 )
        return QString::fromUtf8("جمعه");
    return QString::fromUtf8("؟");
}

QString JCalendar::getDayOfWeekNameSmall(JCalendar::Date &i_date)
{
    int dayOfWeek = getDayOfWeek( i_date );
    if( dayOfWeek == 1 )
        return QString::fromUtf8("ش");
    if( dayOfWeek == 2 )
        return QString::fromUtf8("ی");
    if( dayOfWeek == 3 )
        return QString::fromUtf8("د");
    if( dayOfWeek == 4 )
        return QString::fromUtf8("س");
    if( dayOfWeek == 5 )
        return QString::fromUtf8("چ");
    if( dayOfWeek == 6 )
        return QString::fromUtf8("پ");
    if( dayOfWeek == 7 )
        return QString::fromUtf8("ج");
    return QString::fromUtf8("؟");
}

int JCalendar::getDiffInDay(JCalendar::Date &i_from, JCalendar::Date &i_to)
{
    Q_UNUSED( i_from );
    Q_UNUSED( i_to );
    return 0;
}

JCalendar::Date &JCalendar::getCurrentDate()
{
    return m_currentDate;
}

void JCalendar::setDate(Date i_date)
{
    if( !isValid( i_date ) || m_currentDate == i_date )
        return;

    m_currentDate = i_date;

    m_ui->year->blockSignals( true );
    m_ui->year->setValue( i_date.Year );
    m_ui->year->blockSignals( false );

    m_ui->moon->blockSignals( true );
    m_ui->moon->setCurrentIndex( i_date.Month - 1 );
    m_ui->moon->blockSignals( false );

    m_ui->TextDate->blockSignals( true );
    m_ui->TextDate->setText( i_date.toString() );
    m_ui->TextDate->blockSignals( false );

    reDecorate();
    emit dateChanged( m_currentDate.toString() );
}

void JCalendar::on_moon_currentIndexChanged(int i_index)
{
    Date date = m_currentDate;
    date.Month = i_index + 1;
    if( isValid( date ) )
    {
        m_currentDate = date;
        reDecorate();
        m_ui->TextDate->blockSignals( true );
        m_ui->TextDate->setText( m_currentDate.toString() );
        m_ui->TextDate->blockSignals( false );
        emit dateChanged( m_currentDate.toString() );
    }
}

void JCalendar::on_year_valueChanged(int i_value)
{
    Date date = m_currentDate;
    date.Year = i_value;
    if( isValid( date ) )
    {
        m_currentDate = date;
        reDecorate();
        m_ui->TextDate->blockSignals( true );
        m_ui->TextDate->setText( m_currentDate.toString() );
        m_ui->TextDate->blockSignals( false );
        emit dateChanged( m_currentDate.toString() );
    }
}

void JCalendar::on_today_clicked()
{
    setDate( today() );
}

void JCalendar::bClicked(bool i_checked)
{
    if( !i_checked )
    {
        m_b[ m_currentB ]->blockSignals( true );
        m_b[ m_currentB ]->setChecked( true );
        m_b[ m_currentB ]->blockSignals( false );
    }else
    {
        m_b[ m_currentB ]->blockSignals( true );
        m_b[ m_currentB ]->setChecked( false );
        m_b[ m_currentB ]->blockSignals( false );

        for( int i=0; i<42; ++i )
        {
            if( m_b[ i ]->isChecked() )
            {
                m_currentB = i;
                m_currentDate.Day = m_day[ i ];
                m_ui->TextDate->blockSignals( true );
                m_ui->TextDate->setText( m_currentDate.toString() );
                m_ui->TextDate->blockSignals( false );
                emit dateChanged( m_currentDate.toString() );
            }
        }
    }
}

QString toPersianNumber( int i_val )
{
    QString out;
    std::string str = QString::number( i_val ).toStdString();
    for( int i=0; i<(int)str.size(); ++i )
    {
        ushort ch = str[ i ] + 1728;
        out += QChar( ch );
    }
    return out;
}

void JCalendar::reDecorate()
{
    Date d = m_currentDate;
    d.Day = 1;
    int dayOfWeek = getDayOfWeek( d ) - 1;
    int dayCount = getDayCount( d.Year, d.Month );
    int day;

    m_b[ m_currentB ]->blockSignals( true );
    m_b[ m_currentB ]->setChecked( false );
    m_b[ m_currentB ]->blockSignals( false );

    int previousYear = d.Year;
    int previousMonth = d.Month - 1;
    if( previousMonth == 0 )
    {
        previousYear--;
        previousMonth = 12;
    }
    day = getDayCount( previousYear, previousMonth ) - dayOfWeek + 1;
    for( int i=0; i<dayOfWeek; ++i )
    {
        m_b[ i ]->setText( toPersianNumber( day ) );
        m_b[ i ]->setEnabled( false );
        m_b[ i ]->setFlat( true );
        m_day[ i ] = day++;
    }

    day = 1;
    for( int i = dayOfWeek; i< dayCount + dayOfWeek; ++i )
    {
        m_b[ i ]->setText( toPersianNumber( day ) );
        m_b[ i ]->setEnabled( true );
        m_b[ i ]->setFlat( false );
        if( day == m_currentDate.Day )
        {
            m_b[ i ]->blockSignals( true );
            m_b[ i ]->setChecked( true );
            m_b[ i ]->blockSignals( false );
            m_currentB = i;
        }
        m_day[ i ] = day++;
    }

    day = 1;
    for( int i = dayOfWeek + dayCount ; i<42; ++i )
    {
        m_b[ i ]->setText( toPersianNumber( day ) );
        m_b[ i ]->setEnabled( false );
        m_b[ i ]->setFlat( true );
        m_day[ i ] = day++;
    }

    int weekNumber = d.toQDate().weekNumber();
    for( int i=0; i<6; ++i )
        m_w[ i ]->setText( toPersianNumber( weekNumber++ ) );
}

QString JCalendar::Date::toString()
{
    return QString("%1-%2-%3").arg( Year ).arg( Month ).arg( Day );
}

QString JCalendar::Date::toStringFull()
{
    return QString("%1-%2-%3").arg( Year ).arg( Month ).arg( Day );
}

QDate JCalendar::Date::toQDate()
{
    return QDate( Year, Month, Day );
}

bool JCalendar::Date::operator ==(JCalendar::Date &i_other)
{
    return Year == i_other.Year && Month == i_other.Month && Day == i_other.Day;
}

JCalendar::Date JCalendar::Date::fromQDate(const QDate &i_qDate)
{
    Date date;
    date.Year = i_qDate.year();
    date.Month = i_qDate.month();
    date.Day = i_qDate.day();
    return date;
}

JCalendar::Date JCalendar::Date::fromString(const QString &i_date)
{
    Date date;
    QStringList list = i_date.split( "-" );
    if( list.size() < 3 )
        return today();
    date.Year = list[ 0 ].toInt();
    date.Month = list[ 1 ].toInt();
    date.Day = list[ 2 ].toInt();
    return date;
}

JCalendar::Date JCalendar::Date::fromString(const QString &i_date, const QString &i_format)
{
    Date date;
    QDate d = QDate::fromString( i_date, i_format );
    date.Year = d.year();
    date.Month = d.month();
    date.Day = d.day();
    return date;
}

void JCalendar::on_TextDate_editingFinished()
{
    Date date = Date::fromString( m_ui->TextDate->text() );
    if( isValid( date ) )
        setDate( date );
}
