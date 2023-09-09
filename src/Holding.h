#pragma once

#include <numeric>
#include "Portfolio.h"
#include "PurchaseRecord.h"

class Holding {
   public:
   void Add(PurchaseRecord& record) {
      purchaseRecords_.push_back(record);
   }

   std::vector<PurchaseRecord> Purchases() const {
      return purchaseRecords_;
   }

   unsigned int ShareCount() const {
      return accumulate(purchaseRecords_.begin(), purchaseRecords_.end(), 0,
         [] (int total, PurchaseRecord record) {
            return total + record.ShareCount;
         });
   }

   private:
   std::vector<PurchaseRecord> purchaseRecords_;
};