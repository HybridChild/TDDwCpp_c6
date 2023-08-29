#include "Portfolio.h"

using namespace std;

Portfolio::Portfolio()
{
}

bool Portfolio::IsEmpty() const { 
   return shares_.size() == 0; 
}

void Portfolio::Purchase(const string& symbol, unsigned int shares) {
   if (shares == 0) {
      throw InvalidPurchaseException();
   }

   shares_.insert(make_pair(symbol, shares));
}

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = shares_.find(symbol);
   
   if (it == shares_.end()) {
      return 0;
   } else {
      return it->second;
   }
}
