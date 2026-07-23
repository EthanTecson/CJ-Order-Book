// Orderbook.cpp
#include "Orderbook.h"

bool Orderbook::CanMatch(Side side, Price price) const
{
    return false; // stub
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