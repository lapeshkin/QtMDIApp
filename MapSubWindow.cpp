#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include "MapSubWindow.h" 
#include "RateChart.h" 
#include "RateMap.h" 
#include "RateFileLoader.h" 

MapSubWindow::MapSubWindow(QtMDIExample* pParent) :
	QWidget(pParent->getMdiArea())
{
    ui.setupUi(this);

    strOnlineResource = "https://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=02/03/2001&date_req2=14/03/2001&VAL_NM_RQ=R01235";
    strFileResource = "I:\\rates.xml";

    resourceButtonsGroup.addButton(ui.radioButtonFromFile);
    resourceButtonsGroup.addButton(ui.radioButtonOnline);
    resourceButtonsGroup.setExclusive(true);
    ui.radioButtonFromFile->setChecked(true);

    setProperty("numSubWindow", 0);
    numSubWindow = 0;

    //mapView = new MapGraphicView(this);
    //ui.mapLayout->addWidget(mapView);

    rateMap = nullptr;
    rateChart = new RateChart(this);
    ui.mapLayout->addWidget(rateChart);

    // Устанавливаю заголовок окна
    this->setWindowTitle("Sub Window");

    QtMDIExample* p = qobject_cast<QtMDIExample*>(pParent);
}

MapSubWindow::~MapSubWindow()
{
}

void MapSubWindow::on_loadButton_clicked()
{
    if (rateMap)
    {
        delete rateMap;
        rateMap = nullptr;
    }

    rateMap = new RateMap(this);
    RateFileLoader loader(rateMap);
    loader.setFileName(ui.resourceName->text());

    if (!loader.load())
    {
        return;
    }

    ui.beginDate->setDate(rateMap->getFirstDate());
    ui.endDate->setDate(rateMap->getLastDate());
    ui.currencyNameLabel->setText(rateMap->getCurrencyCode());

    rateChart->setRateMap(rateMap);
    rateChart->update();

}

void MapSubWindow::on_selectFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select file", "", "XML files (*.xml);;All files (*.*)");
    ui.resourceName->setText(fileName);
}


void MapSubWindow::on_radioButtonFromFile_toggled(bool bChecked)
{
    if (bChecked)
    {
        if (!ui.resourceName->text().isEmpty())
            strOnlineResource = ui.resourceName->text();

        ui.resourceName->setText(strFileResource);
    }
    else
    {
        if (!ui.resourceName->text().isEmpty())
            strFileResource = ui.resourceName->text();

        ui.resourceName->setText(strOnlineResource);
    }

    ui.selectFileButton->setVisible(bChecked);
}
