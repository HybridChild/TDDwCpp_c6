#include "Portfolio.h"

using namespace std;

Portfolio::Portfolio() {
}

bool Portfolio::IsEmpty() const { 
   return holdings_.size() == 0; 
}

void Portfolio::Purchase(const string& symbol, unsigned int shareCount) {
   if (shareCount == 0) throw InvalidPurchaseException();
   holdings_[symbol] = shareCount + ShareCount(symbol);
}

void Portfolio::Sell(const string& symbol, unsigned int shareCount) {
   if (shareCount > ShareCount(symbol)) throw InvalidSellException();
   holdings_[symbol] = ShareCount(symbol) - shareCount;
}

unsigned int Portfolio::ShareCount(const string& symbol) const {
   auto it = holdings_.find(symbol);
   
   if (it == holdings_.end()) return 0;
   else return it->second;
}
