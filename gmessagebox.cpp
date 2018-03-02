#include "gmessagebox.h"

GMessageBox::GMessageBox(Icone icone, QString titre, QString const& texte, QWidget *parent,
                         RoleBouton bouton1, RoleBouton bouton2, RoleBouton bouton3, RoleBouton bouton4, RoleBouton bouton5)
    : text(""),
    choix(0),
    listeBoutons(new QMap<QPushButton*, RoleBouton>),
    layoutHBoutons(0),
    layoutHTexte(0),
    layoutVFenetre(0),
    labelTexte(0),
    labelIcone(0),
    barreTitre(0)
{
    /// Réglages des propriétés
    setWindowTitle(titre);
    setText(texte);
    setParent(parent);
    setWindowIcon(parent->windowIcon());

    /// Construction du GUI
    barreTitre = new GBarreTitre(QColor(47, 191, 64).rgb(), this);
        barreTitre->setTypeBoutonTitre(GBarreTitre::Fermer);

    // Construction des labels
    labelTexte = new QLabel(getText());

    labelIcone = new QLabel;
        setPixmapIcon(icone);

    // Construction des layouts
    layoutHTexte = new QHBoxLayout;
        layoutHTexte->addWidget(labelIcone, 0, Qt::AlignCenter);
        layoutHTexte->addWidget(labelTexte, 1, Qt::AlignTop);

    layoutHBoutons = new QHBoxLayout;

    layoutVFenetre = new QVBoxLayout(this);
        layoutVFenetre->addWidget(barreTitre, 0);
        layoutVFenetre->addLayout(layoutHTexte, 1);
        layoutVFenetre->addLayout(layoutHBoutons, 2);
        layoutVFenetre->setMargin(2);

    // Construction des boutons
    QList<RoleBouton> listeRoleBoutonsAjouter;
        listeRoleBoutonsAjouter.append(bouton1);
        listeRoleBoutonsAjouter.append(bouton2);
        listeRoleBoutonsAjouter.append(bouton3);
        listeRoleBoutonsAjouter.append(bouton4);
        listeRoleBoutonsAjouter.append(bouton5);

    for (int i = 0; i < listeRoleBoutonsAjouter.size(); i++)
        if (listeRoleBoutonsAjouter.at(i) != AucunRole)
            addButton(new QPushButton(getTextFromEnum(listeRoleBoutonsAjouter.at(i))), listeRoleBoutonsAjouter.at(i));
}

bool GMessageBox::addButton(QPushButton *bouton, RoleBouton const role)
{
    if (listeBoutons->contains(bouton))
    {
        listeBoutons->insert(bouton, role);
        layoutHBoutons->addWidget(bouton);
        connect(bouton, SIGNAL(clicked(bool)), this, SLOT(boutonCliquer()));
        return true;
    }

    return false;
}

bool GMessageBox::removeButton(QPushButton *bouton)
{
    if (listeBoutons->remove(bouton) != 0)
    {
        layoutHBoutons->removeWidget(bouton);
        return true;
    }

    return false;
}

QString GMessageBox::getTextFromEnum(RoleBouton typeBouton)
{
    switch (typeBouton)
    {
        case Ok:
            return tr("Ok");
            break;

        case Ouvrir:
            return tr("Ouvrir");
            break;

        case Enregistrer:
            return tr("Enregistrer");
            break;

        case NePasEnregistrer:
            return tr("Ne pas enregistrer");
            break;

        case Annuler:
            return tr("Annuler");
            break;

        case Fermer:
            return tr("Fermer");
            break;

        case Appliquer:
            return tr("Appliquer");
            break;

        case Reinitiliser:
            return tr("Réinitialiser");
            break;

        case Oui:
            return tr("Oui");
            break;

        case OuiATous:
            return tr("Oui à tous");
            break;

        case Non:
            return tr("Non");
            break;

        case NonATous:
            return tr("Non à tous");
            break;

        case Reessayer:
            return tr("Réessayer");
            break;

        case Ignorer:
            return tr("Ignorer");
            break;

        default: //(AucunRole)
            return tr("**AUCUN*BOUTON**");
            break;
    }
}


/// **-------**SETs/GETs**-------**
// Ascenseur pour le texte de la boite de dialogue
QString GMessageBox::getText()
{
    return text;
}

void GMessageBox::setText(QString const& texte)
{
    if (texte != NULL)
        if (!texte.isEmpty())
            text = texte;
}

void GMessageBox::setPixmapIcon(Icone icone)
{
    switch (icone)
    {
    case Question:
         labelIcone->setPixmap(QPixmap("images/000-question.png"));
        break;

    case Information:
         labelIcone->setPixmap(QPixmap("images/001-information.png"));
        break;

    case Avertissement:
         labelIcone->setPixmap(QPixmap("images/002-warning.png"));
        break;

    case Critique:
         labelIcone->setPixmap(QPixmap("images/003-critical.png"));
        break;

    default: //AucuneIcone
         labelIcone->setPixmap(QPixmap());
         qDebug("Aucune icone attribuée");
        break;
    }
}



/// **-------**SLOTs**-------**
// Stocke le bouton qui à été cliqué dans le pointeur "bouton" et ferme la boite de dialogue
void GMessageBox::boutonCliquer()
{
    choix = qobject_cast<QPushButton*>(sender());
    accept();
}

// Ouvre la boite de dialogue et attend une réponse
int GMessageBox::exec()
{
    QDialog::exec();

    if (choix != 0)
    {
        RoleBouton role(listeBoutons->value(choix, AucunRole));
        choix = 0;
        return role;
    }

    return AucunRole;
}



/// **-------**STATICs**-------**
// Ouvre une boite de dialogue avec l'icone "Question"
int GMessageBox::question(QString titre, const QString &texte, QWidget *parent, RoleBouton bouton1, RoleBouton bouton2, RoleBouton bouton3, RoleBouton bouton4, RoleBouton bouton5)
{
    return GMessageBox(Question, titre, texte, parent, bouton1, bouton2, bouton3, bouton4, bouton5).exec();
}

// Ouvre une boite de dialogue avec l'icone "Information"
int GMessageBox::information(QString titre, const QString &texte, QWidget *parent, RoleBouton bouton1, RoleBouton bouton2, RoleBouton bouton3, RoleBouton bouton4, RoleBouton bouton5)
{
    return GMessageBox(Information, titre, texte, parent, bouton1, bouton2, bouton3, bouton4, bouton5).exec();
}

// Ouvre une boite de dialogue avec l'icone "Avertissement"
int GMessageBox::warning(QString titre, const QString &texte, QWidget *parent, RoleBouton bouton1, RoleBouton bouton2, RoleBouton bouton3, RoleBouton bouton4, RoleBouton bouton5)
{
    return GMessageBox(Avertissement, titre, texte, parent, bouton1, bouton2, bouton3, bouton4, bouton5).exec();
}

// Ouvre une boite de dialogue avec l'icone "Critique"
int GMessageBox::critical(QString titre, const QString &texte, QWidget *parent, RoleBouton bouton1, RoleBouton bouton2, RoleBouton bouton3, RoleBouton bouton4, RoleBouton bouton5)
{
    return GMessageBox(Critique, titre, texte, parent, bouton1, bouton2, bouton3, bouton4, bouton5).exec();
}

// Retourne les fichiers nécessaire à la classe GMessageBox
QStringList GMessageBox::getFilesList()
{
    QStringList listeFichiers;
        listeFichiers.append("images/000-question.png");
        listeFichiers.append("images/001-information.png");
        listeFichiers.append("images/002-warning.png");
        listeFichiers.append("images/003-critical.png");

    return listeFichiers;
}
