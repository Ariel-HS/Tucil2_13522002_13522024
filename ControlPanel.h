#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include "ImageView.h"
#include <QGraphicsOpacityEffect>

class ControlPanel : public QWidget{
    Q_OBJECT

public:
    ControlPanel(QWidget* parent = nullptr);
    virtual ~ControlPanel();

public slots:
    void updateControlPanel(ImageView*);
    void hideNow();
    void showNow();
    void applyNow();
    void updateByCb(int);
    void resetControlPanel(ImageView*);

signals:
    void applyChanges(int, double, double, int, int);
    void getCoordinateFromView(int, QPointF*&);

public:
    QGridLayout* layout;
    QSpinBox* numCPoint;
    QComboBox* pointChosen;
    QDoubleSpinBox* spbx1;
    QDoubleSpinBox* spbx2;
    QSpinBox* iterbox;
    QLabel* lpointChosen;
    QLabel* lspbx1;
    QLabel* lspbx2;
    QLabel* literbox;
    QLabel* lpoints;
    QLabel* lnumpoints;
    QLabel* lnumcpoint;
    QPushButton* butHide;
    QPushButton* butApply;

private:
    std::string getPointName(int);
};

#endif // CONTROLPANEL_H
