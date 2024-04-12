#include "gpiotoggleaction.h"
#include <QDebug>


GpioToggleAction::GpioToggleAction(quint8 gpioNumber, quint8 actionDurationSeconds)
    :gpioLine(gpioNumber), duration(actionDurationSeconds)
{
    timer.setSingleShot(true);
    timer.setInterval(duration * 1000);

    chip = new gpiod::chip(chipname);
    auto request = chip->prepare_request();
    request.set_consumer("DoorUnlocker");

    /* Relay line setup ughhhh*/
    gpiod::line_settings line_cfg;
    line_cfg.set_direction(gpiod::line::direction::OUTPUT);
    line_cfg.set_output_value(gpiod::line::value::INACTIVE);
    request.add_line_settings(gpioNumber, line_cfg);
    relay_line = new gpiod::line_request(request.do_request());
}

GpioToggleAction::~GpioToggleAction()
{
    relay_line->release();
    delete chip;

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
    relay_line->set_value(gpioLine, gpiod::line::value::ACTIVE);
}

void GpioToggleAction::resetLine()
{
    qDebug() << "Resetting GPIO line";
    relay_line->set_value(gpioLine, gpiod::line::value::INACTIVE);
}
