#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QWidget>

namespace Ui {
class DataDisplay;
}

class DataDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit DataDisplay(QWidget *parent = nullptr);
    ~DataDisplay();
public slots:
    void setSymbol(QString s);
    void updateValue(double value, int direction=1);
private:
    Ui::DataDisplay *ui;
};

#endif // DATADISPLAY_H
