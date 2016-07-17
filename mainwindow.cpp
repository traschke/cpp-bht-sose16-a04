#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "brush.h"
#include "mylabel.h"
#include "history.h"
#include <QPixmap>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageReader>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , label_       { new MyLabel(this) }
    , image_       { 580, 340 }
    , brushType_   { 1 }
    , brush_       { 1 }
    , line_        { 1 }
    , circle_      { }
    , square_      { }
    , brushColor_  { 0xff00eeaa }
    , ui(new Ui::MainWindow)
    , history_(image_)
{
    ui->setupUi(this);

    // Set default brushColor to colorWidget
    ui->widget->setStyleSheet("background-color: #ff00eeaa");

    // Updates the pixmap shown by label from the data of our custom image
    auto update_label = [this]
    {
       auto qimage = QImage(
          reinterpret_cast<uchar const*>(history_.current().data()), history_.current().width(), history_.current().height(),
          sizeof(my::image::rgba_t)*history_.current().width(), QImage::Format_ARGB32
       );
       label_->setPixmap(QPixmap::fromImage( qimage ));
    };

    connect( label_, &MyLabel::onMouseMove, [update_label,this](int x, int y)
    {
        if (x >= brush_.GetSize() &&
                x < (label_->width() - brush_.GetSize()) &&
                y >= brush_.GetSize() &&
                y < (label_->height() - brush_.GetSize())) {
            std::cout << "mouse down @ " << x << ", " << y << std::endl;
            if (brush_.GetBrushType() == 4) {
                 std::cout << "mouse down @FOR line " << x << ", " << y << std::endl;
                 line_.drawLine(history_.current(), x, y, brushColor_);
                 line_.lastX = x;
                 line_.lastY = y;
            } else if (brush_.GetBrushType() == 5) {
                 circle_.radius = brush_.GetSize();
                 circle_.drawCircle(history_.current(), x, y, brushColor_);
            } else if (brush_.GetBrushType() == 6) {
                 square_.a = brush_.GetSize();
                 square_.drawSquare(history_.current(), x, y, brushColor_);
            } else if (brush_.GetBrushType() == 7) {
                triangle_.tileLength = brush_.GetSize()*2;
                triangle_.drawTriangle(history_.current(), x, y, brushColor_);
           } else {
                 brush_.drawBrush(history_.current(), x, y, brushColor_);
                 this->draw(x, y);
            }
            update_label();
        }
    });

    connect( label_, &MyLabel::onMouseDown, [update_label,this](int x, int y)
    {
        if (x >= brush_.GetSize() &&
                x < (label_->width() - brush_.GetSize()) &&
                y >= brush_.GetSize() &&
                y < (label_->height() - brush_.GetSize())) {
        this->makeHistory();
           std::cout << "mouse down @ " << x << ", " << y << std::endl;
           if (brush_.GetBrushType() == 4) {
                std::cout << "mouse down @FOR line " << x << ", " << y << std::endl;
                line_.drawLine(history_.current(), x, y, brushColor_);
                line_.lastX = x;
                line_.lastY = y;
           } else if (brush_.GetBrushType() == 5) {
                circle_.radius = brush_.GetSize();
                circle_.drawCircle(history_.current(), x, y, brushColor_);
           } else if (brush_.GetBrushType() == 6) {
                square_.a = brush_.GetSize();
                square_.drawSquare(history_.current(), x, y, brushColor_);
           } else if (brush_.GetBrushType() == 7) {
               triangle_.tileLength = brush_.GetSize()*2;
               triangle_.drawTriangle(history_.current(), x, y, brushColor_);
          } else {
                brush_.drawBrush(history_.current(), x, y, brushColor_);
           }
           update_label();
        }
       /* Habe dein draw mal auskomentiert wegen merge und so.
        draw(x, y);
        update_label();
        */
    });

    connect (ui->actionClear_Background, &QAction::triggered, this, &MainWindow::on_actionBackground_triggered);
    connect (ui->actionSave, &QAction::triggered, this, &MainWindow::SaveToFile);
    connect (ui->actionOpen, &QAction::triggered, this, &MainWindow::OpenFromFile);
    connect (ui->actionUndo, &QAction::triggered, this, &MainWindow::Undo);

    connect( ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(setBrushSize(int)));
    label_ -> setParent(ui->canvas);
    update_label();

    // Initialize Settings
    brush_.SetBrush(1);
    setBrushSize(2);
    history_.commit(history_.current());
}

void MainWindow::update_label()
{
   auto qimage = QImage(
      reinterpret_cast<uchar const*>(history_.current().data()), history_.current().width(), history_.current().height(),
      sizeof(my::image::rgba_t)*history_.current().width(), QImage::Format_ARGB32
   );
   label_->setPixmap(QPixmap::fromImage( qimage ));
}

void MainWindow::makeHistory() {
    history_.commit(history_.current());
}

void MainWindow::draw(int x, int y) {
    std::cout << "Label: " << label_->width() << "x" << label_->height() << std::endl;
    std::cout << "Mouse: " << x << " " << y << std::endl;
    std::cout << "Brush: " << brush_.GetSize() << std::endl;
    if (x >= brush_.GetSize() &&
            x < (label_->width() - brush_.GetSize()) &&
            y >= brush_.GetSize() &&
            y < (label_->height() - brush_.GetSize())) {
        std::cout << "JO" << std::endl;
        brush_.drawBrush(history_.current(), x, y, brushColor_);
    }
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

void MainWindow::on_actionBackground_triggered() {
    history_.commit(history_.current());
    std::cout << "Reset background" << std::endl;
    history_.current().ClearBackground(brushColor_);
    update_label();
}

void MainWindow::SaveToFile(){
    QString name = QFileDialog::getSaveFileName(this, tr("Save File"),
                                           "untitled.jpg",
                                           tr("Images (*.png *.xpm *.jpg)"));
    label_->pixmap()->save(name,0, 100);

}

void MainWindow::OpenFromFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    QImageReader reader(fileName);
    QImage img = reader.read();

    history_.current().LoadData(img);

    label_->resize(img.width(), img.height());
    update_label();
}

void MainWindow::Undo() {
    history_.Undo();
    update_label();
}

void MainWindow::on_actionCircle_triggered()
{
    std::cout << "Clicked on the circle button, now drawing nice circle!" << std::endl;
    brush_.SetBrush(5);
}

void MainWindow::on_actionRectangle_triggered()
{
    std::cout << "Clicked on the square button, now drawing nice square!" << std::endl;
    brush_.SetBrush(6);
}

void MainWindow::on_actionTriangle_triggered()
{
    std::cout << "Clicked on the triangle button, now drawing nice triangle!" << std::endl;
    brush_.SetBrush(7);
}
