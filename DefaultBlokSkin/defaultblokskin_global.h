#ifndef DEFAULTBLOKSKIN_GLOBAL_H
#define DEFAULTBLOKSKIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEFAULTBLOKSKIN_LIBRARY)
#  define DEFAULTBLOKSKINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DEFAULTBLOKSKINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DEFAULTBLOKSKIN_GLOBAL_H