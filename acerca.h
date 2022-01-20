#ifndef ACERCA_H
#define ACERCA_H

#include <QDialog>

namespace Ui {
class Acerca;
}


//Esta ventana es para obtener la vizualicacion del boton acerca de, el cual nos permite conocer mas de la app
class Acerca : public QDialog
{
    Q_OBJECT

public:
    explicit Acerca(QWidget *parent = nullptr);
    ~Acerca();

    void setVersion(const QString &newVersion);

private:
    Ui::Acerca *ui;

    QString m_version;
};

#endif // ACERCA_H
