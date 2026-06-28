#pragma once
#include "IGestaoSalaoService.h"
#include "GestaoSalaoServiceImpl.h"
#include "gestaosalaoservice_global.h"

class GESTAOSALAOSERVICE_EXPORT GestaoSalaoServiceFactory {
public: static IGestaoSalaoService* create() { return GestaoSalaoServiceImpl::getInstance(); }
};
