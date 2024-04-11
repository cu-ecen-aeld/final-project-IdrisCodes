#include "gpiotoggleaction.h"
#include <QDebug>

GpioToggleAction::GpioToggleAction(quint8 gpioNumber, quint8 actionDurationSeconds)
    :gpioLine(gpioNumber), duration(actionDurationSeconds)
{
    timer.setSingleShot(true);
    timer.setInterval(duration * 1000);
}


void GpioToggleAction::doAction()
{
    qDebug() << "Toggling GPIO";
    setLine();
    timer.singleShot(duration * 1000, this, &GpioToggleAction::resetLine);
}

void GpioToggleAction::setLine()
{
    qDebug() << "Setting GPIO line";
}

void GpioToggleAction::resetLine()
{
    qDebug() << "Resetting GPIO line";
}
