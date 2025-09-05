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
