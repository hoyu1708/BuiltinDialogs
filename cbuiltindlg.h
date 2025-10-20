#ifndef CBUILTINDLG_H
#define CBUILTINDLG_H

#include <QDialog>
#include<QPushButton>
#include<QTextEdit>


class cBuiltindlg : public QDialog
{
    Q_OBJECT

public:
    cBuiltindlg(QWidget *parent = nullptr);
    ~cBuiltindlg();

private:
    QTextEdit   *displayTextEdit;
    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;

};
#endif // CBUILTINDLG_H
