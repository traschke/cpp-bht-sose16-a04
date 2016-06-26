#pragma once

#include <QMainWindow>
#include "image.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

   class MyLabel*  label_;
   my::image       image_;
   bool            usePencil_;
   bool            useBrush_;
   int             toolSize_;
   size_t          brushColor_;

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void setBrushSize(int brushSize);

   void on_actionStift_triggered();

   void on_actionPinsel_triggered();

   void on_pushButton_red_clicked();

   void on_pushButton_blue_clicked();

   void on_pushButton_green_clicked();

   void on_pushButton_yellow_clicked();

   void on_pushButton_rosa_clicked();

   void on_pushButton_teal_clicked();

private:
   Ui::MainWindow *ui;

};
