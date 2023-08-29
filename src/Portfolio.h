#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <unordered_map>

class InvalidPurchaseException:  public std::exception {};
class InvalidSellException:      public std::exception {};

class Portfolio {
public:
   Portfolio();
   bool IsEmpty() const;
   void Purchase(const std::string& symbol, unsigned int shares);
   void Sell(const std::string& symbol, unsigned int shares);
   unsigned int Shares(const std::string& symbol) const;

private:
   std::unordered_map<std::string, unsigned int> shares_;
};

#endif
