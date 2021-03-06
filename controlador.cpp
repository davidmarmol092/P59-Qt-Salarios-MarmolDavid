#include "controlador.h"

Controlador::Controlador(QObject *parent) : QObject(parent)
{
    this->m_obrero=nullptr;
    this->m_totalBruto=0;
    this->m_totalIESS=0;
    this->m_totalNeto=0;
}

bool Controlador::agregarObrero(QString nombre, int horas, TipoJornada jornada)
{
    this->m_obrero=new Obrero(nombre,horas,jornada);
    return true;
}


bool Controlador::calcularSalario()
{
      if (m_obrero == nullptr)
          return false;

      double valorHora = 0;
      switch(m_obrero->jornada()){
      case TipoJornada::Vespertina:
          valorHora = VESPERTINO;
          break;
      case TipoJornada::Matutina:
          valorHora = MATUTINO;
          break;
      case TipoJornada::Nocturna:
          valorHora = NOCTURNO;
          break;
      default:
          return false;
      }
      int horas = m_obrero->horas();
      int horasExtra = 0;
      if (m_obrero->horas() > 40){
          horasExtra = m_obrero->horas() - 40;
          horas = 40;
      }

      double salarioBruto = horas * valorHora + horasExtra * (HORA_EXTRA * valorHora / 100);


      double descuento = salarioBruto * IESS / 100;


      double salarioNeto = salarioBruto - descuento;


      m_obrero->setSalarioBruto(salarioBruto);
      m_obrero->setDescuento(descuento);
      m_obrero->setSalarioNeto(salarioNeto);


      m_totalBruto+=salarioBruto;
      m_totalIESS+=descuento;
      m_totalNeto+=salarioNeto;

      return true;
}

Obrero *Controlador::obrero() const
{
    return m_obrero;
}

void Controlador::setObrero(Obrero *newObrero)
{
    m_obrero = newObrero;
}
