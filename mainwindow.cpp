#include <QtGui>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Changed(false)
{
    ui->setupUi(this);

    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::textChanged()
{
    m_Changed = true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_Changed) {
        QMessageBox msgBox;

        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        switch (msgBox.exec()) {
            case QMessageBox::Save:
                on_ActionSave_triggered();
                break;

            case QMessageBox::Cancel:
                event->ignore();
                return;

            default:
                break;
        }
    }

    event->accept();
}

/* menu file */

void MainWindow::on_ActionNew_triggered()
{
    if(m_Changed) {
        QMessageBox msgBox;

        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        switch (msgBox.exec()) {
            case QMessageBox::Save:
                on_ActionSave_triggered();
                break;

            case QMessageBox::Cancel:
                return;

            default:
                break;
        }
    }

    ui->textEdit->clear();
    m_Filename.clear();
    m_Changed = false;

    UpdateTitle();
}

void MainWindow::on_ActionOpen_triggered()
{
    on_ActionNew_triggered();

    QString filename = QFileDialog::getOpenFileName(this);

    if (!filename.isEmpty()) {
        QFile f(filename);

        if (f.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&f);

            ui->textEdit->setPlainText(in.readAll());

            m_Filename = filename;

            UpdateTitle();
        }
    }
}

void MainWindow::on_ActionSave_triggered()
{
    if (m_Filename.isEmpty()) {
        on_ActionSave_as_triggered();

        return;
    }

    QFile f(m_Filename);

    if (f.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&f);

        out << ui->textEdit->toPlainText();

        m_Changed = false;
    }
}

void MainWindow::on_ActionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this);

    if (!filename.isEmpty()) {
        QFile f(filename);

        if (f.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&f);

            out << ui->textEdit->toPlainText();

            m_Filename = filename;
            m_Changed = false;

            UpdateTitle();
        }
    }
}

/* menu edit*/

void MainWindow::on_ActionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_ActionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_ActionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_ActionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_ActionRedo_triggered()
{
    ui->textEdit->redo();
}

/* menu help */

void MainWindow::on_ActionAbout_triggered()
{
    QMessageBox msgBox(this);

    msgBox.setText(
        "(c) QuickPad Oleh Kravchenko <oleg@kaa.org.ua>\n"
        "Build date: " __DATE__
    );

    msgBox.exec();
}
