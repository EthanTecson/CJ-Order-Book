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
    Trades trades;

    while (true) 
    {
        if (bids_.empty() || asks_.empty())
        {
            break;
        }

        auto [bidsPrice, bids] = *bids_.begin();
        auto [asksPrice, asks] = *asks_.begin();

        if (bidsPrice < asksPrice)
            break;
        
        while (bids.size() > 0 && asks.size() > 0)
        {
            auto& bid = bids.front(); 
            auto& ask = asks.front(); 

            Quantity quantity = std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());

            bid->Fill(quantity);
            ask->Fill(quantity);

            trades.push_back(Trade{
                TradeInfo{bid->GetOrderId(), bid->GetPrice(), quantity},
                TradeInfo{ask->GetOrderId(), ask->GetPrice(), quantity},
            });

            if (bid->IsFilled())
            {
                bids.pop_front();
                orders_.erase(bid->GetOrderId());
            }

            if (ask->IsFilled())
            {
                asks.pop_front();
                orders_.erase(ask->GetOrderId());
            }
        }
        if (bids.empty())
            bids_.erase(bidsPrice);
        if (asks.empty())
            asks_.erase(asksPrice);
    }

    if (!bids_.empty())
    {
        auto& [_, bids] = *bids_.begin();
        auto& order = bids.front();
        if (order->GetOrderType() == OrderType::FillAndKill)
            CancelOrder(order->GetOrderId());
    }

    if (!asks_.empty())
    {
        auto& [_, asks] = *asks_.begin();
        auto& order = asks.front();
        if (order->GetOrderType() == OrderType::FillAndKill)
            CancelOrder(order->GetOrderId());
    }

    return trades;
}

// Trades Orderbook::AddOrder(OrderPointer order)
// {
//     return {}; // stub
// }

void Orderbook::CancelOrder(OrderId orderId)
{
    if (!orders_.contains(orderId))
        return;

    const auto [order, iterator] = orders_.at(orderId);
    orders_.erase(orderId);

    if (order->GetSide() == Side::Buy)
    {
        auto price = order->GetPrice();
        auto& orders = bids_.at(price);
        orders.erase(iterator);
        if (orders.empty())
            bids_.erase(price);
    }
    else
    {
        auto price = order->GetPrice();
        auto& orders = asks_.at(price);
        orders.erase(iterator);
        if (orders.empty())
            asks_.erase(price);
    }

    return;
}

// Trades Orderbook::MatchOrder(OrderModify order)
// {
//     return {}; // stub
// }

// OrderbookLevelInfos Orderbook::GetOrderInfos() const
// {
//     return {{}, {}}; // stub
// }