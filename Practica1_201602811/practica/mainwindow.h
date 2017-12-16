#ifndef MAINWINDOW_H
#include <fstream>
#include <QtGui>
#define MAINWINDOW_H
#include <QGraphicsObject>
#include <QMainWindow>
#include <QImage>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPaintDevice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_editingFinished();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_spinBox_2_editingFinished();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
