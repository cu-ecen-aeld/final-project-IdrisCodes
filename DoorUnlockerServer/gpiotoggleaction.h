#ifndef GPIOTOGGLEACTION_H
#define GPIOTOGGLEACTION_H

#include "abstractaction.h"
#include <QTimer>
#include <gpiod.h>
class GpioToggleAction : public QObject, public AbstractAction
{
    Q_OBJECT
private:
    quint8 gpioLine;
    quint8 duration;
    QTimer timer;

    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *relay_line;

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
