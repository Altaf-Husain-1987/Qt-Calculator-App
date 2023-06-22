
#include "calculator.h"
#include "ui_calculator.h"
#include<QRegularExpression>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
double MemoireVal;

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(released()),this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign,SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));

    connect(ui->Clear,SIGNAL(released()),this,
            SLOT(Clear()));

    connect(ui->MemAdd,SIGNAL(released()),this,
            SLOT(MemoryAdd()));

    connect(ui->MemGet,SIGNAL(released()),this,
            SLOT(MemoryCall()));

    connect(ui->MemClear,SIGNAL(released()),this,
            SLOT(MemoryClear()));
}

calculator::~calculator()
{
    delete ui;
}

void calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->display->text();
    if((displayVal.toDouble()==0)||(displayVal.toDouble()==0.0)){
        ui->display->setText(butval);
    }
    else{
        QString newVal = displayVal + butval;
        double dblNewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblNewVal,'g',16));
    }
}

void calculator::MathButtonPressed(){
    divTrigger=false;
    multTrigger=false;
    addTrigger=false;
    subTrigger=false;
    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0)
        divTrigger=true;
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0)
        multTrigger=true;
    else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0)
        addTrigger=true;
    else
        subTrigger=true;
    ui->display->setText("");
}

void calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger)
            solution = calcVal + dblDisplayVal;
        else if(subTrigger)
            solution = calcVal - dblDisplayVal;
        else if(multTrigger)
            solution = calcVal * dblDisplayVal;
        else
            solution = calcVal / dblDisplayVal;
    }
    ui->display->setText(QString::number(solution));
}

void calculator::ChangeNumberSign(){
    QString displayVal = ui->display->text();

    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match=reg.match(displayVal);
    if(match.hasMatch()){
        double dblDisplay=displayVal.toDouble();
        double dblDisplayValSign=-1*dblDisplay;
        ui->display->setText(QString::number(dblDisplayValSign));
    }
}


void calculator::MemoryAdd()
{
    QString displayVal = ui->display->text();
    MemoireVal = displayVal.toDouble();
    ui->display->setText("");

}

void calculator::MemoryCall()
{
    ui->display->setText(QString::number(MemoireVal));

}

void calculator::MemoryClear()
{
    MemoireVal = 0.0;
}

void calculator::Clear()
{
    ui->display->setText("");
}
