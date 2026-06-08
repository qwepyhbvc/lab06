#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"

class TransactionTest : public ::testing::Test {
protected:
    Account* from;
    Account* to;
    
    void SetUp() override {
        from = new Account("FROM123", 500.0);
        to = new Account("TO456", 100.0);
    }
    
    void TearDown() override {
        delete from;
        delete to;
    }
};

TEST_F(TransactionTest, ExecuteValidTransaction) {
    Transaction tx(from, to, 200.0);
    EXPECT_TRUE(tx.execute());
    EXPECT_EQ(from->getBalance(), 300.0);
    EXPECT_EQ(to->getBalance(), 300.0);
    EXPECT_TRUE(tx.isCompleted());
    EXPECT_EQ(tx.getAmount(), 200.0);
}

TEST_F(TransactionTest, ExecuteTransactionInsufficientFunds) {
    Transaction tx(from, to, 600.0);
    EXPECT_FALSE(tx.execute());
    EXPECT_EQ(from->getBalance(), 500.0);
    EXPECT_EQ(to->getBalance(), 100.0);
    EXPECT_FALSE(tx.isCompleted());
}

TEST_F(TransactionTest, ExecuteTransactionZeroAmount) {
    Transaction tx(from, to, 0.0);
    EXPECT_FALSE(tx.execute());
    EXPECT_EQ(from->getBalance(), 500.0);
    EXPECT_EQ(to->getBalance(), 100.0);
}

TEST_F(TransactionTest, ExecuteTransactionNegativeAmount) {
    Transaction tx(from, to, -100.0);
    EXPECT_FALSE(tx.execute());
    EXPECT_EQ(from->getBalance(), 500.0);
    EXPECT_EQ(to->getBalance(), 100.0);
}

TEST_F(TransactionTest, ExecuteTransactionAlreadyCompleted) {
    Transaction tx(from, to, 200.0);
    EXPECT_TRUE(tx.execute());
    EXPECT_FALSE(tx.execute());
    EXPECT_EQ(from->getBalance(), 300.0);
    EXPECT_EQ(to->getBalance(), 300.0);
}

TEST_F(TransactionTest, RevertCompletedTransaction) {
    Transaction tx(from, to, 200.0);
    EXPECT_TRUE(tx.execute());
    tx.revert();
    EXPECT_EQ(from->getBalance(), 500.0);
    EXPECT_EQ(to->getBalance(), 100.0);
    EXPECT_FALSE(tx.isCompleted());
}

TEST_F(TransactionTest, RevertNotCompletedTransaction) {
    Transaction tx(from, to, 600.0);
    EXPECT_FALSE(tx.execute());
    tx.revert();
    EXPECT_EQ(from->getBalance(), 500.0);
    EXPECT_EQ(to->getBalance(), 100.0);
}

TEST_F(TransactionTest, GetTimestamp) {
    Transaction tx(from, to, 200.0);
    std::string timestamp = tx.getTimestamp();
    EXPECT_FALSE(timestamp.empty());
    EXPECT_EQ(timestamp.length(), 19);
}
