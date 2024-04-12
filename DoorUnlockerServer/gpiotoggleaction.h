#ifndef GPIOTOGGLEACTION_H
#define GPIOTOGGLEACTION_H

#include "abstractaction.h"
#include <QTimer>
#include <gpiod.hpp>

class GpioToggleAction : public QObject, public AbstractAction
{
    Q_OBJECT
private:
    quint8 gpioLine;
    quint8 duration;
    QTimer timer;

    const char *chipname = "/dev/gpiochip0";
    gpiod::chip *chip;
    gpiod::line_request* relay_line = nullptr;

public:
    GpioToggleAction(quint8 gpioNumber, quint8 actionDurationSeconds);
    virtual ~GpioToggleAction();
    // AbstractAction interface
public:
    virtual void doAction() override;

public slots:
    void setLine();
    void resetLine();
};

#endif // GPIOTOGGLEACTION_H
