#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Changed();

    /* menu file */

    void on_ActionNew_triggered();

    void on_ActionOpen_triggered();

    void on_ActionSave_triggered();

    void on_ActionSave_as_triggered();

    /* menu edit */

    void on_ActionCopy_triggered();

    void on_ActionCut_triggered();

    void on_ActionPaste_triggered();

    void on_ActionUndo_triggered();

    void on_ActionRedo_triggered();

    /* menu help */

    void on_ActionAbout_triggered();

private:
    Ui::MainWindow *ui;

    QString m_Filename;

    bool m_Changed;
};

#endif // MAINWINDOW_H
