#pragma once
#include <QtCore/qglobal.h>

#if defined(CONTROLEACESSOSERVICE_LIBRARY)
#  define CONTROLEACESSOSERVICE_EXPORT Q_DECL_EXPORT
#else
#  define CONTROLEACESSOSERVICE_EXPORT Q_DECL_IMPORT
#endif
