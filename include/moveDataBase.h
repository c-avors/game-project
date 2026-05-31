#include "moves.h"
#include <map>

class MoveDatabase {
private:
    std::map<MoveName, Move> registry;

public:
    MoveDatabase();

    MoveInstance createInstance(MoveName name) const;
};