// Orderbook.cpp
#include "Orderbook.h"

bool Orderbook::CanMatch(Side side, Price price) const
{
    if (side == Side::Buy)
    {
        if (asks_.empty())
            return false;
        
        auto& [ask, _] = *asks_.begin();
        return (price >= ask);
    }
    else
    {
        if (bids_.empty())
            return false;
        
        auto& [bid, _] = *bids_.begin();
        return (price <= bid);
    }
}

Trades Orderbook::MatchOrders()
{
    return {}; // stub
}

Trades Orderbook::AddOrder(OrderPointer order)
{
    return {}; // stub
}

void Orderbook::CancelOrder(OrderId orderId)
{
    return; // stub
}

Trades Orderbook::MatchOrder(OrderModify order)
{
    return {}; // stub
}

OrderbookLevelInfos Orderbook::GetOrderInfos() const
{
    return {{}, {}}; // stub
}