#ifndef LOGINDLL_GLOBAL_H
#define LOGINDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGINDLL_LIBRARY)
#define LOGINDLL_EXPORT Q_DECL_EXPORT
#else
#define LOGINDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGINDLL_GLOBAL_H
