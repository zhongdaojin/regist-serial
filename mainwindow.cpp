#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbconnect.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QString>
#include <QHash>
#include <QTimer>
#include <QEventLoop>

#define STORES_ON  "1"
#define STORES_OFF "2"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 非表示項目の設定 */
    ui->message1Label->setVisible( false );
    ui->message2Label->setVisible( false );
    ui->downloadLabel->setVisible( false );
    ui->decorativeProgressBar->setVisible( false );
    /* シリアル入力時にIME無効 */
    ui->serialLineEdit->setAttribute( Qt::WA_InputMethodEnabled, false );
    ui->releasePushButton->setEnabled( false );

    /* スロットの接続 */
    connect( ui->releasePushButton, SIGNAL( clicked() ), this, SLOT( onReleasePushButtonClicked() ) );
    connect( ui->closePushButton, SIGNAL( clicked() ), this, SLOT( onClosePushButtonClicked() ) );
    connect( ui->serialLineEdit, SIGNAL( textChanged(QString) ) , this, SLOT( onSerialChanged() )  );
    connect( ui->decorativeProgressBar, SIGNAL( valueChanged(int)) , this, SLOT( onDecorativeProgressBarValueChanged(int) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReleasePushButtonClicked()
{
    ui->releasePushButton->setEnabled( false );
    QString serial = ui->serialLineEdit->text().replace("-", "");
    QMessageBox msgBox(ui->centralWidget);
    msgBox.setWindowTitle( tr("シリアル番号の入力"));

    DbConnect db;
    QHash<QString, QString> params;
    params.insert(":SERIAL", serial);
    params.insert(":ON", STORES_ON );
    params.insert(":OFF", STORES_OFF );
    {
        QString sql;
        sql =  " UPDATE stores ";
        sql += "   SET ";
        sql += "   on_off = :ON";
        sql += " WHERE serial = :SERIAL ";
        sql += "   AND on_off = :OFF ";
        QSqlQuery *query = db.queryPrepareExecute(sql, params);
    }
    {
         QString sql;
         sql =  " SELECT ";
         sql += "        A.name ";
         sql += "       ,A.on_off ";
         sql += "   FROM stores A ";
         sql += "   WHERE A.serial = :SERIAL ";
         QSqlQuery *query = db.queryPrepareExecute(sql, params);
         while ( query->next()) {
            QString name = query->value(0).toString();
            QString on_off = query->value(1).toString();
            qDebug() << name << on_off;

            if ( on_off == STORES_ON ) {
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setText( "制限は解除されました。" );
                ui->decorativeProgressBar->setMaximum( 100 );
            }
         }
         if ( 0 == query->size() ) {
             msgBox.setStandardButtons(QMessageBox::Yes);
             msgBox.setText( "制限が解除できませんでした。\nシリアル番号をご確認ください。" );
             ui->decorativeProgressBar->setMaximum( 50 );
         }
    }
    ui->decorativeProgressBar->setVisible( true );
    /* 飾りプログレスバー */
    QEventLoop loop;
    for (int i = 0; i <= 100; i++ ) {

        QTimer::singleShot( 50, &loop, SLOT( quit() ) );
        loop.exec();
        ui->decorativeProgressBar->setValue(i);
    }
    msgBox.exec();
}

void MainWindow::onSerialChanged()
{
    QString serial = ui->serialLineEdit->text().replace("-", "");
    if ( MAX_SERIAL_LENGTH == serial.size() ) {
        ui->serialCheckBox->setChecked( true );     //　checkマークの表示
        ui->releasePushButton->setEnabled( true );  // 認証ボタンの有効化
    } else {
        ui->serialCheckBox->setChecked( false );    // crossマークの表示
        ui->releasePushButton->setEnabled( false ); // 認証ボタンの無効化
    }
}

void MainWindow::onClosePushButtonClicked()
{
    closeEvent(new QCloseEvent);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    close();
}

void MainWindow::onDecorativeProgressBarValueChanged(int value)
{
    if ( 100 <= value ) {
        ui->message1Label->setVisible( true );
        ui->message2Label->setVisible( true );
        ui->downloadLabel->setVisible( true );
    } else {
        ui->message1Label->setVisible( false );
        ui->message2Label->setVisible( false );
        ui->downloadLabel->setVisible( false );
    }
}
