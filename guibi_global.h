#ifndef GUIBI_GLOBAL_H
#define GUIBI_GLOBAL_H

#include <QtCore/qglobal.h>


#if defined(GUIBI_LIBRARY)
#  define GUIBISHARED_EXPORT Q_DECL_EXPORT
#else
#  define GUIBISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GUIBI_GLOBAL_H
