#ifndef GPIOTOGGLEACTION_H
#define GPIOTOGGLEACTION_H

#include "abstractaction.h"
#include <QTimer>

class GpioToggleAction : public QObject, public AbstractAction
{
    Q_OBJECT
private:
    quint8 gpioLine;
    quint8 duration;
    QTimer timer;
public:
    GpioToggleAction(quint8 gpioNumber, quint8 actionDurationSeconds);

    // AbstractAction interface
public:
    virtual void doAction() override;

public slots:
    void setLine();
    void resetLine();
};

#endif // GPIOTOGGLEACTION_H
