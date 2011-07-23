#include "ContextALG.hh"
#include "bo/ContextBO.hh"

ContextALG::ContextALG()
: pContextBo_m(0)
{
}

ContextALG::~ContextALG()
{
}

ContextBO * ContextALG::getpContextBo() const
{
    return pContextBo_m;
}

void ContextALG::setpContextBo(ContextBO * pContextBo_p)
{
    pContextBo_m = pContextBo_p;
}
