#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QPixmap>
#include "filters.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>


Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->loadButton, &QPushButton::clicked, this, &Widget::loadImage);
    connect(ui->grayscaleButton, &QPushButton::clicked, this, &Widget::applyGrayscale);
    connect(ui->blackandwhiteButton, &QPushButton::clicked, this, &Widget::applyBlackWhite);
    connect(ui->invertButton, &QPushButton::clicked, this, &Widget::applyInvert);
    connect(ui->mergeButton, &QPushButton::clicked, this, &Widget::on_mergeButton_clicked);
    connect(ui->flipButton, &QPushButton::clicked, this, &Widget::on_flipButton_clicked);
    connect(ui->rotateButton, &QPushButton::clicked, this, &Widget::on_rotateButton_clicked);
    connect(ui->lightenButton, &QPushButton::clicked, this, &Widget::on_lightenButton_clicked);
    connect(ui->darkenButton, &QPushButton::clicked, this, &Widget::on_darkenButton_clicked);
    connect(ui->cropButton, &QPushButton::clicked, this, &Widget::on_cropButton_clicked);
    connect(ui->frameButton, &QPushButton::clicked, this, &Widget::on_frameButton_clicked);
    connect(ui->edgeButton, &QPushButton::clicked, this, &Widget::on_edgeButton_clicked);
    connect(ui->resizeButton, &QPushButton::clicked, this, &Widget::on_resizeButton_clicked);
    connect(ui->blurButton, &QPushButton::clicked, this, &Widget::on_blurButton_clicked);
    connect(ui->sunlightButton, &QPushButton::clicked, this, &Widget::on_sunlightButton_clicked);
    connect(ui->oilpaintingButton, &QPushButton::clicked, this, &Widget::on_oilPaintingButton_clicked);
    connect(ui->tvButton, &QPushButton::clicked, this, &Widget::on_tvNoiseButton_clicked);
    connect(ui->purpleButton, &QPushButton::clicked, this, &Widget::on_purpleButton_clicked);
    connect(ui->infraredButton, &QPushButton::clicked, this, &Widget::on_infraredButton_clicked);
    connect(ui->skewButton, &QPushButton::clicked, this, &Widget::on_skewButton_clicked);
    connect(ui->motionblurButton, &QPushButton::clicked, this, &Widget::onMotionBlurClicked);
    connect(ui->sepiaButton, &QPushButton::clicked, this, &Widget::onSepiaClicked);
    connect(ui->pencilButton, &QPushButton::clicked, this, &Widget::onPencilSketchClicked);
    connect(ui->filmButton, &QPushButton::clicked, this, &Widget::onFilmFilterClicked);
    connect(ui->undo, &QPushButton::clicked, this, &Widget::onUndoClicked);
    connect(ui->save, &QPushButton::clicked, this, &Widget::onSaveClicked);
    connect(ui->exit, &QPushButton::clicked, this, &Widget::onExitClicked);
}

Widget::~Widget()
{
    delete ui;
}

QImage Widget::convertToQImage(const Image &img)
{
    QImage qimg(img.width, img.height, QImage::Format_RGB888);
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++)
        {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);
            qimg.setPixel(x, y, qRgb(r, g, b));
        }
    return qimg;
}

void Widget::loadImage()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (filename.isEmpty()) return;

    img.loadNewImage(filename.toStdString());
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
    imageLoaded = true;

}

void Widget::displayImage(const Image &img)
{
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::applyGrayscale()
{
    if (img.width == 0 || img.height == 0) return;
    previousImage = img;
    Apply_Grayscale_filter(img);
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::applyBlackWhite()
{
    if (img.width == 0 || img.height == 0)
        return;
    previousImage = img;
    Apply_black_white_filter(img);
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::applyInvert()
{
    if (img.width == 0 || img.height == 0)
        return;
    previousImage = img;
    Apply_Invert_filter(img);  // 👈 استدعاء الفلتر
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_mergeButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load the first image before merging.");
        return;
    }
    previousImage = img;
    // الخطوة 1: تحميل الصورة الثانية
    QString secondFilename = QFileDialog::getOpenFileName(this, "Select Image to Merge", "", "Images (*.png *.jpg *.bmp)");
    if (secondFilename.isEmpty()) return;

    Image img2;
    try {
        img2.loadNewImage(secondFilename.toStdString());
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", QString("Failed to load second image: %1").arg(e.what()));
        return;
    }

    // الخطوة 2: إنشاء نافذة خيارات
    QMessageBox msgBox;
    msgBox.setWindowTitle("Choose Merge Option");
    msgBox.setText("How would you like to merge the images?");
    QPushButton *resizeBtn = msgBox.addButton("Resize smaller image", QMessageBox::AcceptRole);
    QPushButton *commonBtn = msgBox.addButton("Merge common area only", QMessageBox::RejectRole);
    msgBox.exec();

    // الخطوة 3: تحديد الاختيار وتنفيذ الدمج
    MergeOption option;
    if (msgBox.clickedButton() == resizeBtn)
        option = ResizeToMatch;
    else
        option = CommonArea;

    Apply_Merge_Filter(img, img2, option);

    // الخطوة 4: عرض النتيجة
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_flipButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first.");
        return;
    }
    previousImage = img;
    // نافذة الاختيار بين horizontal و vertical
    QMessageBox msgBox;
    msgBox.setWindowTitle("Flip Options");
    msgBox.setText("Choose flip direction:");

    QPushButton *horizontalBtn = msgBox.addButton("Horizontal", QMessageBox::AcceptRole);
    QPushButton *verticalBtn = msgBox.addButton("Vertical", QMessageBox::RejectRole);

    msgBox.exec();

    // تحديد نوع الفليب
    FlipType flipType;
    if (msgBox.clickedButton() == horizontalBtn)
        flipType = Horizontal;
    else
        flipType = Vertical;

    // تطبيق الفلتر
    Apply_Flip_Filter(img, flipType);

    // عرض النتيجة
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_rotateButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first.");
        return;
    }
    previousImage = img;
    // نافذة اختيار الزاوية
    QMessageBox msgBox;
    msgBox.setWindowTitle("Rotate Options");
    msgBox.setText("Choose rotation angle:");

    QPushButton *btn90 = msgBox.addButton("90°", QMessageBox::AcceptRole);
    QPushButton *btn180 = msgBox.addButton("180°", QMessageBox::AcceptRole);
    QPushButton *btn270 = msgBox.addButton("270°", QMessageBox::AcceptRole);

    msgBox.exec();

    int angle = 0;
    if (msgBox.clickedButton() == btn90)
        angle = 90;
    else if (msgBox.clickedButton() == btn180)
        angle = 180;
    else if (msgBox.clickedButton() == btn270)
        angle = 270;

    // تطبيق الفلتر
    Apply_Rotate_Filter(img, angle);

    // تحديث الصورة في الواجهة
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_darkenButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first.");
        return;
    }
    previousImage = img;
    bool ok;
    double percentage = QInputDialog::getDouble(this, "Darken Image",
                                                "Enter darken percentage (0-100):",
                                                20, 0, 100, 1, &ok);
    if (!ok) return; // المستخدم لغى الإدخال

    Apply_Lighten_Darken_Filter(img, Darken, percentage);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_lightenButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first.");
        return;
    }
    previousImage = img;
    bool ok;
    double percentage = QInputDialog::getDouble(this, "Lighten Image",
                                                "Enter lighten percentage (0-100):",
                                                20, 0, 100, 1, &ok);
    if (!ok) return; // المستخدم لغى الإدخال

    Apply_Lighten_Darken_Filter(img, Lighten, percentage);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_cropButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int startX = QInputDialog::getInt(this, "Crop Image", "Enter start X:", 0, 0, img.width, 1, &ok);
    if (!ok) return;

    int startY = QInputDialog::getInt(this, "Crop Image", "Enter start Y:", 0, 0, img.height, 1, &ok);
    if (!ok) return;

    int cropW = QInputDialog::getInt(this, "Crop Image", "Enter crop width:", img.width / 2, 1, img.width - startX, 1, &ok);
    if (!ok) return;

    int cropH = QInputDialog::getInt(this, "Crop Image", "Enter crop height:", img.height / 2, 1, img.height - startY, 1, &ok);
    if (!ok) return;

    Apply_Crop_Filter(img, startX, startY, cropW, cropH);

    // عرض الصورة بعد القص
    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);
}

void Widget::on_frameButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int thickness = QInputDialog::getInt(this, "Frame Thickness",
                                         "Enter frame thickness:",
                                         10, 1, 200, 1, &ok);
    if (!ok) return;

    QStringList styles = {"Solid", "Gradient", "Striped", "Checkered", "Decorated"};
    QString style = QInputDialog::getItem(this, "Frame Style",
                                          "Choose style:", styles, 0, false, &ok);
    if (!ok) return;

    QColor color1 = QColorDialog::getColor(Qt::white, this, "Choose first color");
    if (!color1.isValid()) return;

    QColor color2;
    if (style == "Gradient") {
        color2 = QColorDialog::getColor(Qt::black, this, "Choose second color");
        if (!color2.isValid()) return;
    } else {
        color2 = color1;
    }

    int styleIndex = styles.indexOf(style) + 1;

    Apply_frame_filter(img,
                       thickness,
                       styleIndex,
                       color1.red(), color1.green(), color1.blue(),
                       color2.red(), color2.green(), color2.blue());

    displayImage(img);
    QMessageBox::information(this, "Done", "Frame applied successfully!");
}

void Widget::on_edgeButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int threshold = QInputDialog::getInt(this, "Edge Detection",
                                         "Enter edge detection threshold (10-255):",
                                         50, 1, 255, 1, &ok);
    if (!ok) return;

    Apply_Edge_Detection_Filter(img, threshold);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Edge detection applied successfully!");
}

void Widget::on_resizeButton_clicked()
{
    if (img.width == 0 || img.height == 0) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok1, ok2;
    int newWidth = QInputDialog::getInt(this, "Resize", "Enter new width:", img.width, 1, 5000, 1, &ok1);
    int newHeight = QInputDialog::getInt(this, "Resize", "Enter new height:", img.height, 1, 5000, 1, &ok2);
    if (!ok1 || !ok2) return;

    Apply_Resize_Filter(img, newWidth, newHeight);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Image resized successfully!");
}

void Widget::on_blurButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int strength = QInputDialog::getInt(this, "Blur Filter",
                                        "Enter blur strength (e.g., 1-10):",
                                        2, 1, 20, 1, &ok);
    if (!ok) return;

    Apply_Blur_Filter(img, strength);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Blur filter applied successfully!");
}

void Widget::on_sunlightButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_Sunlight_filter(img);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Sunlight filter applied successfully!");
}

void Widget::on_oilPaintingButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_OilPainting_filter(img);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Oil Painting filter applied successfully!");
}

void Widget::on_tvNoiseButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_TV_Noise_Filter(img);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "TV Noise filter applied successfully!");
}

void Widget::on_purpleButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_Purple_filter(img);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Purple filter applied successfully!");
}

void Widget::on_infraredButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_Infrared_filter(img);

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Infrared filter applied successfully!");
}

void Widget::on_skewButton_clicked()
{
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int degree = QInputDialog::getInt(this, "Skew Filter",
                                      "Enter skew degree (مثلاً 10 أو -10):",
                                      10, -45, 45, 1, &ok);
    if (!ok) return;

    QStringList directions = {"Right", "Left"};
    QString direction = QInputDialog::getItem(this, "Skew Direction",
                                              "Choose direction:",
                                              directions, 0, false, &ok);
    if (!ok) return;

    Apply_Skew_Filter(img, degree, direction.toStdString());

    QImage qimg = convertToQImage(img);
    ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
    ui->imageLabel->setScaledContents(true);

    QMessageBox::information(this, "Done", "Skew filter applied successfully!");
}

void Widget::onFilmFilterClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok;
    int level = QInputDialog::getInt(this, "Film Filter",
                                     "Enter filter level (1-3):",
                                     1, 1, 3, 1, &ok);
    if (!ok) return;

    Apply_Film_Filter(img, level);
    displayImage(img);
}

void Widget::onMotionBlurClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    bool ok1, ok2;
    int strength = QInputDialog::getInt(this, "Motion Blur",
                                        "Enter blur strength (1-50):",
                                        10, 1, 50, 1, &ok1);
    if (!ok1) return;

    double angle = QInputDialog::getDouble(this, "Motion Blur",
                                           "Enter blur angle (degrees):",
                                           0.0, 0.0, 360.0, 1, &ok2);
    if (!ok2) return;

    Apply_Motion_Blur_Filter(img, strength, angle);
    displayImage(img);
}

void Widget::onSepiaClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_Sepia_Filter(img);
    displayImage(img);
}

void Widget::onPencilSketchClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "Please load an image first!");
        return;
    }
    previousImage = img;
    Apply_Pencil_Sketch_Filter(img);
    displayImage(img);
}

void Widget::onUndoClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "No image to undo!");
        return;
    }
    if (previousImage.width == 0 || previousImage.height == 0) {
        QMessageBox::information(this, "Undo", "No previous image available.");
        return;
    }

    img = previousImage;
    displayImage(img);
    QMessageBox::information(this, "Undo", "Reverted to previous image.");
}

void Widget::onSaveClicked() {
    if (!imageLoaded) {
        QMessageBox::warning(this, "Error", "No image to save!");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(
        this, "Save Image", "", "Images (*.png *.jpg *.bmp)");

    if (filename.isEmpty()) return;

    QImage qimg = convertToQImage(img);
    if (!qimg.save(filename)) {
        QMessageBox::warning(this, "Error", "Failed to save image!");
    } else {
        QMessageBox::information(this, "Saved", "Image saved successfully!");
    }
}

void Widget::onExitClicked() {
    QApplication::quit();
}

