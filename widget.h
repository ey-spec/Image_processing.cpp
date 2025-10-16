#ifndef WIDGET_H
#define WIDGET_H
#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QString>
#include "Image_Class.h"
#include <QWidget>
#include "filters.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private :
    void loadImage();
    void applyGrayscale();
    void applyBlackWhite();
    void applyInvert();
    void loadSecondImage();
    void on_mergeButton_clicked();
    void on_flipButton_clicked();
    void on_rotateButton_clicked();
    void on_darkenButton_clicked();
    void on_lightenButton_clicked();
    void on_cropButton_clicked();
    void on_frameButton_clicked();
    void on_edgeButton_clicked();
    void on_resizeButton_clicked();
    void on_blurButton_clicked();
    void on_sunlightButton_clicked();
    void on_oilPaintingButton_clicked();
    void on_tvNoiseButton_clicked();
    void on_purpleButton_clicked();
    void on_infraredButton_clicked();
    void on_skewButton_clicked();
    void onMotionBlurClicked();
    void onSepiaClicked();
    void onFilmFilterClicked();
    void onPencilSketchClicked();
    void onUndoClicked();
    void onSaveClicked();
    void onExitClicked();

    void displayImage(const Image &img);

    Ui::Widget *ui;
    Image img, img2;
    Image previousImage;
    bool imageLoaded = false;
    QImage convertToQImage(const Image &img);


};
#endif // WIDGET_H
