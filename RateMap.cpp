#include "RateMap.h"

RateMap::RateMap(QObject* parent)
	: QObject(parent)
{
	min = max = 0;
	firstDate	= QDate::currentDate();
	lastDate	= QDate::currentDate();
	numDays		= firstDate.daysTo(lastDate);
}