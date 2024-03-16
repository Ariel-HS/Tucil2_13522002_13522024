#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget* parent) : QWidget(parent){
    layout = new QGridLayout(this);
    numCPoint = new QSpinBox;
    pointChosen = new QComboBox;
    spbx1 = new QDoubleSpinBox;
    spbx2 = new QDoubleSpinBox;
    iterbox = new QSpinBox;
    lpointChosen = new QLabel(QString("Point:"));
    lspbx1 = new QLabel(QString("X:"));
    lspbx2 = new QLabel(QString("Y:"));
    literbox = new QLabel(QString("Iteration:"));
    lpoints = new QLabel(QString("Points:"));
    lnumpoints = new QLabel(QString(""));
    lnumcpoint = new QLabel(QString("Controls:"));
    butHide = new QPushButton("Hide");
    butApply = new QPushButton("Apply");
    layout->addWidget(lpointChosen, 0, 0);
    layout->addWidget(pointChosen, 0, 1);
    layout->addWidget(lspbx1, 1, 0);
    layout->addWidget(spbx1, 1, 1);
    layout->addWidget(lspbx2, 2, 0);
    layout->addWidget(spbx2, 2, 1);
    layout->addWidget(literbox, 3, 0);
    layout->addWidget(iterbox, 3, 1);
    layout->addWidget(lnumcpoint, 4, 0);
    layout->addWidget(numCPoint, 4, 1);
    layout->addWidget(lpoints, 5, 0);
    layout->addWidget(lnumpoints, 5, 1);
    layout->addWidget(butHide, 6, 0);
    layout->addWidget(butApply, 6, 1);
    for(int i = 0; i < 3; ++i){
        std::string point_name = getPointName(i + 1);
        pointChosen->addItem(QString::fromStdString(point_name));
    }
    pointChosen->setCurrentIndex(0);
    spbx1->setMaximum(10000000000000000);
    spbx1->setMinimum(-10000000000000000);
    spbx2->setMaximum(10000000000000000);
    spbx2->setMinimum(-10000000000000000);
    spbx1->setValue(509);
    spbx2->setValue(31);
    spbx2->setDecimals(2);
    spbx1->setDecimals(2);
    iterbox->setMinimum(1);
    iterbox->setMaximum(100);
    numCPoint->setMinimum(1);
    numCPoint->setMaximum(100);
    QObject::connect(butHide, SIGNAL(clicked()), this, SLOT(hideNow()));
    QObject::connect(butApply, SIGNAL(clicked()), this, SLOT(applyNow()));
    QObject::connect(pointChosen, SIGNAL(activated(int)), this, SLOT(updateByCb(int)));
}

ControlPanel::~ControlPanel(){
    delete layout;
    delete pointChosen;
    delete spbx1;
    delete spbx2;
    delete iterbox;
    delete lpointChosen;
    delete lspbx1;
    delete lspbx2;
    delete literbox;
    delete lpoints;
    delete lnumpoints;
    delete butHide;
    delete butApply;
    delete numCPoint;
    delete lnumcpoint;
}

void ControlPanel::updateControlPanel(ImageView* iv){
    if(iv->n_points != this->pointChosen->count()){
        int lstCur = this->pointChosen->currentIndex();
        this->pointChosen->clear();
        for(int i = 0; i < iv->n_points; ++i){
            std::string point_name = getPointName(i + 1);
            pointChosen->addItem(QString::fromStdString(point_name));
        }
        if(lstCur < this->pointChosen->count()){
            pointChosen->setCurrentIndex(lstCur);
        }else{
            pointChosen->setCurrentIndex(0);
            spbx1->setValue(iv->listPoints.at(0)->scenePos().x());
            spbx2->setValue(iv->listPoints.at(0)->scenePos().y());
        }
    }
    if(iv->dragged != -1){
        pointChosen->setCurrentIndex(iv->dragged);
        spbx1->setValue(iv->listPoints.at(iv->dragged)->scenePos().x());
        spbx2->setValue(iv->listPoints.at(iv->dragged)->scenePos().y());
    }
    iterbox->setValue(iv->iteration);
    lnumpoints->setText(QString::fromStdString(std::to_string(iv->getNumberOfPoints())));
}

std::string ControlPanel::getPointName(int i){
    return "Point " + std::to_string(i);
}

void ControlPanel::hideNow(){
    this->setVisible(false);
}

void ControlPanel::showNow(){
    this->setVisible(true);
}

void ControlPanel::applyNow(){
    this->lnumpoints->setText(QString::fromStdString(std::to_string(1 << this->iterbox->value() | 1)));
    emit applyChanges(this->pointChosen->currentIndex(), this->spbx1->value(), this->spbx2->value(), this->iterbox->value(), this->numCPoint->value());
}

void ControlPanel::updateByCb(int x){
    QPointF* res = nullptr;
    emit getCoordinateFromView(x, res);
    if(res == nullptr){
        return;
    }
    spbx1->setValue(res->x());
    spbx2->setValue(res->y());
    delete res;
}

void ControlPanel::resetControlPanel(ImageView* iv){
    if(iv->n_points != this->pointChosen->count()){
        int lstCur = this->pointChosen->currentIndex();
        this->pointChosen->clear();
        for(int i = 0; i < iv->n_points; ++i){
            std::string point_name = getPointName(i + 1);
            pointChosen->addItem(QString::fromStdString(point_name));
        }
        if(lstCur < this->pointChosen->count()){
            pointChosen->setCurrentIndex(lstCur);
        }else{
            pointChosen->setCurrentIndex(0);
            spbx1->setValue(iv->listPoints.at(0)->scenePos().x());
            spbx2->setValue(iv->listPoints.at(0)->scenePos().y());
        }
    }else{
        int lstCur = this->pointChosen->currentIndex();
        spbx1->setValue(iv->listPoints.at(lstCur)->scenePos().x());
        spbx2->setValue(iv->listPoints.at(lstCur)->scenePos().y());
    }
    if(iv->dragged != -1){
        pointChosen->setCurrentIndex(iv->dragged);
        spbx1->setValue(iv->listPoints.at(iv->dragged)->scenePos().x());
        spbx2->setValue(iv->listPoints.at(iv->dragged)->scenePos().y());
    }

    iterbox->setValue(iv->iteration);
    numCPoint->setValue(iv->listPoints.count() - 2);
    lnumpoints->setText(QString::fromStdString(std::to_string(iv->getNumberOfPoints())));
}
