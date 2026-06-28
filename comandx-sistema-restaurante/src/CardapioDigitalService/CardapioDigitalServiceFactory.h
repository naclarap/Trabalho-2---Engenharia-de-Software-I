#pragma once

#include "CardapioDigitalService_global.h"
#include "ICardapioDigitalService.h"

class CARDAPIODIGITALSERVICE_EXPORT CardapioDigitalServiceFactory {
public:
    static ICardapioDigitalService* create();
};
