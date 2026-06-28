#pragma once
#include <QtCore/qglobal.h>
#if defined(GESTAOSALAOSERVICE_LIBRARY)
#  define GESTAOSALAOSERVICE_EXPORT Q_DECL_EXPORT
#else
#  define GESTAOSALAOSERVICE_EXPORT Q_DECL_IMPORT
#endif
