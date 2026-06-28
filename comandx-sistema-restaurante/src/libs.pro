TEMPLATE = subdirs

SUBDIRS += \
    core \
    ControleAcessoService \
    GestaoSalaoService \
    CardapioDigitalService \
    GestaoComandasService

ControleAcessoService.depends = core
GestaoSalaoService.depends = core
CardapioDigitalService.depends = core
GestaoComandasService.depends = core GestaoSalaoService CardapioDigitalService