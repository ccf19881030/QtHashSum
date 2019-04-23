#include "duplicatedialog.h"
#include "ui_duplicatedialog.h"

#include <QDebug>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

DuplicateDialog::DuplicateDialog(const QList<QString> &pathlist, QString dir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuplicateDialog)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout(this);
    for(int i = 0; i < pathlist.size(); ++i)
    {
       QLabel *label = new QLabel(pathlist[i], this);
       layout->addWidget(label, i, 0);
       QPushButton *button = new QPushButton("Remove", this);
       button->setStatusTip(dir + pathlist[i]);
       //qDebug() << "DuplicateDialog" << i << dir + pathlist[i];
       connect(button, SIGNAL(clicked()), this, SLOT(remove_clicked()));
       layout->addWidget(button, i, 1);
    }
    setLayout(layout);
}

DuplicateDialog::~DuplicateDialog()
{
    delete ui;
}

void DuplicateDialog::remove_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button != nullptr)
    {
        QFile file(button->statusTip());
        if(file.exists())
        {
            bool ok = file.remove();
            if(!ok)
            {
                QMessageBox::warning(this, "", "Remove failed!");
            }
        }
        else
        {
            QMessageBox::warning(this, "", "File not found!");
        }
    }
    this->accept();
}