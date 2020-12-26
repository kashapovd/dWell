#include "admindialog.h"
#include "ui_admindialog.h"

#include "usereditdialog.h"
#include "tools.h"

#include <QMessageBox>

#define UNAME_COLUMN 0
#define HTYPE_COLUMN 1

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);
    m_ubook = ubook::getUbook();

    connect(m_ubook, &ubook::dataChanged, this, &adminDialog::updateTable);
    updateTable();
    ui->tableWidget->verticalHeader()->setVisible(false); // отключаем подпись строк таблицы
    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this]
    {
        // отключаем кнопку "удалить", если нет выделенных пользователей
        ui->removeButton->setDisabled(!ui->tableWidget->selectionModel()
                                                         ->hasSelection());
    });
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_addButton_clicked()
{
    userEditDialog userAddtDlg(this);
    user *u = new user;
    userAddtDlg.setUser(u);
    userAddtDlg.setWindowTitle("Создание пользователя");
    if (userAddtDlg.exec() != userEditDialog::Accepted)
        return;
    m_ubook->insert(*u);
}

void adminDialog::on_removeButton_clicked()
{
    int idx = ui->tableWidget->currentIndex().row();
    QMessageBox::StandardButtons ret = QMessageBox::question(this, "Удаление пользователя", QString("Вы действительно хотите "
                                                                 "удалить пользователя <b><i>%1</i></b>?").arg((*m_ubook)[idx].name()));
    if (ret == QMessageBox::No) return;
    m_ubook->erase(idx);
}

void adminDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    userEditDialog userEditDlg(this);
    user *u = const_cast<user *>(&(*m_ubook)[index.row()]);
    userEditDlg.setUserForEdit(u);
    userEditDlg.setWindowTitle("Редактирование пользователя");
    if (userEditDlg.exec() != userEditDialog::Accepted) return;
    emit m_ubook->dataChanged();
}

void adminDialog::updateTable()
{
    ui->tableWidget->setRowCount(0);
    for (uint i = 0; i < m_ubook->size(); i++)
    {
        auto user = (*m_ubook)[i];
        QTableWidgetItem *username = new QTableWidgetItem(user.name());
        QTableWidgetItem *usertype = new QTableWidgetItem(tools::userTypeToStr(user.type()));
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, UNAME_COLUMN, username);
        ui->tableWidget->setItem(i, HTYPE_COLUMN, usertype);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

void adminDialog::on_logoutButton_clicked()
{
    this->close();
}
