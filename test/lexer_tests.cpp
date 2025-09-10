#include <gtest/gtest.h>
#include "lexer/lexer.h"

using namespace mar2a;

TEST(WhiteSpaceOnly, LexerTests)
{
  Lexer lexer{"      \n\n    "};
  EXPECT_FALSE(lexer.tokenize());
}

TEST(NoWhiteSpace, LexerTests)
{
  Lexer lexer{"main(void){}"};
  EXPECT_TRUE(lexer.tokenize());
  EXPECT_EQ(lexer.at(0)->value(), "main");
  EXPECT_EQ(lexer.at(1)->value(), "(");
  EXPECT_EQ(lexer.at(2)->value(), "void");
  EXPECT_EQ(lexer.at(3)->value(), ")");
  EXPECT_EQ(lexer.at(4)->value(), "{");
  EXPECT_EQ(lexer.at(5)->value(), "}");
}

TEST(WhiteSpace, LexerTests)
{
  Lexer lexer{" main ( void ) { } "};
  EXPECT_TRUE(lexer.tokenize());
  EXPECT_EQ(lexer.at(0)->value(), "main");
  EXPECT_EQ(lexer.at(1)->value(), "(");
  EXPECT_EQ(lexer.at(2)->value(), "void");
  EXPECT_EQ(lexer.at(3)->value(), ")");
  EXPECT_EQ(lexer.at(4)->value(), "{");
  EXPECT_EQ(lexer.at(5)->value(), "}");
}

TEST(StringTokening, LexerTests)
{
  Lexer lexer{R"END("abcd efg hi jk \"lm nop" main)END"};
  EXPECT_TRUE(lexer.tokenize());
  EXPECT_EQ(lexer.at(0)->value(), R"END(abcd efg hi jk \"lm nop)END");
  EXPECT_EQ(lexer.at(1)->value(), "main");
}

TEST(NumberTokening, LexerTests)
{
  Lexer lexer{"1234.56"};
  EXPECT_TRUE(lexer.tokenize());
  EXPECT_EQ(lexer.at(0)->value(), "1234.56");
}

TEST(DecrementAndMinus, LexerTests)
{
  Lexer lexer{"-234 --"};
  EXPECT_TRUE(lexer.tokenize());
  EXPECT_EQ(lexer.at(0)->type(), Token::Type::minus);
  EXPECT_EQ(lexer.at(1)->type(), Token::Type::number);
  EXPECT_EQ(lexer.at(2)->type(), Token::Type::decrement);
}

