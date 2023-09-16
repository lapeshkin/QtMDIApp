#pragma once

#include <qobject.h>
#include <QMap>
#include <QDate>

//class RateMapLoader;

class RateMap : public QObject
{
	Q_OBJECT

public:
	friend class RateFileLoader;

	RateMap(QObject* parent);
	~RateMap() {};

	qreal	getMin() const { return min; };
	qreal	getMax() const { return max; };
	QDate	getFirstDate() const { return firstDate; }
	QDate	getLastDate() const { return lastDate; }
	int		getNumDays() const { return numDays; }
	QString	getCurrencyCode() const { return currencyCode;  }

	qreal	operator[](const QDate& d) const { return rateMap[d]; }
	qreal	getRate(const QDate& d) const { return rateMap[d]; }

private:
	QMap<QDate, qreal> rateMap;
	QString	currencyCode;
	QDate	firstDate;
	QDate	lastDate;
	int		numDays;
	qreal	min;
	qreal	max;
	QDate	minDate;
	QDate	maxDate;
};

