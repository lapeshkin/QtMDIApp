This is a test application in Qt created based on MDI (QMdiArea). 
The solution is built on the Visual Studio 2022 platform, using Qt version 5.15.2.

In the "ratechart" branch, loading from an XML file and displaying exchange rates is implemented. 
Currently, only loading from file is implemented. 
You can download the file following the instructions at https://www.cbr.ru/development/sxml/ (example #2).

To display exchange rates, the RateChart class is used, which is inherited from QWidget. The rendering takes place in the paintEvent method, using the QPixmap class.

Data is loaded into an instance of the RateMap class using the friend class RateFileLoader and then passed for rendering to the RateChart class.
