#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;

MorphDSLSemantics::MorphDSLSemantics(MorphDSLParser* p) {
    imeIzhodneSlike = "";
    imageCounter = 1;
    tempCnt = 0;

    parser = p;
}