#pragma once

#include <QMainWindow>
#include "image.h"
#include "ui_mainwindow.h"
#include "brush.h"
#include "line.h"
#include "history.h"
#include "circle.h"
#include "square.h"
#include "triangle.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT

   class MyLabel*       label_;
   my::image            image_;
   Brush                brush_;
   Line                 line_;
   Circle               circle_;
   Square               square_;
   Triangle             triangle_;
   int                  brushType_;
   my::image::rgba_t    brushColor_;
   my::history          history_;


public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void makeHistory();

   void draw(int x, int y);

   void setBrushSize(int brushSize);

   void on_actionPen_triggered();

   void on_actionBrush_triggered();

   void on_actionInk_Pen_triggered();

   void on_pushButton_red_clicked();

   void on_pushButton_blue_clicked();

   void on_pushButton_green_clicked();

   void on_pushButton_yellow_clicked();

   void on_pushButton_rosa_clicked();

   void on_pushButton_teal_clicked();

   void on_actionColorPalette_triggered();

   void on_actionLine_triggered();

   void on_actionBackground_triggered();

   void on_actionCircle_triggered();

   void on_actionRectangle_triggered();

   void on_actionTriangle_triggered();

private:
   Ui::MainWindow *ui;
   void update_label();
   void SaveToFile();
   void OpenFromFile();
   void Undo();
};
