#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include "obrero.h"
#include <QDebug>

#define MATUTINO 2.65
#define VESPERTINO 2.73
#define NOCTURNO 2.87
#define HORA_EXTRA 50
#define IESS 9.5

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);

    bool agregarObrero(QString nombre, int horas, TipoJornada jornada);
    bool calcularSalario();

    Obrero *obrero() const;

    void setObrero(Obrero *newObrero);

    double m_totalBruto;
    double m_totalIESS;
    double m_totalNeto;

signals:

private:
   Obrero *m_obrero;


};

#endif // CONTROLADOR_H
