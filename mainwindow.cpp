#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brush.h"
#include "mylabel.h"
#include <QPixmap>
#include <QColorDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , label_       { new MyLabel(this) }
    , image_       { 800, 400 }
    , brushType_   { 1 }
    , brush_       { 1 }
    , line_        { 1 }
    , brushColor_  { 0xff00eeaa }
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set default brushColor to colorWidget
    ui->widget->setStyleSheet("background-color: #ff00eeaa");

    // Updates the pixmap shown by label from the data of our custom image
    auto update_label = [this]
    {
       auto qimage = QImage(
          reinterpret_cast<uchar const*>(image_.data()), image_.width(), image_.height(),
          sizeof(my::image::rgba_t)*image_.width(), QImage::Format_ARGB32
       );

       label_->setPixmap(QPixmap::fromImage( qimage ));
    };

    connect( label_, &MyLabel::onMouseMove, [update_label,this](int x, int y)
    {
       brush_.drawBrush(image_, x, y, brushColor_);
       update_label();
    });

    connect( label_, &MyLabel::onMouseDown, [update_label,this](int x, int y)
    {
       std::cout << "mouse down @ " << x << ", " << y << std::endl;
       if (brush_.GetBrushType() > 3) {
            std::cout << "mouse down @FOR line " << x << ", " << y << std::endl;
            line_.drawLine(image_, line_.lastX, line_.lastY, x, y, brushColor_);
            line_.lastX = x;
            line_.lastY = y;
       } else {
            brush_.drawBrush(image_, x, y, brushColor_);
       }
       update_label();
    });

    connect( ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(setBrushSize(int)));

    label_ -> setParent(ui->canvas);
    update_label();
}

void MainWindow::setBrushSize(int brushSize) {
    std::cout << "Brushing with a size of: " << brushSize << std::endl;
    brush_.SetSize(brushSize);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPen_triggered()
{
    std::cout << "Using Pencil..." << std::endl;
    brush_.SetBrush(1);
}

void MainWindow::on_actionBrush_triggered()
{
    std::cout << "Using Brush..." << std::endl;
    brush_.SetBrush(2);
}

void MainWindow::on_actionInk_Pen_triggered()
{
    std::cout << "Using Ink Pen..." << std::endl;
    brush_.SetBrush(3);
}

void MainWindow::on_pushButton_red_clicked()
{
    std::cout << "Clicked on color red..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ffff0000");
    brushColor_ = 0xffff0000;
}

void MainWindow::on_pushButton_blue_clicked()
{
    std::cout << "Clicked on color blue..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ff0000ff");
    brushColor_ = 0xff0000ff;
}

void MainWindow::on_pushButton_green_clicked()
{
    std::cout << "Clicked on color green..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ff00ff00");
    brushColor_ = 0xff00ff00;
}

void MainWindow::on_pushButton_yellow_clicked()
{
    std::cout << "Clicked on color yellow..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ffffff00");
    brushColor_ = 0xffffff00;
}

void MainWindow::on_pushButton_rosa_clicked()
{
    std::cout << "Clicked on color rosa..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ffff557f");
    brushColor_ = 0xffff557f;
}

void MainWindow::on_pushButton_teal_clicked()
{
    std::cout << "Clicked on color teal..." << std::endl;
    ui->widget->setStyleSheet("background-color: #ff006058");
    brushColor_ = 0xff006058;
}

void MainWindow::on_actionColorPalette_triggered()
{
    std::cout << "Clicked on the nice color picker button!" << std::endl;
    QColor tempCol = QColorDialog::getColor(QColor::fromRgba(brushColor_), this, "Pick a color");
    std::cout << "Selected the nice color " + tempCol.name().toStdString() << std::endl;
    ui->widget->setStyleSheet("background-color: " + tempCol.name());
    brushColor_ = tempCol.rgba();
}

void MainWindow::on_actionLine_triggered()
{
    std::cout << "Clicked on the nice drawLine button!" << std::endl;
    brush_.SetBrush(4);
}
