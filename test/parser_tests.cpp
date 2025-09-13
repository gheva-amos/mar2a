#include <gtest/gtest.h>
#include "parser/parser.h"
#include "lexer/lexer.h"
#include <string>
#include <iostream>

TEST(ParseSimpleProgram, ParserTests)
{
  std::string program{R"END(
int main(void)
{
  return 2;
}
)END"};
  std::unique_ptr<mar2a::Lexer> lexer{std::make_unique<mar2a::Lexer>(program)};
  EXPECT_TRUE(lexer->tokenize());
  mar2a::Parser parser{std::move(lexer), std::cout};

  EXPECT_TRUE(parser.parse());
  parser.pretty_print();
}

TEST(ParseUnaryExpression, ParserTests)
{
  std::string program{R"END(
int main(void)
{
  return ~-~-~2;
}
)END"};
  std::unique_ptr<mar2a::Lexer> lexer{std::make_unique<mar2a::Lexer>(program)};
  EXPECT_TRUE(lexer->tokenize());
  mar2a::Parser parser{std::move(lexer), std::cout};

  EXPECT_TRUE(parser.parse());
  parser.pretty_print();
}

TEST(BinaryOps, ParserTests)
{
  std::string program{R"END(
int main(void)
{
  return (2 * 3 + 1) - 3;
}
)END"};
  std::unique_ptr<mar2a::Lexer> lexer{std::make_unique<mar2a::Lexer>(program)};
  EXPECT_TRUE(lexer->tokenize());
  mar2a::Parser parser{std::move(lexer), std::cout};
  EXPECT_TRUE(parser.parse());
  parser.pretty_print();
}

TEST(ParenthesisUnary, ParserTests)
{
  std::string program{R"END(
int main(void)
{
  return -(3);
}
)END"};
  std::unique_ptr<mar2a::Lexer> lexer{std::make_unique<mar2a::Lexer>(program)};
  EXPECT_TRUE(lexer->tokenize());
  mar2a::Parser parser{std::move(lexer), std::cout};
  EXPECT_TRUE(parser.parse());
  parser.pretty_print();
}

TEST(UnaryComplexExpression, ParserTests)
{
  //return  - ( (3 * 2 + 3) / - 6 % 5);
  std::string program{R"END(
int main(void)
{
  return    3 * - 4 ;
}
)END"};
  std::unique_ptr<mar2a::Lexer> lexer{std::make_unique<mar2a::Lexer>(program)};
  EXPECT_TRUE(lexer->tokenize());
  mar2a::Parser parser{std::move(lexer), std::cout};
  EXPECT_TRUE(parser.parse());
  parser.pretty_print();
}
