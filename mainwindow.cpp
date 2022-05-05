#include "mainwindow.h"
#include "ui_mainwindow.h"

List2 *Br;
People *people;
Branch *branch;
int num, k, n = 0, k1, item, s = 0, check_item_number, num1;
QString check, address, str, type;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Information retrieval system \"University\"");
    Br = new List2();
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->stackedWidget->setCurrentIndex(8);
    ui->Return->setDisabled(0);
    ui->edit_p->setDisabled(1);
    ui->edit_s->setDisabled(1);
    ui->edit_w->setDisabled(1);
    ui->edit_br->setDisabled(1);
    ui->Search->setDisabled(1);
    ui->table1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table1->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table1->setRowHeight(1000, 25);
    ui->table2->setRowHeight(1000, 25);
    ui->table3->setRowHeight(1000, 25);
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QRegExp num1("[0-9]{1,8}"); //Ввод только цифр
    QValidator *num1Validator = new QRegExpValidator(num1, this);
    QRegExp name("[A-Za-zА-Яа-яЁё]{1}[A-Za-zА-Яа-яЁё\\s\\.]{1,30}"); //Ввод только букв латиницы или кириллицы, пробелов и точек
    QValidator *strValidator = new QRegExpValidator(name, this);
    QRegExp num2("[0-9]{1,11}"); //Ввод только цифр
    QValidator *num2Validator = new QRegExpValidator(num2, this);
    ui->id_p->setValidator(num1Validator);
    ui->id_s->setValidator(num1Validator);
    ui->id_w->setValidator(num1Validator);
    ui->full_name_p->setValidator(strValidator);
    ui->full_name_s->setValidator(strValidator);
    ui->full_name_w->setValidator(strValidator);
    ui->age_p->setValidator(num1Validator);
    ui->age_s->setValidator(num1Validator);
    ui->age_w->setValidator(num1Validator);
    ui->subject_p->setValidator(strValidator);
    ui->salary_p->setValidator(num2Validator);
    ui->salary_w->setValidator(num2Validator);
    ui->index_b->setValidator(num1Validator);
    ui->region_b->setValidator(strValidator);
    ui->city_b->setValidator(strValidator);
    ui->number_b->setValidator(num2Validator);
    ui->department_p->addItems(QStringList()
                               << tr("Department of Information Systems and Digital Technologies")
                               << tr("Department of Technical Physics and Mathematics")
                               << tr("Department of Information Security")
                               << tr("Department of Electronics, Radio Engineering and Communication Systems")
                               << tr("Department of Automated Control Systems and Cybernetics"));

    ui->department_s->addItems(QStringList()
                               << tr("Department of Information Systems and Digital Technologies")
                               << tr("Department of Technical Physics and Mathematics")
                               << tr("Department of Information Security")
                               << tr("Department of Electronics, Radio Engineering and Communication Systems")
                               << tr("Department of Automated Control Systems and Cybernetics"));
    ui->position_w->addItems(QStringList()
                             << tr("Guard")
                             << tr("Wardrobe maker")
                             << tr("Cleaner"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear_p()
{
    ui->department_p->setCurrentIndex(0);
    ui->id_p->clear();
    ui->full_name_p->clear();
    ui->age_p->clear();
    ui->salary_p->clear();
    ui->subject_p->clear();
}

void MainWindow::clear_b()
{
    ui->region_b->clear();
    ui->city_b->clear();
    ui->street_b->clear();
    ui->index_b->clear();
    ui->name_b->clear();
    ui->number_b->clear();
}

void MainWindow::clear_s()
{
    ui->department_s->setCurrentIndex(0);
    ui->id_s->clear();
    ui->full_name_s->clear();
    ui->age_s->clear();
    ui->group_s->clear();
}

void MainWindow::clear_w()
{
    ui->position_w->setCurrentIndex(0);
    ui->id_w->clear();
    ui->full_name_w->clear();
    ui->age_w->clear();
    ui->salary_w->clear();
}

void MainWindow::write_to_file(QString str1)
{
    QFile file(str1);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        Branch *B = Br->get_tail();
        for (int i = 0; i < Br->get_count(); i++)
        {
            out << B->get_name() << "|"
                << B->get_index() << "|"
                << B->get_region() << "|"
                << B->get_city() << "|"
                << B->get_street() << "|"
                << B->get_number() << endl;
            People *P = B->get_tail();
            for (int j = 0; j < B->get_count(); j++)
            {
                out << " " << P->get_id() << "|"
                    << P->get_type() << "|"
                    << P->get_full_name() << "|"
                    << P->get_age() << "|";
                if (P->get_type() == "Professor")
                {
                    out << dynamic_cast<Professor *>(P)->get_subject() << "|"
                        << dynamic_cast<Professor *>(P)->get_salary() << "|"
                        << dynamic_cast<Professor *>(P)->get_department() << "|"
                        << B->get_name() << endl;
                }
                else if (P->get_type() == "Student")
                {
                    out << dynamic_cast<Student *>(P)->get_group() << "|"
                        << ""
                        << "|"
                        << dynamic_cast<Student *>(P)->get_department() << "|"
                        << B->get_name() << endl;
                }
                else if (P->get_type() == "Worker")
                {
                    out << dynamic_cast<Worker *>(P)->get_position() << "|"
                        << dynamic_cast<Worker *>(P)->get_salary() << "|"
                        << ""
                        << "|"
                        << B->get_name() << endl;
                }

                P = P->get_prev();
            }
            B = B->get_prev();
        }
    }
    else
        QMessageBox::warning(this, "Error", "Unable to open file");
}

int MainWindow::search_id(int id)
{
    branch = Br->get_head();
    for (int i = 0; i < Br->get_count(); i++)
    {
        people = branch->get_head();
        for (int j = 0; j < branch->get_count(); j++)
        {
            if (people->get_id() == QString::number(id))
            {
                return 0;
            }
            people = people->get_next();
        }
        branch = branch->get_next();
    }
    return 0;
}

int MainWindow::search_name(QString name)
{
    branch = Br->get_head();
    for (int i = 0; i < Br->get_count(); i++)
    {
        if (branch->get_name() == name)
            return 0;
        branch = branch->get_next();
    }
    return 0;
}

void MainWindow::tab1(Branch *B, People *P, int j)
{
    ui->table1->setItem(j, 0, new QTableWidgetItem(P->get_id()));
    ui->table1->setItem(j, 1, new QTableWidgetItem(P->get_type()));
    ui->table1->setItem(j, 2, new QTableWidgetItem(P->get_full_name()));
    ui->table1->setItem(j, 3, new QTableWidgetItem(P->get_age()));
    ui->table1->setItem(j, 7, new QTableWidgetItem(B->get_name()));
    if (P->get_type() == "Professor")
    {
        ui->table1->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_subject()));
        ui->table1->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_salary()));
        ui->table1->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_department()));
    }
    else if (P->get_type() == "Student")
    {
        ui->table1->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Student *>(P)->get_group()));
        ui->table1->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Student *>(P)->get_department()));
    }
    else if (P->get_type() == "Worker")
    {
        ui->table1->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Worker *>(P)->get_position()));
        ui->table1->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Worker *>(P)->get_salary()));
    }
}
void MainWindow::tab2(Branch *B, People *P, int j)
{
    ui->table2->insertRow(ui->table2->rowCount());
    ui->table2->setItem(j, 0, new QTableWidgetItem(P->get_id()));
    ui->table2->setItem(j, 1, new QTableWidgetItem(P->get_type()));
    ui->table2->setItem(j, 2, new QTableWidgetItem(P->get_full_name()));
    ui->table2->setItem(j, 3, new QTableWidgetItem(P->get_age()));
    ui->table2->setItem(j, 7, new QTableWidgetItem(B->get_name()));
    if (P->get_type() == "Professor")
    {
        ui->table2->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_subject()));
        ui->table2->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_salary()));
        ui->table2->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Professor *>(P)->get_department()));
    }
    else if (P->get_type() == "Student")
    {
        ui->table2->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Student *>(P)->get_group()));
        ui->table2->setItem(j, 6, new QTableWidgetItem(dynamic_cast<Student *>(P)->get_department()));
    }
    else if (P->get_type() == "Worker")
    {
        ui->table2->setItem(j, 4, new QTableWidgetItem(dynamic_cast<Worker *>(P)->get_position()));
        ui->table2->setItem(j, 5, new QTableWidgetItem(dynamic_cast<Worker *>(P)->get_salary()));
    }
}

void MainWindow::tab3(Branch *B, int j)
{
    ui->table3->setItem(j, 0, new QTableWidgetItem(B->get_name()));
    ui->table3->setItem(j, 1, new QTableWidgetItem(B->get_index()));
    ui->table3->setItem(j, 2, new QTableWidgetItem(B->get_region()));
    ui->table3->setItem(j, 3, new QTableWidgetItem(B->get_city()));
    ui->table3->setItem(j, 4, new QTableWidgetItem(B->get_street()));
    ui->table3->setItem(j, 5, new QTableWidgetItem(B->get_number()));
}

void MainWindow::on_search_by_activated(int index)
{
    if (index == 1)
        ui->stackedWidget_2->setCurrentIndex(1);
    else
        ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_add_b_clicked()
{
    ui->add_br->setDisabled(0);
    ui->edit_br->setDisabled(1);
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_Choose_clicked()
{
    if (Br->get_count() != 0)
    {
        ui->add_p->setDisabled(0);
        ui->add_s->setDisabled(0);
        ui->add_w->setDisabled(0);
        ui->edit_p->setDisabled(1);
        ui->edit_s->setDisabled(1);
        ui->edit_w->setDisabled(1);
        ui->Return->setDisabled(0);
        int x = ui->tip->currentIndex();
        if (x == 0)
            ui->stackedWidget->setCurrentIndex(1);
        if (x == 1)
            ui->stackedWidget->setCurrentIndex(2);
        if (x == 2)
            ui->stackedWidget->setCurrentIndex(3);
    }
    else
        QMessageBox::warning(this, "Error", "Unable to add new product");
}

void MainWindow::on_add_br_clicked()
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->name_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_name_b->setStyleSheet("QLabel { color : white; }");
    QString temp_name = ui->name_b->text();
    bool correct_name = true;
    for (int i = 0; i < ui->table3->rowCount(); i++)
    {
        if (ui->table3->item(i, 0)->text() == temp_name)
        {
            correct_name = false;
        }
    }
    if (!correct_name)
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->number_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_number_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_number_b->setStyleSheet("QLabel { color : white; }");
    if (ui->index_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_index_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_index_b->setStyleSheet("QLabel { color : white; }");
    if (ui->region_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_region_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_region_b->setStyleSheet("QLabel { color : white; }");
    if (ui->city_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_city_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_city_b->setStyleSheet("QLabel { color : white; }");
    if (ui->street_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_street_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_street_b->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        QString region = ui->region_b->text();
        QString city = ui->city_b->text();
        QString street = ui->street_b->text();
        QString index = ui->index_b->text();
        QString number = ui->number_b->text();
        QString name = ui->name_b->text();
        Br->add_branch(name, index, region, city, street, number);
        Branch *B = Br->get_head();
        ui->table3->insertRow(ui->table3->rowCount());
        tab3(B, s);
        s++;
        ui->branch_p->addItem(name);
        ui->branch_w->addItem(name);
        ui->branch_s->addItem(name);
        ui->choice_b->addItem(name);
        clear_b();
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_3->setCurrentIndex(0);
        if (Br->get_count() != 0)
            ui->tip->setDisabled(0);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_add_p_clicked()
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_p->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_p->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_p->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_p->setStyleSheet("QLabel { color : white; }");
    if (ui->age_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_p->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_p->setStyleSheet("QLabel { color : white; }");
    if (ui->subject_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_subject_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subject_p->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        k = ui->branch_p->currentIndex();
        int l = 0;
        Branch *B = Br->get_tail();
        while (l != k)
        {
            B = B->get_prev();
            l++;
        }
        QString id = ui->id_p->text();
        QString full_name = ui->full_name_p->text();
        QString age = ui->age_p->text();
        QString department = ui->department_p->currentText();
        QString salary = ui->salary_p->text();
        QString subject = ui->subject_p->text();
        B->add_professor(id, full_name, age, department, subject, salary);
        People *P = B->get_head();
        ui->table1->insertRow(ui->table1->rowCount());
        tab1(B, P, n);
        n++;
        clear_p();
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_add_s_clicked()
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_s->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_s->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_s->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_s->setStyleSheet("QLabel { color : white; }");
    if (ui->age_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_s->setStyleSheet("QLabel { color : white; }");
    if (ui->group_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_group_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_group_s->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        k = ui->branch_s->currentIndex();
        int l = 0;
        Branch *B = Br->get_tail();
        while (l != k)
        {
            B = B->get_prev();
            l++;
        }
        QString id = ui->id_s->text();
        QString full_name = ui->full_name_s->text();
        QString age = ui->age_s->text();
        QString department = ui->department_s->currentText();
        QString group = ui->group_s->text();
        B->add_student(id, full_name, age, department, group);
        People *P = B->get_head();
        ui->table1->insertRow(ui->table1->rowCount());
        tab1(B, P, n);
        n++;
        clear_s();
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_add_w_clicked()
{
    ui->Return->setDisabled(1);
    bool not_correct = false;
    if (ui->id_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_w->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_w->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if (ui->table1->item(i, 0)->text() == temp_id)
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_w->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_w->setStyleSheet("QLabel { color : white; }");
    if (ui->age_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_w->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_w->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        k = ui->branch_w->currentIndex();
        int l = 0;
        Branch *B = Br->get_tail();
        while (l != k)
        {
            B = B->get_prev();
            l++;
        }
        QString id = ui->id_w->text();
        QString full_name = ui->full_name_w->text();
        QString age = ui->age_w->text();
        QString position = ui->position_w->currentText();
        QString salary = ui->salary_w->text();
        B->add_worker(id, full_name, age, position, salary);
        People *P = B->get_head();
        ui->table1->insertRow(ui->table1->rowCount());
        tab1(B, P, n);
        n++;
        clear_w();
        ui->stackedWidget->setCurrentIndex(0);
        ui->Search->setDisabled(0);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_Delete_clicked()
{
    if (ui->stackedWidget_3->currentIndex() == 1)
        QMessageBox::warning(this, "Error", "Error");
    else
    {
        QItemSelectionModel *selectionModel = ui->table1->selectionModel();
        if (selectionModel->hasSelection())
        {
            item = ui->table1->currentRow();
            int id = ui->table1->item(item, 0)->text().toInt();
            address = ui->table1->item(item, 7)->text();
            ui->table1->removeRow(item);
            Branch *B = Br->get_tail();
            for (int i = 0; i < Br->get_count(); i++)
            {
                if (B->get_name() == address)
                {
                    B->del(id);
                    break;
                }
                B = B->get_prev();
            }
            n--;
            if (n == 0)
            {
                ui->Search->setDisabled(1);
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Choose a line");
        }
    }
}

void MainWindow::on_delete_b_clicked()
{
    QItemSelectionModel *selectionModel = ui->table3->selectionModel();
    if (selectionModel->hasSelection())
    {
        item = ui->table3->currentRow();
        ui->table3->removeRow(item);
        s--;
        ui->choice_b->removeItem(item);
        ui->branch_p->removeItem(item);
        ui->branch_s->removeItem(item);
        ui->branch_w->removeItem(item);
        int l = 0;
        Branch *B = Br->get_tail();
        while (l != item)
        {
            B = B->get_prev();
            l++;
        }
        for (int i = 0; i < n; i++)
        {
            if (ui->table1->item(i, 7)->text() == B->get_name())
            {
                ui->table1->removeRow(i);
                i--;
                n--;
            }
        }
        Br->del(item);
        if (Br->get_count() == 0)
        {
            ui->Search->setDisabled(1);
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_branch_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->stackedWidget->setCurrentIndex(8);
    ui->Return->setDisabled(0);
}

void MainWindow::on_search_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    int h = n;
    for (int i = 0; i < h; i++)
    {
        ui->table2->removeRow(i);
        i--;
        h--;
    }
    int f = 0;
    if (ui->search_by->currentIndex() == 0)
    {
        Branch *B = Br->get_tail();
        for (int i = 0; i < Br->get_count(); i++)
        {
            People *P = B->get_tail();
            for (int j = 0; j < B->get_count(); j++)
            {
                if (P->get_id() == ui->data->text())
                {
                    tab2(B, P, f);
                    f++;
                }
                P = P->get_prev();
            }
            B = B->get_prev();
        }
        f = 0;
    }
    else if (ui->search_by->currentIndex() == 1)
    {
        int l = 0;
        Branch *B = Br->get_tail();
        k = ui->choice_b->currentIndex();
        while (l != k)
        {
            B = B->get_prev();
            l++;
        }
        People *P = B->get_tail();
        {
            for (int i = 0; i < B->get_count(); i++)
            {
                tab2(B, P, f);
                f++;
                P = P->get_prev();
            }
        }
        f = 0;
    }
    else if (ui->search_by->currentIndex() == 2)
    {
        Branch *B = Br->get_tail();
        for (int i = 0; i < Br->get_count(); i++)
        {
            People *P = B->get_tail();
            for (int j = 0; j < B->get_count(); j++)
            {
                if (P->get_type() == ui->data->text())
                {
                    tab2(B, P, f);
                    f++;
                }
                P = P->get_prev();
            }
            B = B->get_prev();
        }
        f = 0;
    }
    ui->data->clear();
    ui->choice_b->setCurrentText(0);
}

void MainWindow::on_Search_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->Return->setDisabled(0);
}

void MainWindow::on_Return_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->Return->setDisabled(1);
}

void MainWindow::on_Edit_clicked()
{
    QItemSelectionModel *selectionModel = ui->table1->selectionModel();
    if (selectionModel->hasSelection())
    {
        ui->edit_p->setDisabled(0);
        ui->edit_s->setDisabled(0);
        ui->edit_w->setDisabled(0);
        ui->add_p->setDisabled(1);
        ui->add_s->setDisabled(1);
        ui->add_w->setDisabled(1);
        item = ui->table1->currentRow();
        QString type = ui->table1->item(item, 1)->text();
        if (type == "Professor")
        {
            ui->stackedWidget->setCurrentIndex(1);
            ui->id_p->setText(ui->table1->item(item, 0)->text());
            ui->full_name_p->setText(ui->table1->item(item, 2)->text());
            ui->age_p->setText(ui->table1->item(item, 3)->text());
            ui->subject_p->setText(ui->table1->item(item, 4)->text());
            ui->salary_p->setText(ui->table1->item(item, 5)->text());
            ui->department_p->setCurrentText(ui->table1->item(item, 6)->text());
            Branch *B = Br->get_tail();
            QString address = ui->table1->item(item, 7)->text();
            int l = 0;
            while (l != Br->get_count())
            {
                if (B->get_name() == address)
                    break;
                l++;
                B = B->get_prev();
            }
            ui->branch_p->setCurrentIndex(l);
            k1 = l;
            num1 = num;
        }
        else if (type == "Student")
        {
            ui->stackedWidget->setCurrentIndex(2);
            ui->id_s->setText(ui->table1->item(item, 0)->text());
            ui->full_name_s->setText(ui->table1->item(item, 2)->text());
            ui->age_s->setText(ui->table1->item(item, 3)->text());
            ui->group_s->setText(ui->table1->item(item, 4)->text());
            ui->department_s->setCurrentText(ui->table1->item(item, 6)->text());
            Branch *B = Br->get_tail();
            address = ui->table1->item(item, 7)->text();
            int l = 0;
            while (l != Br->get_count())
            {
                if (B->get_name() == address)
                    break;
                l++;
                B = B->get_prev();
            }
            ui->branch_s->setCurrentIndex(l);
            k1 = l;
            num1 = num;
        }
        else if (type == "Worker")
        {
            ui->stackedWidget->setCurrentIndex(3);
            ui->id_w->setText(ui->table1->item(item, 0)->text());
            ui->full_name_w->setText(ui->table1->item(item, 2)->text());
            ui->age_w->setText(ui->table1->item(item, 3)->text());
            ui->position_w->setCurrentText(ui->table1->item(item, 4)->text());
            ui->salary_w->setText(ui->table1->item(item, 5)->text());
            Branch *B = Br->get_tail();
            address = ui->table1->item(item, 7)->text();
            int l = 0;
            while (l != Br->get_count())
            {
                if (B->get_name() == address)
                    break;
                l++;
                B = B->get_prev();
            }
            ui->branch_w->setCurrentIndex(l);
            k1 = l;
            num1 = num;
        }
        search_id(ui->table1->item(item, 0)->text().toInt());
        num1 = ui->table1->item(item, 0)->text().toInt();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_edit_b_clicked()
{
    QItemSelectionModel *selectionModel = ui->table3->selectionModel();
    if (selectionModel->hasSelection())
    {
        ui->stackedWidget->setCurrentIndex(6);
        ui->edit_br->setDisabled(0);
        ui->add_br->setDisabled(1);
        item = ui->table3->currentRow();
        ui->index_b->setText(ui->table3->item(item, 1)->text());
        ui->name_b->setText(ui->table3->item(item, 0)->text());
        ui->street_b->setText(ui->table3->item(item, 4)->text());
        ui->city_b->setText(ui->table3->item(item, 3)->text());
        ui->region_b->setText(ui->table3->item(item, 2)->text());
        ui->number_b->setText(ui->table3->item(item, 5)->text());
        search_name(ui->table3->item(item, 0)->text());
    }
    else
    {
        QMessageBox::warning(this, "Error", "Choose a line");
    }
}

void MainWindow::on_edit_p_clicked()
{
    bool not_correct = false;
    if (ui->id_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_p->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_p->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_p->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_p->setStyleSheet("QLabel { color : white; }");
    if (ui->age_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_p->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_p->setStyleSheet("QLabel { color : white; }");
    if (ui->subject_p->text().isEmpty())
    {
        not_correct = true;
        ui->label_subject_p->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_subject_p->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        QString id = ui->id_p->text();
        QString full_name = ui->full_name_p->text();
        QString age = ui->age_p->text();
        QString department = ui->department_p->currentText();
        QString salary = ui->salary_p->text();
        QString subject = ui->subject_p->text();
        k = ui->branch_p->currentIndex();
        if (k1 != k)
        {
            branch->del(num1);
            int l = 0;
            Branch *B = Br->get_tail();
            while (l != k)
            {
                B = B->get_prev();
                l++;
            }

            B->add_professor(id, full_name, age, department, subject, salary);
            People *P = B->get_head();
            tab1(B, P, item);
            ui->add_p->setDisabled(0);
            ui->edit_p->setDisabled(1);
            ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
            People *P = new Professor(id, full_name, age, department, subject, salary);
            if (branch->get_count() != 1)
            {
                people->get_prev()->set_next(P);
                people->get_next()->set_prev(P);
                P->set_next(people->get_next());
                P->set_prev(people->get_prev());
            }
            else
            {
                P->set_next(P);
                P->set_prev(P);
            }
            if (branch->get_head() == people)
                branch->set_head(P);
            if (branch->get_tail() == people)
                branch->set_tail(P);
            tab1(branch, P, item);
            ui->add_p->setDisabled(0);
            ui->edit_p->setDisabled(1);
            ui->stackedWidget->setCurrentIndex(0);
        }
        clear_p();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_edit_s_clicked()
{
    bool not_correct = false;
    if (ui->id_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_s->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_s->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_s->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_s->setStyleSheet("QLabel { color : white; }");
    if (ui->age_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_s->setStyleSheet("QLabel { color : white; }");
    if (ui->group_s->text().isEmpty())
    {
        not_correct = true;
        ui->label_group_s->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_group_s->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        QString id = ui->id_s->text();
        QString full_name = ui->full_name_s->text();
        QString age = ui->age_s->text();
        QString department = ui->department_s->currentText();
        QString group = ui->group_s->text();
        k = ui->branch_s->currentIndex();
        if (k1 != k)
        {
            branch->del(num1);
            int l = 0;
            Branch *B = Br->get_tail();
            while (l != k)
            {
                B = B->get_prev();
                l++;
            }
            B->add_student(id, full_name, age, department, group);
            People *P = B->get_head();
            tab1(B, P, item);
            ui->stackedWidget->setCurrentIndex(0);
            ui->add_s->setDisabled(0);
            ui->edit_s->setDisabled(1);
        }
        else
        {
            People *P = new Student(id, full_name, age, department, group);
            if (branch->get_count() != 1)
            {
                people->get_prev()->set_next(P);
                people->get_next()->set_prev(P);
                P->set_next(people->get_next());
                P->set_prev(people->get_prev());
            }
            else
            {
                P->set_next(P);
                P->set_prev(P);
            }
            if (branch->get_head() == people)
                branch->set_head(P);
            if (branch->get_tail() == people)
                branch->set_tail(P);
            tab1(branch, P, item);
            ui->add_s->setDisabled(0);
            ui->edit_s->setDisabled(1);
            ui->stackedWidget->setCurrentIndex(0);
        }
        clear_s();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_edit_w_clicked()
{
    bool not_correct = false;
    if (ui->id_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_id_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_id_w->setStyleSheet("QLabel { color : white; }");
    QString temp_id = ui->id_w->text();
    bool correct_id = true;
    for (int i = 0; i < ui->table1->rowCount(); i++)
    {
        if ((ui->table1->item(i, 0)->text() == temp_id) && (ui->table1->item(ui->table1->currentRow(), 0)->text() != temp_id))
        {
            correct_id = false;
        }
    }
    if (!correct_id)
    {
        not_correct = true;
        ui->label_id_w->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->full_name_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_full_name_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_full_name_w->setStyleSheet("QLabel { color : white; }");
    if (ui->age_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_age_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_age_w->setStyleSheet("QLabel { color : white; }");
    if (ui->salary_w->text().isEmpty())
    {
        not_correct = true;
        ui->label_salary_w->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_salary_w->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        QString id = ui->id_w->text();
        QString full_name = ui->full_name_w->text();
        QString age = ui->age_w->text();
        QString position = ui->position_w->currentText();
        QString salary = ui->salary_w->text();
        k = ui->branch_w->currentIndex();
        if (k1 != k)
        {
            branch->del(num1);
            int l = 0;
            Branch *B = Br->get_tail();
            while (l != k)
            {
                B = B->get_prev();
                l++;
            }
            B->add_worker(id, full_name, age, position, salary);
            People *P = B->get_head();
            tab1(B, P, item);
            ui->stackedWidget->setCurrentIndex(0);
            ui->add_w->setDisabled(0);
            ui->edit_w->setDisabled(1);
        }
        else
        {
            People *P = new Worker(id, full_name, age, position, salary);
            if (branch->get_count() != 1)
            {
                people->get_prev()->set_next(P);
                people->get_next()->set_prev(P);
                P->set_next(people->get_next());
                P->set_prev(people->get_prev());
            }
            else
            {
                P->set_next(P);
                P->set_prev(P);
            }
            if (branch->get_head() == people)
                branch->set_head(P);
            if (branch->get_tail() == people)
                branch->set_tail(P);
            tab1(branch, P, item);
            ui->add_w->setDisabled(0);
            ui->edit_w->setDisabled(1);
            ui->stackedWidget->setCurrentIndex(0);
        }
        clear_w();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_edit_br_clicked()
{
    bool not_correct = false;
    if (ui->name_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_name_b->setStyleSheet("QLabel { color : white; }");
    QString temp_name = ui->name_b->text();
    bool correct_name = true;
    for (int i = 0; i < ui->table3->rowCount(); i++)
    {
        if ((ui->table3->item(i, 0)->text() == temp_name) && (ui->table3->item(ui->table3->currentRow(), 0)->text() != temp_name))
        {
            correct_name = false;
        }
    }
    if (!correct_name)
    {
        not_correct = true;
        ui->label_name_b->setStyleSheet("QLabel { color : red; }");
    }

    if (ui->number_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_number_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_number_b->setStyleSheet("QLabel { color : white; }");
    if (ui->index_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_index_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_index_b->setStyleSheet("QLabel { color : white; }");
    if (ui->region_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_region_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_region_b->setStyleSheet("QLabel { color : white; }");
    if (ui->city_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_city_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_city_b->setStyleSheet("QLabel { color : white; }");
    if (ui->street_b->text().isEmpty())
    {
        not_correct = true;
        ui->label_street_b->setStyleSheet("QLabel { color : red; }");
    }
    else
        ui->label_street_b->setStyleSheet("QLabel { color : white; }");
    if (!not_correct)
    {
        QString region = ui->region_b->text();
        QString city = ui->city_b->text();
        QString street = ui->street_b->text();
        QString index = ui->index_b->text();
        QString number = ui->number_b->text();
        QString name = ui->name_b->text();

        Branch *B = new Branch(name, index, region, city, street, number);
        if (Br->get_count() != 1)
        {
            branch->get_prev()->set_next(B);
            branch->get_next()->set_prev(B);
            B->set_next(branch->get_next());
            B->set_prev(branch->get_prev());
        }
        else
        {
            B->set_next(B);
            B->set_prev(B);
        }
        if (Br->get_head() == branch)
            Br->set_head(B);
        if (Br->get_tail() == branch)
            Br->set_tail(B);
        tab3(B, item);
        B->set_count(branch->get_count());
        B->set_head(branch->get_head());
        B->set_tail(branch->get_tail());
        People *P = B->get_head(), *C = branch->get_head();
        for (int i = 0; i < B->get_count(); i++)
        {
            P->set_next(C->get_next());
            P->set_prev(C->get_prev());
            P = P->get_next();
            C = C->get_next();
        }
        for (int i = 0; i < n; i++)
        {
            QString name1 = ui->table1->item(i, 7)->text();
            if (name1 == branch->get_name())
                ui->table1->setItem(i, 7, new QTableWidgetItem(B->get_name()));
        }
        int l = 0;
        Branch *b = Br->get_tail();
        while (b != B)
        {
            l++;
            b = b->get_prev();
        }
        ui->branch_p->setItemText(l, name);
        ui->branch_s->setItemText(l, name);
        ui->branch_w->setItemText(l, name);
        ui->choice_b->setItemText(l, name);
        ui->add_br->setDisabled(0);
        ui->edit_br->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(8);
        clear_b();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect data entered");
    }
}

void MainWindow::on_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_about_triggered()
{
    QMessageBox::about(this, "About", "The program is designed to record data on students and university employees\nDeveloper: Bykov Vladislav\nEmail: vlad.bykov2004@mail.ru");
}

void MainWindow::on_manual_triggered()
{
    QMessageBox::about(this, "Manual", "Information retrieval system 'University'\n");
}

void MainWindow::on_Create_triggered()
{
    if (!str.isNull())
    {
        for (int i = n - 1; i >= 0; i--)
        {
            ui->table1->removeRow(i);
        }
        ui->tip->setDisabled(1);
        n = 0;
        for (int i = s - 1; i >= 0; i--)
        {
            ui->table3->removeRow(i);
            ui->branch_p->removeItem(i);
            ui->branch_s->removeItem(i);
            ui->branch_w->removeItem(i);
            ui->choice_b->removeItem(i);
            Br->del(i);
        }
        s = 0;
        ui->Return->setDisabled(1);
        ui->edit_p->setDisabled(1);
        ui->add_p->setDisabled(0);
        ui->edit_s->setDisabled(1);
        ui->add_s->setDisabled(0);
        ui->edit_w->setDisabled(1);
        ui->add_w->setDisabled(0);
        ui->edit_br->setDisabled(1);
        ui->add_b->setDisabled(0);
        ui->Search->setDisabled(1);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->stackedWidget_3->setCurrentIndex(0);
    }
    else
        QMessageBox::warning(this, "Error", "Current file not saved");
}

void MainWindow::on_Open_triggered()
{
    on_Create_triggered();
    QString P, p;
    int row1 = 0, column = 0, row = 0;
    QString selFilter = "All files (*.*)";
    str = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(),
                                       "Text files (*.txt);;All files (*.*)", &selFilter);
    QFile file(str);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            P = in.readLine();
            if (P[0] != ' ')
            {
                ui->table3->insertRow(ui->table3->rowCount());
                for (int i = 0; i < P.size(); i++)
                {
                    if ((P[i] == '|'))
                    {
                        ui->table3->setItem(row1, column, new QTableWidgetItem(p));
                        column++;
                        p.clear();
                    }
                    else
                        p += P[i];
                }
                ui->table3->setItem(row1, column, new QTableWidgetItem(p));
                QString index = ui->table3->item(row1, 1)->text();
                QString name = ui->table3->item(row1, 0)->text();
                QString street = ui->table3->item(row1, 4)->text();
                QString city = ui->table3->item(row1, 3)->text();
                QString region = ui->table3->item(row1, 2)->text();
                QString number = ui->table3->item(row1, 5)->text();
                Br->add_branch(name, index, region, city, street, number);
                ui->branch_p->addItem(name);
                ui->branch_s->addItem(name);
                ui->branch_w->addItem(name);
                ui->choice_b->addItem(name);
                s++;
                column = 0;
                row1++;
                p.clear();
            }
            else
            {
                ui->table1->insertRow(ui->table1->rowCount());
                for (int i = 1; i < P.size(); i++)
                {
                    if ((P[i] == '|'))
                    {
                        ui->table1->setItem(row, column, new QTableWidgetItem(p));
                        if (column == 6)
                        {
                            ui->table1->setItem(row, 7, new QTableWidgetItem(Br->get_head()->get_name()));
                            column++;
                        }
                        column++;
                        if (column > 7)
                            i = P.size();
                        p.clear();
                    }
                    else
                        p += P[i];
                }
                ui->table1->setItem(row, column, new QTableWidgetItem(p));
                p.clear();
                QString type = ui->table1->item(row, 1)->text();
                if (type == "Professor")
                {
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString subject = ui->table1->item(row, 4)->text();
                    QString salary = ui->table1->item(row, 5)->text();
                    QString department = ui->table1->item(row, 6)->text();
                    Branch *B = Br->get_tail();
                    address = ui->table1->item(row, 7)->text();
                    int l = 0;
                    while (l != Br->get_count())
                    {
                        if (B->get_name() == address)
                            break;
                        l++;
                        B = B->get_prev();
                    }
                    B->add_professor(id, full_name, age, department, subject, salary);
                    n++;
                }
                else if (type == "Student")
                {
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString group = ui->table1->item(row, 4)->text();
                    QString department = ui->table1->item(row, 6)->text();
                    Branch *B = Br->get_tail();
                    address = ui->table1->item(row, 7)->text();
                    int l = 0;
                    while (l != Br->get_count())
                    {
                        if (B->get_name() == address)
                            break;
                        l++;
                        B = B->get_prev();
                    }
                    B->add_student(id, full_name, age, department, group);
                    n++;
                }
                else if (type == "Worker")
                {
                    QString id = ui->table1->item(row, 0)->text();
                    QString full_name = ui->table1->item(row, 2)->text();
                    QString age = ui->table1->item(row, 3)->text();
                    QString position = ui->table1->item(row, 4)->text();
                    QString salary = ui->table1->item(row, 5)->text();
                    Branch *B = Br->get_tail();
                    address = ui->table1->item(row, 7)->text();
                    int l = 0;
                    while (l != Br->get_count())
                    {
                        if (B->get_name() == address)
                            break;
                        l++;
                        B = B->get_prev();
                    }
                    B->add_worker(id, full_name, age, position, salary);
                    n++;
                }
                row++;
                column = 0;
            }
        }
        file.close();
        ui->Search->setDisabled(0);
        if (Br->get_count() != 0)
            ui->tip->setDisabled(0);
    }
}

void MainWindow::on_Save_triggered()
{
    if (!str.isNull())
    {
        QFile file(str);
        file.open(QFile::WriteOnly | QFile::Truncate);
        file.close();
        write_to_file(str);
    }
    else
        QMessageBox::warning(this, "Error", "No current file");
}

void MainWindow::on_Save_As_triggered()
{
    QString selFilter = "All files (*.*)";
    QString str1 = QFileDialog::getSaveFileName(this, "Save file", QDir::currentPath(),
                                                "Text files (*.txt);;All files (*.*)", &selFilter);
    write_to_file(str1);
    str = str1;
}
