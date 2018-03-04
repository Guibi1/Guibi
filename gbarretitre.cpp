#include "gbarretitre.h"


GBarreTitre::GBarreTitre(QRgb couleur, QWidget *parent, TypeBoutonTitre type)
    : QFrame(parent, Qt::FramelessWindowHint),
      typeBouton(),
      couleurBoutons(couleur),
      pointDifference(),
      correct(true),
      layoutHPrincipal(0),
      layoutHBoutons(0),
      reduceButton(0),
      sizeButton(0),
      closeButton(0),
      icon(0),
      labelTitre(0)
{
    window()->setWindowFlag(Qt::FramelessWindowHint);

    /// Construction du GUI
    // Construit les QToolButtons
    reduceButton = new QToolButton();
        reduceButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        reduceButton->setIcon(QIcon(getColoredPixmap(Reduce)));

    sizeButton = new QToolButton();
        sizeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        windowViewChanged();

    closeButton = new QToolButton();
        closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        closeButton->setIcon(QIcon(getColoredPixmap(Close)));

    icon = new QToolButton();
        icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        iconChanged();

    labelTitre = new QLabel("<b>" + window()->windowTitle() + "</b>");
        labelTitre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        labelTitre->setTextFormat(Qt::RichText);
        labelTitre->installEventFilter(this);

    // Construit les layouts
    layoutHBoutons = new QHBoxLayout();
        layoutHBoutons->setMargin(0);
        layoutHBoutons->setSpacing(0);
        layoutHBoutons->addWidget(reduceButton, 0, Qt::AlignBaseline);
        layoutHBoutons->addWidget(sizeButton, 1, Qt::AlignBaseline);
        layoutHBoutons->addWidget(closeButton, 2, Qt::AlignBaseline);

    layoutHPrincipal = new QHBoxLayout(this);
        layoutHPrincipal->setMargin(0);
        layoutHPrincipal->setSpacing(10);
        layoutHPrincipal->addWidget(icon, 0, Qt::AlignBaseline);
        layoutHPrincipal->addSpacing(10);
        layoutHPrincipal->addWidget(labelTitre, 1, Qt::AlignBaseline);
        layoutHPrincipal->addLayout(layoutHBoutons, 2);

    /// Connects
    // Avec "window"
    connect(window(), SIGNAL(windowIconChanged(QIcon)), this, SLOT(iconChanged()));
    connect(window(), SIGNAL(windowTitleChanged(QString)), this, SLOT(titleChanged()));
    connect(window(), SIGNAL(viewChanged()), this, SLOT(windowViewChanged()));

    // Avec les boutons
    connect(reduceButton, SIGNAL(clicked(bool)), this, SLOT(reduceButtonClicked()));
    connect(sizeButton, SIGNAL(clicked(bool)), this, SLOT(sizeButtonClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClicked()));
    connect(icon, SIGNAL(clicked(bool)), this, SLOT(iconClicked()));

    connect(reduceButton, SIGNAL(pressed()), this, SLOT(buttonPressed()));
    connect(sizeButton, SIGNAL(pressed()), this, SLOT(buttonPressed()));
    connect(closeButton, SIGNAL(pressed()), this, SLOT(buttonPressed()));
    connect(icon, SIGNAL(pressed()), this, SLOT(buttonPressed()));

    setFixedHeight(25);
    setTypeBoutonTitre(type);
}

void GBarreTitre::setTypeBoutonTitre(GBarreTitre::TypeBoutonTitre type)
{
    typeBouton = type;

    reduceButton->setVisible(false);
    sizeButton->setVisible(false);
    closeButton->setEnabled(false);

    switch (typeBouton)
    {
    case Tout:
        reduceButton->setVisible(true);
            reduceButton->setEnabled(true);
        sizeButton->setVisible(true);
            sizeButton->setEnabled(true);
        closeButton->setVisible(true);
            closeButton->setEnabled(true);
        break;

    case Aucun:
        reduceButton->setVisible(false);
        sizeButton->setVisible(false);
        closeButton->setVisible(true);
            closeButton->setEnabled(false);
        break;

    case Fermer:
        closeButton->setVisible(true);
            closeButton->setEnabled(true);
        break;

    case Reduire:
        sizeButton->setVisible(true);
            sizeButton->setEnabled(true);
        break;

    case Minimiser:
        reduceButton->setVisible(true);
            reduceButton->setEnabled(true);
        break;
    }
}

QPixmap GBarreTitre::getColoredPixmap(SorteBouton bouton)
{
    QImage image;

    switch (bouton)
    {
    case Close:
        image = QImage("images/005-close.png");
        break;

    case Reduce:
        image = QImage("images/006-Reduce.png");
        break;

    case Maximize:
        image = QImage("images/007-maximize.png");
        break;

    case Minimize:
        image = QImage("images/008-minimize.png");
        break;

    default:
        image = QImage();
        break;
    }

    image.setColorTable(QVector<QRgb>(1, couleurBoutons));

    return QPixmap::fromImage(image);
}

void GBarreTitre::mousePressEvent(QMouseEvent *event)
{
    pointDifference.setX(event->x());
    pointDifference.setY(event->y());
}

void GBarreTitre::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->globalY() <= 1 && (typeBouton == GBarreTitre::TypeBoutonTitre::Tout || typeBouton == GBarreTitre::TypeBoutonTitre::Reduire))
    {
        window()->showMaximized();

        windowViewChanged();
    }

    correct = true;
}

void GBarreTitre::mouseMoveEvent(QMouseEvent *event)
{
    if (!window()->isMaximized())
    {
        if (correct == true)
        {
            QPoint p(event->globalX(), event->globalY());

            window()->move(p - (pointDifference + QPoint(window()->layout()->margin(), window()->layout()->margin())));
        }

        else
        {
            pointDifference.setX(event->x());
            pointDifference.setY(event->y());
        }
    }
}

bool GBarreTitre::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == labelTitre)
        event->ignore();

    return false;
}



/// **-------**SLOTs**-------**
//
void GBarreTitre::reduceButtonClicked()
{
    window()->showMinimized();

    correct = true;
}

void GBarreTitre::sizeButtonClicked()
{
    if (window()->isMaximized())
        window()->showNormal();

    else
        window()->showMaximized();

    windowViewChanged();

    correct = true;
}

 void GBarreTitre::closeButtonClicked()
{
    emit willSoonExit();

    window()->close();

    correct = true;
}

void GBarreTitre::iconClicked()
{
    if (!icon->icon().isNull())
        emit iconPressed();

    correct = true;
}

void GBarreTitre::buttonPressed()
{
    correct = false;
}

void GBarreTitre::titleChanged()
{
    labelTitre->setText("<b>" + window()->windowTitle() + "</b>");
}

void GBarreTitre::iconChanged()
{
    icon->setIcon(window()->windowIcon());

    if (window()->windowIcon().isNull())
        icon->hide();
}

void GBarreTitre::windowViewChanged()
{
    if (window()->isMaximized())
        sizeButton->setIcon(QIcon(getColoredPixmap(Minimize)));

    else
        sizeButton->setIcon(QIcon(getColoredPixmap(Maximize)));
}



/// **-------**STATICs**-------**
// Retourne les fichiers nécessaire à la classe GMessageBox
QStringList GBarreTitre::getFilesList()
{
    QStringList listeFichiers;
        listeFichiers.append("images/000-question.png");
        listeFichiers.append("images/001-information.png");
        listeFichiers.append("images/002-warning.png");
        listeFichiers.append("images/003-critical.png");

    return listeFichiers;
}
