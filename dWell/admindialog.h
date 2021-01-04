/**
 * @file admindialog.h
 * @brief Заголовчный файл класса adminDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

// Объявляем класс ubook, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Это увеличивает скорость сборки проекта за
// счёт уменьшения количества обрабатываемых заголовочных файлов.
class ubook;

// Объявляем класс Ui::adminDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class adminDialog;
}

/**
 * @brief Класс диалога панели администрирования.
 * Для функционирования необходима коллекция пользователей.
 * *m_ubook указывает на эту коллекцию.
 */
class adminDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    explicit adminDialog(QWidget *parent);
    /// Деструктор класса adminDialog
    ~adminDialog();

private slots:
    /// Слот, обрабатывающий нажатие на кнопку "Добавить"(пользователя)
    void on_addButton_clicked();
    /// Слот, обрабатывающий нажатие на кнопку "Удалить"(пользователя)
    void on_removeButton_clicked();
    /// Слот, выполняющий обновление (генерацию) таблицы пользователей
    void updateTable();
    /**
     * @brief Обработчик двойного нажатия на строку пользователя в таблице
     * @param index Индекс пользователя в таблице.
     */
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_logoutButton_clicked();


private:
    /// указатель на контейнер пользователей
    ubook *m_ubook;
    /**
     * @brief Указатель на сгенерированный интерфейс.
     *
     * Указатель на объект UI-класса, сгенерированного на основе UI-файла
     * adminDialog.ui.
     *
     * Через этот указатель можно обратиться к элементам главного окна,
     * созданного в Qt Designer.
     */
    Ui::adminDialog *ui;
};

#endif // ADMINDIALOG_H
