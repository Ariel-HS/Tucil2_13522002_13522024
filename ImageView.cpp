#include "ImageView.h"

#include <QMouseEvent>
#include <QScrollBar>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <QDoubleSpinBox>
#include <QGraphicsProxyWidget>
#include "bezier.h"


QPointF ImageView::textLabelLocation(const QPointF& f){
    QPointF ans(f.x() + 10, f.y() - 20);
    return ans;
}

QString ImageView::coordToStr(const QPointF& f){
    int setPrecisionx, setPrecisiony;
    double curx = f.x() - floor(f.x());
    double cury = f.y() - floor(f.y());
    if(curx < 0.01){
        setPrecisionx = 0;
    }else{
        int lastTwo = round(curx * 100);
        if(lastTwo % 10 == 0){
            setPrecisionx = 1;
        }else{
            setPrecisionx = 2;
        }
    }
    if(cury < 0.01){
        setPrecisiony = 0;
    }else{
        int lastTwo = round(cury * 100);
        if(lastTwo % 10 == 0){
            setPrecisiony = 1;
        }else{
            setPrecisiony = 2;
        }
    }
    std::stringstream streamx, streamy;
    streamx << std::fixed << std::setprecision(setPrecisionx) << f.x();
    streamy << std::fixed << std::setprecision(setPrecisiony) << f.y();
    std::string xpart = streamx.str();
    std::string ypart = streamy.str();
    std::string ans = "(" + xpart + "," + ypart + ")";
    return QString::fromStdString(ans);
}

ImageView::ImageView(QWidget *parent) : QGraphicsView(parent){
    r = 8;
    interRadius = 3;
    iteration = 1;
    this->scene = new QGraphicsScene;
    this->n_points = 3;
    this->dragged = -1;
    QVector<QColor> list_of_colors = {Qt::red, Qt::green, Qt::red, Qt::magenta, Qt::yellow}; // PANJANG HANYA 5!!!
    hardCodedCoords.append(QPointF(509,31));
    hardCodedCoords.append(QPointF(55,31));
    hardCodedCoords.append(QPointF(55,430));
    hardCodedCoords.append(QPointF(390,430));
    hardCodedCoords.append(QPointF(390,127));
    hardCodedCoords.append(QPointF(155,127));
    hardCodedCoords.append(QPointF(155,360));
    hardCodedCoords.append(QPointF(315,360));
    hardCodedCoords.append(QPointF(315,202));
    hardCodedCoords.append(QPointF(206,202));
    hardCodedCoords.append(QPointF(206,300));
    hardCodedCoords.append(QPointF(283,300));
    for(int i = 0; i < this->n_points; ++i){
        QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, r, r);
        p1->setPos(hardCodedCoords.at(i));
        QGraphicsTextItem* coords = new QGraphicsTextItem(coordToStr(p1->scenePos()));
        coords->setPos(textLabelLocation(p1->scenePos()));
        this->coordLabels.append(coords);
        QFont f("Calibri", 11);
        coords->setFont(f);
        coords->setDefaultTextColor(QColor(0, 0, 255));
        p1->setPen(QPen(list_of_colors.at(i)));
        p1->setBrush(QBrush(list_of_colors.at(i)));
        listPoints.append(p1);
        QPointF* qp = new QPointF(-1, -1);
        offsets.append(qp);
        //scene->addItem(coords);
        //scene->addItem(p1);
    }
    for(int i = 0; i < this->n_points - 1; ++i){
        QPointF curF = listPoints.at(i)->scenePos();
        QPointF curS = listPoints.at(i + 1)->scenePos();
        QLineF* l1 = new QLineF(curF.x() + r / 2, curF.y() + r / 2, curS.x() + r / 2, curS.y() + r / 2);
        QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
        QPen pen1(Qt::blue);
        pen1.setStyle(Qt::DashLine);
        scene->addItem(l2);
        l2->setPen(pen1);
        lines.append(l2);
    }
    for(int i = 0; i < this->n_points; ++i){
        listPoints.at(i)->setZValue(1);
        scene->addItem(listPoints.at(i));
        scene->addItem(coordLabels.at(i));
    }
    vector<Point> startPoints;
    for(int i = 0; i < this->n_points; ++i){
        Point newPoint = {listPoints.at(i)->scenePos().x(), listPoints.at(i)->scenePos().y()};
        startPoints.push_back(newPoint);
    }
    vector<Point> resultInterPointStart = recurse(0, this->iteration, startPoints);
    for(int i = 0; i < (int)resultInterPointStart.size(); ++i){
        QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, interRadius, interRadius);
        p1->setPos(QPointF(resultInterPointStart[i].x, resultInterPointStart[i].y));
        p1->setPen(QPen(Qt::blue));
        p1->setBrush(QBrush(Qt::blue));
        p1->setZValue(1);
        p1->setVisible(true);
        scene->addItem(p1);
        listInterPoints.append(p1);
    }
    listInterPoints.front()->setVisible(false);
    listInterPoints.back()->setVisible(false);
    for(int i = 0; i < (int)listInterPoints.count() - 1; ++i){
        QPointF curF = listInterPoints.at(i)->scenePos();
        QPointF curS = listInterPoints.at(i + 1)->scenePos();
        qreal r1, r2;
        if(i == 0){
            r1 = r;
        }else{
            r1 = interRadius;
        }
        if(i == (int)listInterPoints.count() - 2){
            r2 = r;
        }else{
            r2 = interRadius;
        }
        QLineF* l1 = new QLineF(curF.x() + r1 / 2, curF.y() + r1 / 2, curS.x() + r2 / 2, curS.y() + r2 / 2);
        QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
        QPen pen1(Qt::black);
        scene->addItem(l2);
        l2->setPen(pen1);
        l2->setZValue(0);
        interLines.append(l2);
    }
    scene->setSceneRect(0, 0, 600, 600);
    this->setSceneRect(scene->sceneRect());
    this->setScene(scene);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->show();
}

ImageView::~ImageView(){
    for(int i = 0; i < this->n_points; ++i){
        delete listPoints.at(i);
        delete coordLabels.at(i);
        delete offsets.at(i);
        if(i != this->n_points - 1) delete lines.at(i);
    }
    for(int i = 0; i < this->listInterPoints.count(); ++i){
        delete listInterPoints.at(i);
        if(i != this->listInterPoints.count() - 1) delete interLines.at(i);
    }
    delete scene;
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    for(int i = this->n_points - 1; i >= 0; --i){
        if(listPoints.at(i)->contains(listPoints.at(i)->mapFromScene(event->position()))){
            this->dragged = i;
            break;
        }
    }
    if(this->dragged == -1) return;
    *(this->offsets[this->dragged]) = event->pos();
    emit yellUpdate(this);
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton)){
        return;
    }
    if(this->dragged == -1){
        return;
    }
    listPoints.at(this->dragged)->setPos(listPoints.at(this->dragged)->pos() + (event->position() - *(offsets.at(this->dragged))));
    coordLabels.at(this->dragged)->setPos(textLabelLocation(listPoints.at(this->dragged)->pos()));
    coordLabels.at(this->dragged)->setPlainText(coordToStr(listPoints.at(this->dragged)->pos()));
    *(this->offsets[this->dragged]) = event->pos();
    for(int i = 0; i < this->n_points - 1; ++i){
        QPointF curF = listPoints.at(i)->scenePos();
        QPointF curS = listPoints.at(i + 1)->scenePos();
        QLineF* l1 = new QLineF(curF.x() + r / 2, curF.y() + r / 2, curS.x() + r / 2, curS.y() + r / 2);
        lines.at(i)->setLine(*l1);
    }
    vector<Point> startPoints;
    for(int i = 0; i < this->n_points; ++i){
        Point newPoint = {listPoints.at(i)->scenePos().x(), listPoints.at(i)->scenePos().y()};
        startPoints.push_back(newPoint);
    }
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
    vector<Point> resultInterPointStart = recurse(0, this->iteration, startPoints);
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    for(int i = 0; i < (int)resultInterPointStart.size(); ++i){
        listInterPoints.at(i)->setPos(QPointF(resultInterPointStart[i].x, resultInterPointStart[i].y));
    }
    for(int i = 0; i < (int)listInterPoints.count() - 1; ++i){
        QPointF curF = listInterPoints.at(i)->scenePos();
        QPointF curS = listInterPoints.at(i + 1)->scenePos();
        qreal r1, r2;
        if(i == 0){
            r1 = r;
        }else{
            r1 = interRadius;
        }
        if(i == (int)listInterPoints.count() - 2){
            r2 = r;
        }else{
            r2 = interRadius;
        }
        QLineF* l1 = new QLineF(curF.x() + r1 / 2, curF.y() + r1 / 2, curS.x() + r2 / 2, curS.y() + r2 / 2);
        interLines.at(i)->setLine(*l1);
    }
    int dur = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();
    emit changeTimeLabel(dur);
    emit yellUpdate(this);
}

void ImageView::mouseReleaseEvent(QMouseEvent*){
    if(this->dragged == -1) return;
    this->dragged = -1;
}

int ImageView::getNumberOfPoints(){
    return (1 << this->iteration) | 1;
}

void ImageView::mouseDoubleClickEvent(QMouseEvent*){
    emit doubleClicked();
}

void ImageView::applyChanges(int curFocus, double posx, double posy, int numIter, int numC){
    if(this->iteration != numIter){
        this->iteration = numIter;
        drawInterPoints();
    }
    numC += 2;
    if(numC != this->n_points){
        bool less = false;
        int prev = this->n_points;
        for(; this->n_points > numC; --this->n_points){
            int n = this->n_points;
            delete listPoints.back();
            delete offsets.back();
            listPoints.pop_back();
            offsets.pop_back();
            delete coordLabels.back();
            coordLabels.pop_back();
            if(n - 2 < this->lines.size()){
                delete lines.at(n - 2);
                lines.pop_back();
            }
        }
        for(; this->n_points < numC; ++this->n_points){
            less = true;
            QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, r, r);
            if(this->n_points >= this->hardCodedCoords.count()){
                p1->setPos(this->getRandomNumberRange(0, 500), this->getRandomNumberRange(0, 500));
            }else{
                p1->setPos(hardCodedCoords.at(this->n_points));
            }
            QGraphicsTextItem* coords = new QGraphicsTextItem(coordToStr(p1->scenePos()));
            coords->setPos(textLabelLocation(p1->scenePos()));
            this->coordLabels.append(coords);
            QFont f("Calibri", 11);
            coords->setFont(f);
            coords->setDefaultTextColor(QColor(0, 0, 255));
            p1->setPen(QPen(Qt::red));
            p1->setBrush(QBrush(Qt::red));
            listPoints.append(p1);
            QPointF* qp = new QPointF(-1, -1);
            offsets.append(qp);
        }
        if(less){
            for(int i = prev - 1; i < this->n_points - 1; ++i){
                QPointF curF = listPoints.at(i)->scenePos();
                QPointF curS = listPoints.at(i + 1)->scenePos();
                QLineF* l1 = new QLineF(curF.x() + r / 2, curF.y() + r / 2, curS.x() + r / 2, curS.y() + r / 2);
                QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
                QPen pen1(Qt::blue);
                pen1.setStyle(Qt::DashLine);
                scene->addItem(l2);
                l2->setPen(pen1);
                lines.append(l2);
            }
            for(int i = prev; i < this->n_points; ++i){
                scene->addItem(listPoints.at(i));
                scene->addItem(coordLabels.at(i));
            }
        }
        for(int i = 0; i < this->n_points; ++i){
            if(i == 0 || i == this->n_points - 1){
                this->listPoints.at(i)->setBrush(QBrush(Qt::red));
                this->listPoints.at(i)->setPen(QPen(Qt::red));
            }else{
                this->listPoints.at(i)->setBrush(QBrush(Qt::green));
                this->listPoints.at(i)->setPen(QPen(Qt::green));
            }
            this->listPoints.at(i)->setZValue(1);
            this->coordLabels.at(i)->setZValue(2);
        }
        drawInterPoints();
    }
    if(curFocus < this->n_points){
        listPoints.at(curFocus)->setPos(QPointF(posx, posy));
        coordLabels.at(curFocus)->setPos(textLabelLocation(listPoints.at(curFocus)->pos()));
        coordLabels.at(curFocus)->setPlainText(coordToStr(listPoints.at(curFocus)->pos()));
        *(this->offsets[curFocus]) = QPointF(posx, posy);
        drawInterPoints();
    }
    for(int i = 0; i < this->n_points - 1; ++i){
        QPointF curF = listPoints.at(i)->scenePos();
        QPointF curS = listPoints.at(i + 1)->scenePos();
        QLineF* l1 = new QLineF(curF.x() + r / 2, curF.y() + r / 2, curS.x() + r / 2, curS.y() + r / 2);
        lines.at(i)->setLine(*l1);
    }
    emit yellUpdate(this);
}

void ImageView::sendCoordinateFromView(int x, QPointF* &qf){
    if(x >= listPoints.size()) return;
    qf = new QPointF(listPoints.at(x)->scenePos());
}

void ImageView::drawInterPoints(){
    //qDebug() << "here";
    vector<Point> pointsNow;
    for(int i = 0; i < this->n_points; ++i){
        Point conv = {listPoints.at(i)->scenePos().x(), listPoints.at(i)->scenePos().y()};
        pointsNow.push_back(conv);
    }
    std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
    vector<Point> intermPoints = recurse(0, this->iteration, pointsNow);
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    while(listInterPoints.count() > (long long)intermPoints.size()){
        delete listInterPoints.back();
        listInterPoints.pop_back();
        delete interLines.back();
        interLines.pop_back();
    }
    for(int i = 0; i < (int)intermPoints.size(); ++i){
        if(i >= listInterPoints.count()){
            QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, interRadius, interRadius);
            p1->setPos(QPointF(intermPoints[i].x, intermPoints[i].y));
            p1->setPen(QPen(Qt::blue));
            p1->setBrush(QBrush(Qt::blue));
            p1->setZValue(1);
            p1->setVisible(true);
            scene->addItem(p1);
            listInterPoints.append(p1);
        }else{
            listInterPoints.at(i)->setVisible(true);
            listInterPoints.at(i)->setPos(QPointF(intermPoints[i].x, intermPoints[i].y));
        }
    }
    listInterPoints.front()->setVisible(false);
    listInterPoints.back()->setVisible(false);
    for(int i = 0; i < listInterPoints.count() - 1; ++i){
        if(i >= interLines.count()){
            QPointF curF = listInterPoints.at(i)->scenePos();
            QPointF curS = listInterPoints.at(i + 1)->scenePos();
            qreal r1, r2;
            if(i == 0){
                r1 = r;
            }else{
                r1 = interRadius;
            }
            if(i == (int)listInterPoints.count() - 2){
                r2 = r;
            }else{
                r2 = interRadius;
            }
            QLineF* l1 = new QLineF(curF.x() + r1 / 2, curF.y() + r1 / 2, curS.x() + r2 / 2, curS.y() + r2 / 2);
            QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
            QPen pen1(Qt::black);
            scene->addItem(l2);
            l2->setPen(pen1);
            interLines.append(l2);
        }else{
            QPointF curF = listInterPoints.at(i)->scenePos();
            QPointF curS = listInterPoints.at(i + 1)->scenePos();
            qreal r1, r2;
            if(i == 0){
                r1 = r;
            }else{
                r1 = interRadius;
            }
            if(i == (int)listInterPoints.count() - 2){
                r2 = r;
            }else{
                r2 = interRadius;
            }
            QLineF* l1 = new QLineF(curF.x() + r1 / 2, curF.y() + r1 / 2, curS.x() + r2 / 2, curS.y() + r2 / 2);
            interLines.at(i)->setLine(*l1);
        }
    }
    int dur = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();
    emit changeTimeLabel(dur);
}

void ImageView::resetView(){
    for(int i = 0; i < this->n_points; ++i){
        delete listPoints.at(i);
        delete coordLabels.at(i);
        delete offsets.at(i);
        if(i != this->n_points - 1) delete lines.at(i);
    }
    for(int i = 0; i < this->listInterPoints.count(); ++i){
        delete listInterPoints.at(i);
        if(i != this->listInterPoints.count() - 1) delete interLines.at(i);
    }
    listPoints.clear();
    coordLabels.clear();
    offsets.clear();
    lines.clear();
    listInterPoints.clear();
    interLines.clear();
    iteration = 1;
    this->n_points = 3;
    this->dragged = -1;
    QVector<QColor> list_of_colors = {Qt::red, Qt::green, Qt::red, Qt::magenta, Qt::yellow}; // PANJANG HANYA 5!!!
    for(int i = 0; i < this->n_points; ++i){
        QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, r, r);
        p1->setPos(hardCodedCoords.at(i));
        QGraphicsTextItem* coords = new QGraphicsTextItem(coordToStr(p1->scenePos()));
        coords->setPos(textLabelLocation(p1->scenePos()));
        this->coordLabels.append(coords);
        QFont f("Calibri", 11);
        coords->setFont(f);
        coords->setDefaultTextColor(QColor(0, 0, 255));
        p1->setPen(QPen(list_of_colors.at(i)));
        p1->setBrush(QBrush(list_of_colors.at(i)));
        listPoints.append(p1);
        QPointF* qp = new QPointF(-1, -1);
        offsets.append(qp);
        //scene->addItem(coords);
        //scene->addItem(p1);
    }
    for(int i = 0; i < this->n_points - 1; ++i){
        QPointF curF = listPoints.at(i)->scenePos();
        QPointF curS = listPoints.at(i + 1)->scenePos();
        QLineF* l1 = new QLineF(curF.x() + r / 2, curF.y() + r / 2, curS.x() + r / 2, curS.y() + r / 2);
        QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
        QPen pen1(Qt::blue);
        pen1.setStyle(Qt::DashLine);
        scene->addItem(l2);
        l2->setPen(pen1);
        lines.append(l2);
    }
    for(int i = 0; i < this->n_points; ++i){
        listPoints.at(i)->setZValue(1);
        scene->addItem(listPoints.at(i));
        scene->addItem(coordLabels.at(i));
    }
    vector<Point> startPoints;
    for(int i = 0; i < this->n_points; ++i){
        Point newPoint = {listPoints.at(i)->scenePos().x(), listPoints.at(i)->scenePos().y()};
        startPoints.push_back(newPoint);
    }
    vector<Point> resultInterPointStart = recurse(0, this->iteration, startPoints);
    for(int i = 0; i < (int)resultInterPointStart.size(); ++i){
        QGraphicsEllipseItem* p1 = new QGraphicsEllipseItem(0, 0, interRadius, interRadius);
        p1->setPos(QPointF(resultInterPointStart[i].x, resultInterPointStart[i].y));
        p1->setPen(QPen(Qt::blue));
        p1->setBrush(QBrush(Qt::blue));
        p1->setZValue(1);
        p1->setVisible(true);
        scene->addItem(p1);
        listInterPoints.append(p1);
    }
    listInterPoints.front()->setVisible(false);
    listInterPoints.back()->setVisible(false);
    for(int i = 0; i < (int)listInterPoints.count() - 1; ++i){
        QPointF curF = listInterPoints.at(i)->scenePos();
        QPointF curS = listInterPoints.at(i + 1)->scenePos();
        qreal r1, r2;
        if(i == 0){
            r1 = r;
        }else{
            r1 = interRadius;
        }
        if(i == (int)listInterPoints.count() - 2){
            r2 = r;
        }else{
            r2 = interRadius;
        }
        QLineF* l1 = new QLineF(curF.x() + r1 / 2, curF.y() + r1 / 2, curS.x() + r2 / 2, curS.y() + r2 / 2);
        QGraphicsLineItem* l2 = new QGraphicsLineItem(*l1);
        QPen pen1(Qt::black);
        scene->addItem(l2);
        l2->setPen(pen1);
        l2->setZValue(0);
        interLines.append(l2);
    }
    emit viewHasBeenReset(this);
}

int ImageView::getRandomNumberRange(int x, int y){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution_rand(x, y); // distribution in range [1, 6]
    return distribution_rand(rng);
}

/*
void ImageView::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(0, 0, 200, 200);
}*/

