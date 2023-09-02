#include "Portfolio.h"

using namespace std;
using namespace boost::gregorian;

const date Portfolio::FIXED_PURCHASE_DATE(date(2014, Jan, 1));

Portfolio::Portfolio() {
}

bool Portfolio::IsEmpty() const { 
   return holdings_.size() == 0; 
}

void Portfolio::Purchase(const string& symbol, unsigned int shareCount, const date& transactionDate) {
   Transact(symbol, shareCount, transactionDate);
}

void Portfolio::Sell(const string& symbol, unsigned int shareCount, const date& transactionDate) {
   if (shareCount > ShareCount(symbol)) throw InsufficientSharesException();
   Transact(symbol, -shareCount, transactionDate);
}

void Portfolio::Transact(const string& symbol, int shareChange, const date& transactionDate)
{
   ThrowIfShareCountIsZero(shareChange);
   UpdateShareCount(symbol, shareChange);
   AddPurchaseRecord(shareChange, transactionDate);
}

unsigned int Portfolio::ShareCount(const string& symbol) const {
   auto it = holdings_.find(symbol);
   
   if (it == holdings_.end()) return 0;
   else return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return purchases_;
}

void Portfolio::ThrowIfShareCountIsZero(int shareCount) const {
   if (shareCount == 0) throw ShareCountCannotBeZeroException();
}

void Portfolio::UpdateShareCount(const std::string& symbol, int shareChange) {
   holdings_[symbol] = ShareCount(symbol) + shareChange;
}

void Portfolio::AddPurchaseRecord(int shareCount, const boost::gregorian::date& transactionDate) {
   purchases_.push_back(PurchaseRecord(shareCount, transactionDate));
}
