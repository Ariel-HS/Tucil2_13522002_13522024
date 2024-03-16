#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsEllipseItem>

class ImageView : public QGraphicsView
{
    Q_OBJECT

public:
    ImageView(QWidget* parent);
    ~ImageView();

public slots:
    void applyChanges(int, double, double, int, int);
    void sendCoordinateFromView(int, QPointF*&);
    void resetView();

signals:
    void yellUpdate(ImageView*);
    void doubleClicked();
    void viewHasBeenReset(ImageView*);
    void changeTimeLabel(int);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    void drawInterPoints();
    int getRandomNumberRange(int, int);
    //virtual void paintEvent(QPaintEvent*) override;

public:
    static QPointF textLabelLocation(const QPointF&);
    static QString coordToStr(const QPointF&);
    int getNumberOfPoints();
    QVector<QGraphicsEllipseItem*> listPoints;
    QVector<QGraphicsEllipseItem*> listInterPoints;
    QVector<QPointF*> offsets;
    QVector<QGraphicsTextItem*> coordLabels;
    QVector<QGraphicsLineItem*> lines;
    QVector<QGraphicsLineItem*> interLines;
    QGraphicsScene* scene;
    qreal r;
    qreal interRadius;
    int dragged;
    int n_points;
    int iteration;

private:
    QVector<QPointF> hardCodedCoords;
};

#endif // IMAGEVIEW_H
