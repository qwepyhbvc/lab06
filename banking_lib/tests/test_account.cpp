#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, ConstructorWithInitialBalance) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_EQ(acc.getBalance(), 100.0);
    EXPECT_EQ(acc.getIban(), "DE89370400440532013000");
}

TEST(AccountTest, ConstructorWithZeroBalance) {
    Account acc("DE89370400440532013000");
    EXPECT_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, DepositPositiveAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_TRUE(acc.deposit(50.0));
    EXPECT_EQ(acc.getBalance(), 150.0);
}

TEST(AccountTest, DepositZeroAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_FALSE(acc.deposit(0.0));
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DepositNegativeAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_FALSE(acc.deposit(-50.0));
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, WithdrawValidAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_TRUE(acc.withdraw(30.0));
    EXPECT_EQ(acc.getBalance(), 70.0);
}

TEST(AccountTest, WithdrawExactBalance) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_TRUE(acc.withdraw(100.0));
    EXPECT_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, WithdrawInsufficientFunds) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_FALSE(acc.withdraw(150.0));
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, WithdrawNegativeAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_FALSE(acc.withdraw(-10.0));
    EXPECT_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, WithdrawZeroAmount) {
    Account acc("DE89370400440532013000", 100.0);
    EXPECT_FALSE(acc.withdraw(0.0));
    EXPECT_EQ(acc.getBalance(), 100.0);
}
