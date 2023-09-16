#pragma once

#include <QObject>
#include <QXmlStreamReader>

#include "RateMap.h"
#include "RateFileLoader.h"


class RateFileLoader : public QObject
{
	Q_OBJECT

public:

	RateFileLoader(RateMap* pMap);
	~RateFileLoader();

	void	setFileName(QString	fileName);
	bool	load();
private:

	void	skipCharesters(QXmlStreamReader& xml);
	RateMap*	pRateMap;
	QString		fileName;
};

