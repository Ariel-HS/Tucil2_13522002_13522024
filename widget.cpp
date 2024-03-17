#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    setFixedSize(QSize(600, 600));
    setWindowIcon(QIcon(":/bezierAppIcon.png"));
    ui->setupUi(this);
    this->ui->label->hide();
    this->ui->timeLabel->setStyleSheet("QLabel { font-weight: bold; color : green; }");
    connect(this->ui->graphicsView, SIGNAL(yellUpdate(ImageView*)), this->ui->widget, SLOT(updateControlPanel(ImageView*)));
    connect(this->ui->graphicsView, SIGNAL(doubleClicked()), this->ui->widget, SLOT(showNow()));
    connect(this->ui->graphicsView, SIGNAL(doubleClicked()), this->ui->label, SLOT(hide()));
    connect(this->ui->widget->butHide, SIGNAL(clicked()), this->ui->label, SLOT(show()));
    connect(this->ui->widget, SIGNAL(applyChanges(int,double,double,int,int,int)), this->ui->graphicsView, SLOT(applyChanges(int,double,double,int,int,int)));
    connect(this->ui->widget, SIGNAL(getCoordinateFromView(int,QPointF*&)), this->ui->graphicsView, SLOT(sendCoordinateFromView(int,QPointF*&)));
    connect(this->ui->resetButton, SIGNAL(clicked()), this->ui->graphicsView, SLOT(resetView()));
    connect(this->ui->graphicsView, SIGNAL(viewHasBeenReset(ImageView*)), this->ui->widget, SLOT(resetControlPanel(ImageView*)));
    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(this->ui->graphicsView, SIGNAL(changeTimeLabel(int)), this, SLOT(changeTimeLabel(int)));
    this->ui->widget->setAttribute(Qt::WA_StyledBackground, true);
    this->ui->widget->setStyleSheet(".ControlPanel{background-color: rgba(229, 228, 226,0.5)}");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet(".Widget{background-color: rgba(255, 255, 255,1)}");
    this->ui->graphicsView->setFrameStyle(QFrame::NoFrame);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeTimeLabel(int x){
    this->ui->timeLabel->setText(QString::fromStdString(std::to_string(x) + " µs"));
}
