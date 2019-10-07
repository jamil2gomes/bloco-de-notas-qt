#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include<QMessageBox>
#include <QTextStream>
#include<QFileDialog>
#include<QFont>
#include<QFontDialog>
#include<QColor>
#include<QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionAbrir_triggered()
{
    QString filtro = "Arquivos de texto (*.txt)";
    QString abrirArquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivos",QDir::homePath(),filtro);

    QFile file(abrirArquivo);
    local_arquivo = abrirArquivo;

    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::information(this, "Atenção!", "Arquivo não pode ser aberto.");
    }

    QTextStream entrada(&file);
    QString texto = entrada.readAll();
    ui->textEdit->setPlainText(texto);
    file.close();

}

void MainWindow::on_actionSalvar_triggered()
{
    QFile file(local_arquivo);

    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::information(this, "Atenção!", "Arquivo não pode ser aberto.");
    }

    QTextStream saida(&file);
    QString texto = ui->textEdit->toPlainText();
    saida<<texto;

    file.flush();
    file.close();
    QMessageBox::information(this, "Sucesso!", "Conteúdo salvo no arquivo com sucesso!");
    ui->textEdit->clear();

}

void MainWindow::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionColar_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionDesfazer_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRefazer_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox::information(this,"Informação", "Editor de texto simples.");
}

void MainWindow::on_actionNovo_triggered()
{
    local_arquivo = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void MainWindow::on_actionSalvar_como_triggered()
{
    QString filtro = "Arquivos de texto (*.txt)";
    QString nomeArquivo = QFileDialog::getSaveFileName(this,"Salvar como",QDir::homePath(),filtro);
    local_arquivo = nomeArquivo;
    QFile file(nomeArquivo);

    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::information(this, "Atenção!", "Arquivo não pode ser aberto.");
    }

    QTextStream saida(&file);
    QString texto = ui->textEdit->toPlainText();
    saida<<texto;

    file.flush();
    file.close();


}

void MainWindow::on_actionFechar_triggered()
{
    close();
}

void MainWindow::on_actionFonte_triggered()
{
    bool fonte_ok;
    QFont fonte = QFontDialog::getFont(&fonte_ok,this);

    if(fonte_ok)
    {
        ui->textEdit->setFont(fonte);
    }else
    {
        return;
    }
}

void MainWindow::on_actionCor_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black,this,"Escolha uma cor");

    if(cor.isValid())
    {
        ui->textEdit->setTextColor(cor);
    }else
    {
        return;
    }
}

void MainWindow::on_actionCor_de_Fundo_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black,this,"Escolha uma cor");

    if(cor.isValid())
    {
        ui->textEdit->setTextBackgroundColor(cor);
    }else
    {
        return;
    }
}
