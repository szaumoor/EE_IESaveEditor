#ifndef EE_SAVEEDITOR_QT_IO_H
#define EE_SAVEEDITOR_QT_IO_H

#include <qdir.h>
#include <QString>

inline QString extend_path( const std::initializer_list<QString> steps)
{
    QString path;
    for ( const auto& step : steps )
    {
        path.append( step )
            .append( QDir::separator() );
    }
    path.erase(path.cend()-1);

    return path;
}

#endif //EE_SAVEEDITOR_QT_IO_H
