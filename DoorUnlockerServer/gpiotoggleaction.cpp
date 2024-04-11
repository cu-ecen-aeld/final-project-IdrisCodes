#include "gpiotoggleaction.h"
#include <QDebug>
#include <gpiod.h>

GpioToggleAction::GpioToggleAction(quint8 gpioNumber, quint8 actionDurationSeconds)
    :gpioLine(gpioNumber), duration(actionDurationSeconds)
{
    timer.setSingleShot(true);
    timer.setInterval(duration * 1000);

    chip = gpiod_chip_open_by_name(chipname);
    relay_line = gpiod_chip_get_line(chip, gpioNumber);
    gpiod_line_request_output(relay_line, "DoorUnlocker", 0);

}

GpioToggleAction::~GpioToggleAction()
{
    gpiod_line_release(relay_line);
    gpiod_chip_close(chip);
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
