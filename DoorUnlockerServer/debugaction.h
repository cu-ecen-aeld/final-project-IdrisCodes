#ifndef DEBUGACTION_H
#define DEBUGACTION_H

#include "abstractaction.h"

class DebugAction : public AbstractAction
{
    static DebugAction instance;
private:
    DebugAction();

    // AbstractAction interface
public:
    virtual void doAction() override;
    static DebugAction* getInstance();
};

#endif // DEBUGACTION_H
