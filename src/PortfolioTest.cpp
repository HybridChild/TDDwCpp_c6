#include "gmock/gmock.h"
#include "Portfolio.h"

using namespace ::testing;
using namespace boost::gregorian;

class APortfolio: public Test {
public:
   static const std::string IBM;
   static const std::string AAPL;
   static const std::string SAMSUNG;
   Portfolio portfolio_;
   static const date ArbitraryDate;

   void Purchase(
         const std::string& symbol,
         unsigned int shareCount,
         const date& transactionDate = APortfolio::ArbitraryDate) {
      portfolio_.Purchase(symbol, shareCount, transactionDate);
   }
};
const std::string APortfolio::IBM     = "IBM";
const std::string APortfolio::AAPL    = "AAPL";
const std::string APortfolio::SAMSUNG = "SAMSUNG";
const date APortfolio::ArbitraryDate  = date(2014, Jan, 1);

TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(true));
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   Purchase(IBM, 1);
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(false));
}

TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.ShareCount(AAPL), Eq(0u));
}

TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol) {
   Purchase(IBM, 666);
   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(666u));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(Purchase(IBM, 0), InvalidPurchaseException);
}

TEST_F(APortfolio, AnswersShareCountForAppropriateSymbol) {
   Purchase(IBM, 5);
   Purchase(AAPL, 7);
   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u));
   ASSERT_THAT(portfolio_.ShareCount(AAPL), Eq(7u));
}

TEST_F(APortfolio, ShareCountReflectsAccumulatedPurchasesOfSameSymbol) {
   Purchase(IBM, 1);
   Purchase(IBM, 2);
   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(3u));
}

TEST_F(APortfolio, ReducesShareCountOfSymbolOnSell) {
   Purchase(IBM, 5);
   portfolio_.Sell(IBM, 2);
   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(3u));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
   portfolio_.Purchase(IBM, 3);
   ASSERT_THROW(portfolio_.Sell(IBM, 4), InvalidSellException);
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
   date dateOfPurchase(2014, Mar, 17);

   Purchase(SAMSUNG, 5, dateOfPurchase);
   auto purchases = portfolio_.Purchases(SAMSUNG);
   auto purchase = purchases[0];

   ASSERT_THAT(purchase.ShareCount, Eq(5u));
   ASSERT_THAT(purchase.Date, Eq(dateOfPurchase));
}
