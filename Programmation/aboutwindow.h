#ifndef ABOUTWINDOWJIUEYT_H
#define ABOUTWINDOWJIUEYT_H

// On inclue les librairies nécessaires à la fenêtre "A Propos"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QMainWindow>
#include <QDesktopServices>

// On défini le namespace pour QT
QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutWindow;
} // namespace Ui

QT_END_NAMESPACE

// On initialise la classe AboutWindow

class AboutWindow : public QDialog
{

// Dans la partie public, on retrouve tout ce qui relève de l'affichage
public:

    // On commence par définir les widgets qui seront utilisés sur l'interface
    QLabel *Lilian;
    QLabel *Simon;
    QLabel *label;
    QLabel *github_lilian;
    QLabel *github_simon;
    QPushButton *pushButton;

    // Déclaration du constructeur et du destructeur
    AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

    void setupUi(QDialog *Dialog)
    {
        // On donne le nom de la fenêtre et ses dimensions
        Dialog->setObjectName("Dialog");
        Dialog->resize(320, 240);
        Dialog->setWindowTitle("About authors");

        // On crée la photo de Lilian
        Lilian = new QLabel(Dialog);
        Lilian->setObjectName("Lilian");
        Lilian->setGeometry(QRect(0, -10, 91, 151));
        Lilian->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/about/Lilian.jpg"));

        // On crée la photo de Simon
        Simon = new QLabel(Dialog);
        Simon->setObjectName("Simon");
        Simon->setGeometry(QRect(0, 160, 91, 81));
        Simon->setPixmap(QPixmap(QApplication::applicationDirPath() + "/ressources/about/Simon.jpg"));

        // On crée le texte de la fenêtre
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 10, 141, 81));
        label->setAutoFillBackground(false);
        label->setWordWrap(true);
        label->setText("Authors are Lilian Cizeron and Simon Provot, two engeneers students in Software Cybersecurity at ENSIBS.");

        // On crée le lien vers le Github de Lilian
        github_lilian = new QLabel(Dialog);
        github_lilian->setObjectName("github_lilian");
        github_lilian->setGeometry(QRect(100, 120, 71, 31));
        github_lilian->setText("<a href = \"https://www.github.com/Lilianc2000\">Github</a>");
        github_lilian->setTextFormat(Qt::RichText);
        github_lilian->setTextInteractionFlags(Qt::TextBrowserInteraction);
        github_lilian->setOpenExternalLinks(true);

        // On crée le lien vers le Github de Simon
        github_simon = new QLabel(Dialog);
        github_simon->setObjectName("github_simon");
        github_simon->setGeometry(QRect(100, 200, 71, 31));
        github_simon->setText("<a href = \"https://github.com/OnlyAtN1ght\">Github</a>");
        github_simon->setTextFormat(Qt::RichText);
        github_simon->setTextInteractionFlags(Qt::TextBrowserInteraction);
        github_simon->setOpenExternalLinks(true);

        // On crée le bouton ok pour fermer la fenêtre de dialogue
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(240, 210, 75, 24));
        pushButton->setText("Ok");

        // On le connecte à la fonction qui ferme la fenêtre
        connect(pushButton, &QPushButton::pressed, this, &AboutWindow::close);

        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    }

// Dans la partie privée, on retrouve la fonction  pour fermer la fenêtre
private:

    Ui::AboutWindow *ui;

    // Fonction pour fermer la fenêtre de dialogue
    void close(){

        this->done(1);

    }

};

#endif // ABOUTWINDOWJIUEYT_H
