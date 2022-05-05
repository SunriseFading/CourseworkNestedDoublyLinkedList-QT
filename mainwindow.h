#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>

#include "branch.h"
#include "list1.h"
#include "list2.h"
#include "people.h"
#include "professor.h"
#include "student.h"
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void tab1(Branch *B, People *P, int j);
    void tab2(Branch *B, People *P, int j);
    void tab3(Branch *B, int j);
    int check_id(int kod, int n);
    int check_name(QString name, int s);
    void clear_p();
    void clear_s();
    void clear_w();
    void clear_b();
    int search_id(int kod);
    int search_name(QString name);
    void add_g();
    void add_m();
    void add_bag();
    void add_headdress();
    void add_belt();
    void add_shop();
    void write_to_file(QString str);
    void edit(int itm);

private slots:
    void on_Choose_clicked();
    void on_tip_activated(int index);
    void on_add_p_clicked();
    void on_add_br_clicked();
    void on_add_s_clicked();
    void on_add_w_clicked();
    void on_Edit_clicked();
    void on_Delete_clicked();
    void on_delete_b_clicked();
    void on_branch_clicked();
    void on_edit_b_clicked();
    void on_search_by_activated(int index);
    void on_search_clicked();
    void on_Search_clicked();
    void on_Return_clicked();
    void on_edit_p_clicked();
    void on_edit_s_clicked();
    void on_edit_w_clicked();
    void on_edit_br_clicked();
    void on_add_b_clicked();
    void on_Exit_triggered();
    void on_about_triggered();
    void on_manual_triggered();
    void on_Create_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_Save_As_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
