#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mylabel.h"
#include <QPixmap>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , label_       { new MyLabel(this) }
    , image_       { 800, 400 }
    , usePencil_   { true }
    , useBrush_    { false }
    , toolSize_    { 1 }
    , brushColor_  { 0xff00eeaa }
    ,  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
       std::cout << "mouse move: " << x << ", " << y << std::endl;
       if( toolSize_ >= 2 && usePencil_) {
           std::cout << "Draw pencil..." << std::endl;
           for (int i = 0; i < toolSize_/2; ++i) {
                image_.set_pixel( x-i, y-i, brushColor_ );
                image_.set_pixel( x, y-i, brushColor_ );
                image_.set_pixel( x+i, y-i, brushColor_ );

                image_.set_pixel( x-i, y, brushColor_ );
                image_.set_pixel( x, y, brushColor_ );
                image_.set_pixel( x+i, y, brushColor_ );

                image_.set_pixel( x-i, y+i, brushColor_ );
                image_.set_pixel( x, y+i, brushColor_ );
                image_.set_pixel( x+i, y+i, brushColor_ );
           }
       } else if( toolSize_ >= 2 && useBrush_) {
           std::cout << "Draw brush..." << std::endl;
           for (int i = 0; i < toolSize_/2; ++i) {
                image_.set_pixel( x+i, y+i, brushColor_ );
                image_.set_pixel( x-i, y-i, brushColor_ );
           }
       } else {
           std::cout << "Set a small pixel..." << std::endl;
           image_.set_pixel( x, y, brushColor_ );
       }
       update_label();
    });

    connect( label_, &MyLabel::onMouseDown, [update_label,this](int x, int y)
    {
       std::cout << "mouse down @ " << x << ", " << y << std::endl;
       update_label();
    });

    connect( ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(setBrushSize(int)));

    label_ -> setParent(ui->canvas);
    update_label();
}

void MainWindow::setBrushSize(int brushSize) {
    std::cout << "Brushing with a size of: " << brushSize << std::endl;
    toolSize_ = brushSize;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStift_triggered()
{
    std::cout << "Using Pencil..." << std::endl;
    usePencil_ = true;
    useBrush_  = false;
}

void MainWindow::on_actionPinsel_triggered()
{
    std::cout << "Using Brush..." << std::endl;
    usePencil_ = false;
    useBrush_  = true;
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
