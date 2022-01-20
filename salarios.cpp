#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador=new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}

void Salarios::limpiar()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
{
    if(ui->inNombre->text()==""){
        ui->statusbar->showMessage("Ingrese un nombre valido porfavor!",3500);

        QMessageBox::warning(this,"Nombre","Este nombre es invalido");
        return;
    }
    else if((ui->inMatutina->isChecked()==false&&ui->inNocturna->isChecked()==false&&ui->inVespertina->isChecked()==false)){
        ui->statusbar->showMessage("Se necesita conocer la jornada del trabajador",3500);
        QMessageBox::warning(this,"Jornada","Es necesario elegir la jornada del trabajador");
        return;
    }
    else if(ui->inHoras->value()==0){
        ui->statusbar->showMessage("El numero de horas esta vacio, no puede ser cero",3500);
        QMessageBox::warning(this,"Horas","El numero de horas no puede ser cero");
        return;
    }


    QString nombre=ui->inNombre->text();
    int horas=ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada=TipoJornada::Matutina;
    }
    else if(ui->inNocturna->isChecked()){
        jornada=TipoJornada::Nocturna;
    }
    if(ui->inVespertina->isChecked()){
        jornada=TipoJornada::Vespertina;
    }
    m_controlador->agregarObrero(nombre,horas,jornada);

    if(m_controlador->calcularSalario()){
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
        limpiar();
    }

}


void Salarios::on_cmdCalcular_clicked()
{
    calcular();
    ui->outTotalBruto->setText(QString::number(m_controlador->m_totalBruto,'f',2));

    ui->outTotalIESS->setText(QString::number(m_controlador->m_totalIESS));


    ui->outTotalNeto->setText(QString::number(m_controlador->m_totalNeto,'f',2));

}


void Salarios::on_actionNuevo_triggered()
{
    ui->inHoras->setValue(8);
    ui->inNombre->clear();
    ui->outResultado->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
    ui->outTotalBruto->setText("0");
    ui->outTotalIESS->setText("0");
    ui->outTotalNeto->setText("0");
    m_controlador->m_totalBruto=0;
    m_controlador->m_totalIESS=0;
    m_controlador->m_totalNeto=0;
}


void Salarios::on_actioncalcular_triggered()
{
    calcular();
}

void Salarios::guardar()
{

    QString nombreArchivo = QFileDialog::getSaveFileName(this,"Guardar datos",QDir::home().absolutePath(),"Archivo de salarios .slr (*.slr)");


    QFile archivo(nombreArchivo);

    if(archivo.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream salida(&archivo);
        salida<<ui->outResultado->toPlainText();
        salida.operator<<("\n/////////////\n");
        salida.operator<<("Total:\n");
        salida.operator<<("Salario bruto: "+QString::number(m_controlador->m_totalBruto)+"\n");
        salida.operator<<("Descuento total: "+QString::number(m_controlador->m_totalIESS)+"\n");
        salida.operator<<("Salario neto: "+QString::number(m_controlador->m_totalNeto)+"\n");
        salida.operator<<("//////////");
        ui->statusbar->showMessage("Datos almacenados en "+nombreArchivo,3500);
    }
    else{
        QMessageBox::warning(this,"Error!","Los datos no pudieron ser guardados");
    }
    //cerrar el archivo
    archivo.close();
}


void Salarios::on_actionGuardar_triggered()
{
    guardar();
}

void Salarios::abrir()
{

    QString nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir Archivos",QDir::home().absolutePath(),"Archivo de salarios .slr (*.slr)");
    //crear un objeto QFile

    QFile archivo(nombreArchivo);
    //abrir para lectura
    if(archivo.open(QFile::ReadOnly)){
        QTextStream entrada(&archivo);
        //leer todo el contenido
        ui->outResultado->clear();
        QString dato="",linea;

        while(entrada.atEnd()==false&&linea!="/////////////"){
            linea=entrada.readLine();
            if(linea=="/////////////"){}else{
                dato+=linea+"\n";
            }
        }

        ui->outResultado->setPlainText(dato);
        linea=entrada.readLine();
        linea=entrada.readLine();
        linea.remove(0,15);
        ui->outTotalBruto->setText(linea);
        m_controlador->m_totalBruto=linea.toDouble();
        linea=entrada.readLine();
        linea.remove(0,16);
        ui->outTotalIESS->setText(linea);
        m_controlador->m_totalIESS=linea.toDouble();
        linea=entrada.readLine();
        linea.remove(0,14);
        ui->outTotalNeto->setText(linea);
        m_controlador->m_totalNeto=linea.toDouble();
        //cargar a la pantalla

        ui->statusbar->showMessage("El archivo "+nombreArchivo+" se leyo con exito",3500);
    }
    else{
        QMessageBox::warning(this,"Advertencia!","Los datos no pudieron ser leidos");
        ui->statusbar->showMessage("El archivo "+nombreArchivo+" no pudo ser leido",3500);
    }
    //cerrar el archivo
    archivo.close();

}

void Salarios::on_actionAbrir_triggered()
{

    abrir();
}


void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    Acerca *dialogo=new Acerca (this);
    dialogo->setVersion(VERSION);
    dialogo->exec();

}


void Salarios::on_actionSalir_triggered()
{
    close();
}

