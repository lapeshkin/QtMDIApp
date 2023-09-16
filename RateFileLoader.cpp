#include <QFile>
#include <QXmlStreamReader>

#include "RateMap.h"

#include "RateFileLoader.h"

RateFileLoader::RateFileLoader(RateMap* pMap)
	: QObject(pMap)
{
	pRateMap = pMap;
	//setFileName("I:\\rates.xml");
}

RateFileLoader::~RateFileLoader()
{
}

void RateFileLoader::setFileName(QString _fileName)
{
	fileName = _fileName;
}

bool RateFileLoader::load()
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QXmlStreamReader xml(&file);

	while (!xml.atEnd() && !xml.hasError())
	{
		QXmlStreamReader::TokenType token = xml.readNext();

		//QString s;
		//s = xml.name().toString();
		//s = xml.text().toString();
		//s = xml.tokenString();

		if (token == QXmlStreamReader::StartDocument)
			continue;

		if (token == QXmlStreamReader::StartElement)
		{
			if (xml.name() == "Record")
			{
				QXmlStreamAttributes attributes = xml.attributes();

				QDate recordDate = QDate::fromString(attributes.value("Date").toString(), "dd.MM.yyyy");
				QString	recordNominal;
				qreal recordValue;

				skipCharesters(xml);	// tag "Nominal"
				//s = xml.name().toString();
				//s = xml.text().toString();
				//s = xml.tokenString();
				token = xml.readNext(); // value "Nominal"
				recordNominal = xml.text().toString();
				token = xml.readNext(); // endtag "Nominal"

				skipCharesters(xml);	// tag "Value"
				token = xml.readNext(); // value "Value"
				//QString s = xml.text().toString().replace(",", ".");
				//qreal r = s.toDouble();
				recordValue = xml.text().toString().replace(",", ".").toDouble();
				token = xml.readNext(); // endtag "Value"

				//qInfo("Date=" + recordDate.toString("dd.MM.yyyy").toLatin1() + ", Value=" + recordValue.toLatin1());

				if (pRateMap->rateMap.isEmpty())
				{
					pRateMap->min = recordValue;
					pRateMap->max = recordValue;
				}

				pRateMap->rateMap.insert(recordDate, recordValue);

				if (recordValue < pRateMap->min)
				{
					pRateMap->min = recordValue;
					pRateMap->minDate = recordDate;

				}
				if (recordValue > pRateMap->max)
				{
					pRateMap->max = recordValue;
					pRateMap->maxDate = recordDate;

				}
			}
			else if (xml.name() == "ValCurs")
			{
				QXmlStreamAttributes attributes = xml.attributes();

				pRateMap->firstDate = QDate::fromString(attributes.value("DateRange1").toString(), "dd.MM.yyyy");
				pRateMap->lastDate = QDate::fromString(attributes.value("DateRange2").toString(), "dd.MM.yyyy");
				pRateMap->currencyCode = attributes.value("ID").toString();
				pRateMap->numDays = pRateMap->firstDate.daysTo(pRateMap->lastDate);
				pRateMap->min = 0;
				pRateMap->max = 0;

				pRateMap->rateMap.clear();
			}
		}
	}

	return true;
}

void RateFileLoader::skipCharesters(QXmlStreamReader& xml)
{
	QXmlStreamReader::TokenType token = xml.readNext();
	while (token == QXmlStreamReader::Characters)
		token = xml.readNext();
}
