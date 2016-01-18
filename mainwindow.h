#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define MAX_SERIAL_LENGTH   (25)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onReleasePushButtonClicked();
    void onClosePushButtonClicked();
    void onSerialChanged();
    void onDecorativeProgressBarValueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
