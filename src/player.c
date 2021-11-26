#include "player.h"

Player get_other_player(Player player) {
    switch (player) {
        case CROSS:
            return NAUGHT;
        case NAUGHT:
            return CROSS;
        default:
            return NO_PLAYER;
    }
}
