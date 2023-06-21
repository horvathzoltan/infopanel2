#ifndef SLAVEMODE_H
#define SLAVEMODE_H

#include <QObject>
#include "form3.h"
#include "frame2.h"
#include "mode.h"

class SlaveMode : public Mode
{

private:
    Form3* _w1 = nullptr;
    Frame2* _w2 = nullptr;
public:
    SlaveMode();
    ~SlaveMode();

    void Init();
};

#endif // SLAVEMODE_H
