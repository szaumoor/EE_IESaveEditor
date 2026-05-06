#ifndef GAMES_H
#define GAMES_H

#include <QString>

#include "../../backend/utils/aliases.h"
#include "../../backend/utils/errors.h"

namespace game {

    enum class Type : i8 { None=-1, Bgee=0, Bg2ee=1, Iwdee=2 };

    inline std::expected<Type, QString> parse( const i8 game )
    {
        if ( game < -1 || game > 2 )
            return std::unexpected("Valid values for Game are -1 to -2 (none, bgee, bg2ee, iwdee)");
        return static_cast<Type>(game);
    }

    inline i8 to_integer( const Type game ) { return static_cast<i8>( game ); }
}
#endif // GAMES_H
