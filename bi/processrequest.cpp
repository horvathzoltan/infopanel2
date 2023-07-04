#include "cechelper.h"
#include "processrequest.h"
#include "helpers/logger.h"

bool ProcessRequest::Process(const QString &request, const QChar& sep)
{
    bool retVal = false;
    bool valid = !request.isEmpty();

    if(valid){    //master:started
        int ix = request.indexOf(sep);
        if(ix>0){
            QString cmd = request.left(ix);
            QString value = request.mid(ix+1);

            if(cmd=="master"){
                retVal = MasterCmd(value);
            } else if(cmd=="pow"){
                retVal = PowCmd(value);
            }
        } else{
            if(request=="getlist"){
                retVal = GetListRequest();
            }
        }

    }
    return retVal;
}


bool ProcessRequest::MasterCmd(const QString &value)
{
    zInfo("MasterCmd: "+value);
    return true;
}

bool ProcessRequest::PowCmd(const QString &value)
{
    bool parse_ok, retVal = false;
    int v = value.toInt(&parse_ok);
    if(parse_ok){
        retVal = CECHelper::SetPowerState(1, v);
    }
    zInfo("PowCmd: "+value + ' '+ (retVal?"ok":"failed"));
    return true;
}

bool ProcessRequest::GetListRequest()
{
    zInfo("GetListRequest");
    return true;
}

