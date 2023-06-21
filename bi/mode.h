#ifndef MODE_H
#define MODE_H

#include <QObject>

class Mode  {

private:
    bool _isMaster;
public:
    Mode(bool isMaster);

    bool IsMater(){return _isMaster;}
    virtual void Start(){};
};

#endif // MODE_H
