#ifndef GMESSAGEBOX_H
#define GMESSAGEBOX_H

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QPixmap>
#include <QMap>
#include <QStringList>

#include "guibi_global.h"
#include "gbarretitre.h"


class GMessageBox : public QDialog
{
    Q_OBJECT

public:
    enum Icone { AucuneIcone, Information, Question, Avertissement, Critique };
    enum RoleBouton { Ok, Ouvrir, Enregistrer, NePasEnregistrer, Annuler, Fermer, Appliquer, Reinitiliser, Oui, OuiATous, Non, NonATous, Reessayer, Ignorer, AucunRole };


public:
    GMessageBox(Icone icone, QString titre, QString const& texte, QWidget *parent = Q_NULLPTR, RoleBouton bouton1 = Ok, RoleBouton bouton2 = AucunRole, RoleBouton bouton3 = AucunRole, RoleBouton bouton4 = AucunRole, RoleBouton bouton5 = AucunRole);

    bool addButton(QPushButton *bouton, RoleBouton const role);
    bool removeButton(QPushButton *bouton);

    QString getText();
    static QStringList getFilesList();

    static int question(QString titre, QString const& texte, QWidget *parent = Q_NULLPTR, RoleBouton bouton1 = Ok, RoleBouton bouton2 = AucunRole, RoleBouton bouton3 = AucunRole, RoleBouton bouton4 = AucunRole, RoleBouton bouton5 = AucunRole);
    static int information(QString titre, QString const& texte, QWidget *parent = Q_NULLPTR, RoleBouton bouton1 = Ok, RoleBouton bouton2 = AucunRole, RoleBouton bouton3 = AucunRole, RoleBouton bouton4 = AucunRole, RoleBouton bouton5 = AucunRole);
    static int warning(QString titre, QString const& texte, QWidget *parent = Q_NULLPTR, RoleBouton bouton1 = Ok, RoleBouton bouton2 = AucunRole, RoleBouton bouton3 = AucunRole, RoleBouton bouton4 = AucunRole, RoleBouton bouton5 = AucunRole);
    static int critical(QString titre, QString const& texte, QWidget *parent = Q_NULLPTR, RoleBouton bouton1 = Ok, RoleBouton bouton2 = AucunRole, RoleBouton bouton3 = AucunRole, RoleBouton bouton4 = AucunRole, RoleBouton bouton5 = AucunRole);

public slots:
    virtual int exec();

protected:
    QString getTextFromEnum(RoleBouton typeBouton);

    void setText(QString const& texte);
    void setPixmapIcon(Icone icone);

protected:
    QString text;
    QPushButton *choix;

    // GUI
    QMap<QPushButton*, RoleBouton> *listeBoutons;

    QHBoxLayout *layoutHBoutons;
    QHBoxLayout *layoutHTexte;
    QVBoxLayout *layoutVFenetre;

    QLabel *labelTexte;
    QLabel *labelIcone;

    GBarreTitre *barreTitre;


private slots:
    void boutonCliquer();
};

#endif // GMESSAGEBOX_H
