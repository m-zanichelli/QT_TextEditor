#include "mainwindow.h" // where we define our application functionalities
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) //class definition
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); //setup user interface
    this-> setCentralWidget(ui->textEdit); //
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as") ;
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }
    currentFile=fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out <<text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer di Marco");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec()==QDialog::Rejected){
        QMessageBox::warning(this,"Warning","Cannot Access Printer");
        return;
    }
    ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionFind_in_file_triggered()
{
    QString find_text = QInputDialog::getText(this,tr("Find in file: "), tr("Find: "));
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(cursor);
    cursor.movePosition(QTextCursor::StartOfWord);
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    QTextDocument *document = ui->textEdit->document();
    QTextCursor newCursor(document);
    int count = 0;
    QString txt = ui->textEdit->toPlainText();
    while (!newCursor.isNull() && !newCursor.atEnd() && count!=1) {
        newCursor = document->find(find_text, newCursor);

        if (!newCursor.isNull()) {
            //++count;
            newCursor.movePosition(QTextCursor::WordRight,
                                   QTextCursor::KeepAnchor);
            ui->textEdit->setTextCursor(newCursor);

           // newCursor.mergeCharFormat(colorFormat);
        }
    }
}

void MainWindow::on_actionFind_and_substitute_triggered()
{
    QString find_text = QInputDialog::getText(this,tr("Find in file: "), tr("Find: "));
    QString repl = QInputDialog::getText(this,tr("Replace: "), tr("Replace: "));
    QString txt = ui->textEdit->toPlainText();
    txt.replace(find_text, repl);
    ui->textEdit->setText(txt);

}

