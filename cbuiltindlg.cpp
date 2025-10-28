#include "cbuiltindlg.h"
#include "qapplication.h"
#include <QGridLayout>
#include<QDebug>
#include<QPalette>
#include<QWidget>
#include<QColorDialog>
#include<QfileDialog>
#include<QProgressDialog>
#include<QErrorMessage>
#include<QFontDialog>
#include<QInputDialog>
#include<QtPrintSupport/qprinter.h>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrintPreviewDialog>
#include<QPageSetupDialog>


cBuiltindlg::cBuiltindlg(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridlayout = new QGridLayout;
    displayTextEdit  = new QTextEdit(QStringLiteral("Qt的標準通用對話盒"));
    colorPushBtn = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton(QStringLiteral("列印對話盒"));
    setcolorPushBtn = new QPushButton(QStringLiteral("設定文字顏色"));

    gridlayout->addWidget(colorPushBtn,0,0,1,1);
    gridlayout->addWidget(errorPushBtn,0,1,1,1);
    gridlayout->addWidget(filePushBtn,0,2,1,1);
    gridlayout->addWidget(fontPushBtn,1,0,1,1);
    gridlayout->addWidget(inputPushBtn,1,1,1,1);
    gridlayout->addWidget(pagePushBtn,1,2,1,1);
    gridlayout->addWidget(progressPushBtn,2,0,1,1);
    gridlayout->addWidget(printPushBtn,2,1,1,1);
    gridlayout->addWidget(displayTextEdit,3,0,3,3);
    gridlayout->addWidget(setcolorPushBtn,2,2,1,1);


    setLayout(gridlayout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(400,300);
    connect(colorPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(filePushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(errorPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(fontPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(inputPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(pagePushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(progressPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(printPushBtn,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(displayTextEdit,SIGNAL(clicked()),this,SLOT(doPushBtn()));
    connect(setcolorPushBtn,SIGNAL(clicked()),this,SLOT(textPushBtn()));
}


void cBuiltindlg:: textPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == setcolorPushBtn)
    {
        QPalette palette=displayTextEdit->palette();
        const QColor& color=
            QColorDialog::getColor(palette.color(QPalette::Text),
                                   this, QStringLiteral("設定背景顏色"));
        if(color.isValid())
        {
            palette.setColor(QPalette:: Text, color);
            displayTextEdit->setPalette (palette);
        }
    }
}




void cBuiltindlg :: doPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn == colorPushBtn)
    {

        QPalette palette = displayTextEdit->palette();
        const QColor& color =
            QColorDialog::getColor(palette.color(QPalette::Base),this,tr("設定背景顏色"));

        if(color.isValid())
        {
            palette.setColor(QPalette::Base,color);
            displayTextEdit->setPalette(palette);
        }
    }


    if (btn == filePushBtn)
    {
        QString fileName = QFileDialog::getOpenFileName(this,tr("開啟檔案"),".",tr("任何檔案(*.*)"";;文字檔(*.txt)"";;XML檔(*.xml)"));
        displayTextEdit->setText(fileName);
    }


    if (btn == progressPushBtn)
    {
        QProgressDialog progress(tr("正在複製檔案..."),tr("取消"),0,10000,this);
        progress.setWindowTitle(QStringLiteral("進度對話方塊"));
        progress.show();
        for (int i = 0; i < 10000; i++)
        {
            progress.setValue(i);
            qApp->processEvents();
            if(progress.wasCanceled())
                break;
            qDebug()<<i;
        }
        progress.setValue(10000);
    }


    if (btn == errorPushBtn)
    {
        QErrorMessage box (this);
        box.setWindowTitle (QStringLiteral("錯誤訊息盒"));
        box.showMessage (QStringLiteral("錯誤訊息盒實例xx:"));
        box.showMessage (QStringLiteral("錯誤訊息盒實例yy:"));
        box.showMessage (QStringLiteral("錯誤訊息盒實例zz:"));
        box.exec();
    }


    if (btn == fontPushBtn)
    {
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,displayTextEdit->font(),this,QStringLiteral("字體對話盒"));
        if (ok) displayTextEdit->setFont(font);
    }


    if (btn == inputPushBtn)
    {
            bool ok;
                      QString text = QInputDialog::getText(this,QStringLiteral("輸入對話盒"),QStringLiteral("輸入文字"),QLineEdit:: Normal,QDir::home().dirName(), &ok );
            if (ok && !text.isEmpty()) displayTextEdit->setText(text);
    }


    if (btn == pagePushBtn)
    {
        QPrinter printer (QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer,this);
        dlg->setWindowTitle (QStringLiteral("頁面設定話方塊"));
        if (dlg->exec() == QDialog::Accepted)
        {

        }
    }


    if (btn == printPushBtn)
    {
        QPrinter printer (QPrinter:: HighResolution);
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog:: Accepted)
            return;
    }
}





cBuiltindlg::~cBuiltindlg()
{

}



