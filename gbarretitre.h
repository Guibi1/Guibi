#ifndef GBARRETITRE_H
#define GBARRETITRE_H

#include <QApplication>
#include <QFrame>
#include <QPoint>
#include <QMouseEvent>
#include <QLayout>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QStringList>
#include <QImage>
#include <QRgb>

#include "guibi_global.h"


class GBarreTitre : public QFrame
{
    Q_OBJECT

public:
    enum TypeBoutonTitre{ Tout, Aucun, Fermer, Reduire, Minimiser };

private:
    enum SorteBouton{ Close, Reduce, Minimize, Maximize };


public:
    explicit GBarreTitre(QRgb couleur = QRgb(), QWidget *parent = Q_NULLPTR, TypeBoutonTitre type = Tout);
    void setTypeBoutonTitre(TypeBoutonTitre type);


    static QStringList getFilesList();

private:
    QPixmap getColoredPixmap(SorteBouton bouton);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void reduceButtonClicked();
    void sizeButtonClicked();
    void closeButtonClicked();
    void iconClicked();

    void buttonPressed();

    void titleChanged();
    void iconChanged();
    void windowViewChanged();

signals:
    void iconPressed();
    void willSoonExit();

private:
    TypeBoutonTitre typeBouton;
    QRgb couleurBoutons;

    // Déplacement de la fenêtre
    QPoint pointDifference;
    bool correct;

    // GUI
    QHBoxLayout *layoutHPrincipal;
    QHBoxLayout *layoutHBoutons;

    QToolButton *reduceButton;
    QToolButton *sizeButton;
    QToolButton *closeButton;
    QToolButton *icon;

    QLabel *labelTitre;
};

#endif // GBARRETITRE_H
