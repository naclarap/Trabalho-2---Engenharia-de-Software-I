#pragma once
#include "IGestaoComandasService.h"
#include "Gestaocomandasservice_global.h"
class GESTAOCOMANDASSERVICE_EXPORT GestaoComandasServiceFactory {
public: static IGestaoComandasService* create();
};
