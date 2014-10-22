#ifndef JCALENDAR_H
#define JCALENDAR_H

#include <QWidget>

namespace Ui { class JCalendar; }
class QPushButton;
class QLabel;

class JCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit JCalendar(QWidget *i_parent = 0);
    ~JCalendar();

    struct Date
    {
        int Year;
        int Month;
        int Day;
        QString toString();
        QString toStringFull();
        QDate toQDate();
        bool operator ==( Date &i_other );

        static Date fromQDate( const QDate &i_qDate );
        static Date fromString( const QString &i_date );
        static Date fromString( const QString &i_date, const QString &i_format );
    };

    static bool isLeap(int i_year);//year is in Jalali system in range:[1244,1472]
    static bool isValid(Date &i_date );//year is in Jalali system in range:[1244,1472]
    static bool isValid(const QString &i_date);
    static Date toJalali( Date &i_date );
    static Date toGregorian( Date &i_date );
    static int getDayCount( int i_year );//Jalali
    static int getDayCount( int i_year, int i_moon );//Jalali
    static int sumOfDaysJalali(Date &i_date);
    static int sumOfDaysGregorian( Date &i_date );
    static Date today();
    static int getDayOfWeek( Date &i_date );//Jalali
    static QString getDayOfWeekName( Date &i_date );//Lalali
    static QString getDayOfWeekNameSmall( Date &i_date );//Lalali
    static int getDiffInDay( Date &i_from, Date &i_to );

    Date &getCurrentDate();
signals:
    void dateChanged( QString date );

public slots:
    void setDate(Date i_date );

private slots:
    void on_moon_currentIndexChanged(int i_index);
    void on_year_valueChanged(int i_value);
    void on_today_clicked();
    void bClicked( bool i_checked );
    void on_TextDate_editingFinished();

private:

    void reDecorate();

    int m_currentB;
    Ui::JCalendar *m_ui;
    QPushButton *m_b[ 42 ];
    int m_day[ 42 ];
    QLabel *m_w[ 6 ];
    Date m_currentDate;
};

#endif
