#ifndef GUIBI_H
#define GUIBI_H

#include <QApplication>
#include <QSplashScreen>
#include <QLockFile>
#include <QPixmap>
#include <QStringList>
#include <QMessageBox>

#include "gmessagebox.h"
#include "gbarretitre.h"
#include "guibi_global.h"


/// -*-*- Déclarations -*-*-
bool demmarerApp(QWidget & fenetrePrincipale, QStringList const& listeFichiers, QString const& cheminImageSplash);
bool verifierFichiers(QStringList const& listeFichier);
QStringList getFilesList();


/// -*-*- Code source -*-*-
bool demmarerApp(QWidget & fenetrePrincipale, QStringList const& listeFichiers, QString const& cheminImageSplash)
{
    // Vérification des fichiers requis
    QStringList liste(getFilesList());
            liste.append(listeFichiers);
            liste.append(cheminImageSplash);

    if (!verifierFichiers(liste))
        return false;


    // On configure le splash screen
    QPixmap pixSplash(cheminImageSplash);
    QSplashScreen splash(pixSplash);
    splash.showMessage(QObject::tr("Verrouillage des fichier..."), Qt::AlignBottom & Qt::AlignHCenter, Qt::white);
    splash.show();


    // Vérification d'une potentielle deuxième instance
    QLockFile fichier(qApp->applicationDisplayName() + "_" + qApp->applicationName() + "-V." + qApp->applicationVersion() + ".lockFile");
    fichier.setStaleLockTime(0);

    if (!fichier.tryLock(1))
        return false;


    // On démarre l'application au complet
    splash.showMessage(QObject::tr("Démarrage de l'application..."), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    fenetrePrincipale.show();
    splash.close();

    return true;
}



bool verifierFichiers(QStringList const& listeFichiers)
{
    for (int i = 0; i < listeFichiers.size(); i++)
    {
        if (!QFile::exists(listeFichiers.at(i)))
        {
            GMessageBox messageBox(GMessageBox::Critique, QObject::tr("Erreur critique - ") + qApp->applicationDisplayName(), QObject::tr("Impossible de charger le fichier \"") + qApp->applicationDirPath() + "/" + listeFichiers.at(i) + QObject::tr("\". Réinstaller le programme pourrait aider."), Q_NULLPTR, GMessageBox::Ok);
                messageBox.setWindowIcon(QIcon("images/003-critical.png"));

            messageBox.exec();
            return false;
        }
    }

    return true;
}

QStringList getFilesList()
{
    QStringList listeFichiers;
        listeFichiers.append(GMessageBox::getFilesList());
        listeFichiers.append(GBarreTitre::getFilesList());

    return listeFichiers;
}

#endif // GUIBI_H
