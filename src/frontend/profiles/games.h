#ifndef GAMES_H
#define GAMES_H

#include <QString>

#include "../../backend/utils/aliases.h"
#include "../../backend/utils/errors.h"

namespace Game {

    enum class Type : i8 { Bgee=0, Bg2ee=1, Iwdee=2 };

    inline std::expected<Type, QString> parse( const i8 game )
    {
        if ( game < 0 || game > 2 )
            return std::unexpected("Valid values for Game are 0-2 (bgee, bg2ee, iwdee)");
        return static_cast<Type>(game);
    }

    inline i8 to_integer( const Type game ) { return static_cast<i8>( game ); }
}
#endif // GAMES_H
