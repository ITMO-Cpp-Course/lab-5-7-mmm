#include "indexstore.hpp"

UpdateTransaction IndexStore::begin_update()
{
    return UpdateTransaction(*this);
}