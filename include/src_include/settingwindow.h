#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindow(QWidget *parent = nullptr);

    QPushButton* SetBasicButton();

    QPushButton* SetEnvironmentButton();

    QPushButton* SetMoreButton();

    QPushButton* SetRetunButton();

    QPushButton* SetStartButton();

signals:
    void ShowSettingWindow();
};

#endif // SETTINGWINDOW_H
