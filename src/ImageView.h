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
    void applyChanges(int, double, double, int, int, int);
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
    static QPointF getRealCoord(const QPointF&);
    static QPointF getFakeCoord(const QPointF&);
    int getNumberOfPoints();
    QVector<QGraphicsEllipseItem*> listPoints;
    QVector<QGraphicsEllipseItem*> listInterPoints;
    QVector<QPointF*> offsets;
    QVector<QGraphicsTextItem*> coordLabels;
    QVector<QGraphicsTextItem*> landmarkCoord;
    QVector<QGraphicsLineItem*> lines;
    QVector<QGraphicsLineItem*> interLines;
    QVector<QGraphicsLineItem*> coordLines;
    QGraphicsScene* scene;
    QPointF sceneOffset;
    qreal r;
    qreal interRadius;
    qreal m_originX;
    qreal m_originY;
    int dragged;
    int n_points;
    int iteration;
    int calcMethod; // 0 -> dnc, 1 -> bf
    static const int sceneSize = 1000;
    static const int spaceBetweenPoints = 20;
    static const int spaceBetweenPointLabels = 100;

private:
    QVector<QPointF> hardCodedCoords;
    bool contains(QPointF, QPointF);
    void drawCoordinateLines();
};

#endif // IMAGEVIEW_H
