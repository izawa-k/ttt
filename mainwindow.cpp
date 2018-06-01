#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	alarm(), first(false)
{
	ui->setupUi(this);
	timer.setInterval(500);
	timer.setSingleShot(false);
	connect(& timer, SIGNAL(timeout()), SLOT(timeOut()));
	timer.start();
	ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	if (alarm == ui->dateTimeEdit->dateTime()) {
		alarm.fromTime_t(0);
		ui->dateTimeEdit->setEnabled(true);
		ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
		return;
	}
	QDateTime edit = ui->dateTimeEdit->dateTime();
	ui->dateTimeEdit->setTime(QTime(edit.time().hour(), edit.time().minute(), 0));
	edit = ui->dateTimeEdit->dateTime();
	alarm = edit;
	ui->dateTimeEdit->setEnabled(false);
	first = true;
}

void MainWindow::timeOut()
{
	QTime now = QTime::currentTime();
	ui->lcdNumber->display(now.hour());
	ui->lcdNumber_2->display(now.minute());
	ui->dial->setValue((now.second() + 30) % 60);
	this->setWindowTitle(now.toString());
	ui->label->setText(now.second() % 2 ? ":" : ";");

	if (alarm <= QDateTime::currentDateTime()) {
		if (first) {
			first = false;
			QMessageBox::information(this, "Alert", "It' alarm time.");
		}
		ui->dateTimeEdit->setEnabled(true);
	}
}
