#include "Portfolio.h"
#include <numeric>

using namespace std;
using namespace boost::gregorian;

const date Portfolio::FIXED_PURCHASE_DATE(date(2014, Jan, 1));

Portfolio::Portfolio() {
}

bool Portfolio::IsEmpty() const { 
   return purchaseRecords_.size() == 0; 
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
   AddPurchaseRecord(symbol, shareChange, transactionDate);
}

unsigned int Portfolio::ShareCount(const string& symbol) const {
   auto records = Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
   
   return accumulate(records.begin(), records.end(), 0,
      [] (int total, PurchaseRecord record) {
         return total + record.ShareCount;
      });
}

void Portfolio::ThrowIfShareCountIsZero(int shareCount) const {
   if (shareCount == 0) throw ShareCountCannotBeZeroException();
}

void Portfolio::AddPurchaseRecord(const std::string& symbol, int shareCount, const boost::gregorian::date& transactionDate) {
   if (!ContainsSymbol(symbol)) {
      InitializePurchaseRecords(symbol);
   }

   Add(symbol, {shareCount, transactionDate});
}

void Portfolio::InitializePurchaseRecords(const std::string& symbol) {
   purchaseRecords_[symbol] = vector<PurchaseRecord>();
}

void Portfolio::Add(const std::string& symbol, PurchaseRecord&& record) {
   purchaseRecords_[symbol].push_back(record);
}

bool Portfolio::ContainsSymbol(const std::string& symbol) const {
   return purchaseRecords_.find(symbol) != purchaseRecords_.end();
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
}
