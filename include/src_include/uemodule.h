#ifndef UEMODULE_H
#define UEMODULE_H

#include <QWidget>
#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

class UEModule : public QWidget
{
    Q_OBJECT
public:
    explicit UEModule(QWidget *parent = nullptr);

    ~UEModule();

public:

    void GetPathAndWidgetContainer(const QString& path,QWidget* widget_container);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);

    void hideEvent(QHideEvent *event);

    void showEvent(QShowEvent *event);

private:
    void InitWidget();

    void TimerShowUe();

    void KillProcessByName(const QString& process_name);
signals:

    void SignalsUeComplete();

private slots:
    void SlotUeComplete();

private:
    QProcess* process_;
    HWND ue_window_;
};

#endif // UEMODULE_H
