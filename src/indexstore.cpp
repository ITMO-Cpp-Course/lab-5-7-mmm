#include "indexstore.hpp"
#include "updatetransaction.hpp"

UpdateTransaction IndexStore::begin_update()
{
    return UpdateTransaction(*this); //вернет объект транзакции 
}