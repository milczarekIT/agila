#include "DateEdit.h"

DateEdit::DateEdit()
{
    setDate(QDate::currentDate());
    setDisplayFormat("yyyy-MM-dd");
    setCalendarPopup(true);
    setCalendarWidget(new CalendarWidget());
}
