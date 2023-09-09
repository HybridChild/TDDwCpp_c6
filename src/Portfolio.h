#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <unordered_map>
#include <vector>

#include "boost/date_time/gregorian/gregorian_types.hpp"

class ShareCountCannotBeZeroException:  public std::exception {};
class InsufficientSharesException:      public std::exception {};

struct PurchaseRecord {
   PurchaseRecord(int shareCount, const boost::gregorian::date& date)
      : ShareCount(shareCount), Date(date)
   {}

   int ShareCount;
   boost::gregorian::date Date;
};

class Portfolio {
public:
   static const boost::gregorian::date FIXED_PURCHASE_DATE;

   Portfolio();
   bool IsEmpty() const;

   void Purchase(
      const std::string& symbol,
      unsigned int shares,
      const boost::gregorian::date& transactionDate = FIXED_PURCHASE_DATE);
   
   void Sell(
      const std::string& symbol,
      unsigned int shares,
      const boost::gregorian::date& transactionDate);

   unsigned int ShareCount(const std::string& symbol) const;

   std::vector<PurchaseRecord> Purchases(const std::string& symbol) const;

private:
   void Transact(
      const std::string& symbol,
      int shareChange,
      const boost::gregorian::date& transactionDate);
   
   void ThrowIfShareCountIsZero(int shareCount) const;
   void UpdateShareCount(const std::string& symbol, int shareChange);
   void AddPurchaseRecord(const std::string& symbol, int shareCount, const boost::gregorian::date& transactionDate);
   std::unordered_map<std::string, unsigned int> holdings_;
   std::unordered_map<std::string, std::vector<PurchaseRecord>> purchaseRecords_;
};

#endif
