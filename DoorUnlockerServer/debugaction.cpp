#include "debugaction.h"
#include <QDebug>

DebugAction::DebugAction() {}

DebugAction DebugAction::instance;

void DebugAction::doAction()
{
    qDebug()<< "Action Performed";
}

DebugAction* DebugAction::getInstance()
{
    return &DebugAction::instance;
}
