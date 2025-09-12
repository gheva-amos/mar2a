#include "parser/parser.h"
#include "ast/ast_program.h"
#include "ast/ast_function.h"
#include "ast/ast_identifier.h"
#include "ast/ast_return.h"
#include "ast/ast_expression.h"
#include "ast/ast_factor.h"
#include "ast/ast_type.h"
#include "lexer/token.h"

namespace mar2a
{

Parser::Parser(std::unique_ptr<Lexer> lexer, std::ostream& out) :
  lexer_{std::move(lexer)}, ast_{std::make_unique<ASTProgram>()},  out_{out}, index_{0}, left_{nullptr}
{
  nodes_.push_back(ast_.get());
}

bool Parser::parse()
{
  index_ = 0;
  return parse_program(index_);
}

void Parser::pretty_print()
{
  ast_->pretty_print(out_, "");
}

std::unique_ptr<IRNode> Parser::get_ir()
{
  return ast_->visit();
}

bool Parser::parse_program(size_t index)
{
  if (parse_function(index))
  {
    return true;
  }
  return false;
}

bool Parser::expect(Token* token, Token::Type type, const std::string& msg)
{
  if (token->type() != type)
  {
    out_ << "Expected " << msg << " Found: " << token->value() << std::endl;
    return false;
  }
  return true;
}

bool Parser::parse_function(size_t index)
{
  std::unique_ptr<ASTFunction> func{std::make_unique<ASTFunction>()};
  auto fp{func.get()};
  nodes_.back()->add_child(std::move(func));
  nodes_.push_back(fp);
  Token* token{lexer_->at(index)};
  if (!expect_type(token))
  {
    return false;
  }
  nodes_.back()->add_child(std::make_unique<ASTType>(token->value(), token->type()));
  index += 1;
  token = lexer_->at(index);
  if (!expect(token, Token::Type::identifier, "a function name (identifier)"))
  {
    return false;
  }
  nodes_.back()->add_child(std::make_unique<ASTIdentifier>(token->value()));
  index += 1;
  token = lexer_->at(index);
  if (!expect_open_paren(token))
  {
    return false;
  }
  index += 1;
  token = lexer_->at(index);
  if (!expect_type(token))
  {
    return false;
  }
  index += 1;
  token = lexer_->at(index);
  if (!expect_close_paren(token))
  {
    return false;
  }
  index += 1;
  token = lexer_->at(index);
  if (!expect_open_brace(token))
  {
    return false;
  }

  index += 1;
  if (!parse_statement(index))
  {
    return false;
  }
  index = index_; // it has changed by parse_statement
  index += 1;
  token = lexer_->at(index);
  if (!expect_close_brace(token))
  {
    return false;
  }
  nodes_.pop_back();
  index_ = index;
  return true;
}

bool Parser::parse_statement(size_t index)
{
  if (!parse_return(index))
  {
    return false;
  }
  return true;
}

bool Parser::parse_return(size_t index)
{
  std::unique_ptr<ASTReturn> ret{std::make_unique<ASTReturn>()};
  auto rp{ret.get()};
  nodes_.back()->add_child(std::move(ret));
  nodes_.push_back(rp);
  Token* token{lexer_->at(index)};
  if (!expect(token, Token::Type::keyword, "return"))
  {
    return false;
  }
  if (token->value() != "return")
  {
    out_ << "Expected return found " << token->value() << std::endl;
    return false;
  }
  index += 1;
  if (!parse_expression(index))
  {
    return false;
  }
  left_ = nullptr;

  index = index_;
  token = lexer_->at(index);
  if (!expect_semicolon(token))
  {
    return false;
  }
  nodes_.pop_back();
  index_ = index;
  return true;
}

bool Parser::parse_expression(size_t index, Token::Precedence min_prec)
{
  static std::vector<Token::Type> binary_ops(
      {Token::Type::plus, Token::Type::negate, Token::Type::times,
        Token::Type::divide, Token::Type::remainder}
      );
  // Take care of the left side
  if (!parse_factor(index))
  {
    return false;
  }
  index = index_;
  while (std::find(binary_ops.begin(), binary_ops.end(), lexer_->at(index)->type()) != binary_ops.end()
        && lexer_->at(index)->precedence() >= min_prec)
  {
    std::unique_ptr<ASTExpression> exp{ASTExpression::factory(lexer_->at(index)->value(), lexer_->at(index)->type())};
    if (left_ != nullptr)
    {
      exp->add_child(std::move(left_));
    }
    left_ = std::move(exp);
    index += 1;
    if (!parse_expression(index, Token::next_precedence(min_prec)))
    {
      return false;
    }
    index = index_;
  }
  // TODO
  if (left_ != nullptr)
  {
    auto rp{left_.get()};
    nodes_.back()->add_child(std::move(left_));
    nodes_.push_back(rp);
  }
  return true;
}

bool Parser::parse_factor(size_t index)
{
  // constant int, parenthesis then expresion then parenthesis, unary then expression
  static std::vector<Token::Type> unariy_types(
    {Token::Type::tilde, Token::Type::decrement, Token::Type::negate}
    );
  bool ret{false};
  if (lexer_->at(index)->type() == Token::Type::open_paren)
  {
    ret = parse_expression(index + 1);
    index = index_;
    expect_close_paren(lexer_->at(index));
    out_ << __LINE__ << left_ <<std::endl;
    index += 1;
  }
  else if (std::find(unariy_types.begin(), unariy_types.end(), lexer_->at(index)->type()) != unariy_types.end())
  {
    ASTFactor::Type type{ASTFactor::Type::tilde};
    if (lexer_->at(index)->type() == Token::Type::negate)
    {
      type = ASTFactor::Type::minus;
    }
    else if (lexer_->at(index)->type() == Token::Type::decrement)
    {
      type = ASTFactor::Type::decrement;
    }
    std::unique_ptr<ASTFactor> exp{std::make_unique<ASTFactor>(lexer_->at(index)->value(), type)};
    if (left_ == nullptr)
    {
      left_ = std::move(exp);
    }
    else
    {
      left_->add_child(std::move(exp));
    }
    index += 1;
    ret = parse_factor(index);
    index = index_;
  }
  else // constant int
  {
    std::unique_ptr<ASTFactor> exp{std::make_unique<ASTFactor>(lexer_->at(index)->value(), ASTFactor::Type::const_int)};
    if (left_ == nullptr)
    {
      left_ = std::move(exp);
    }
    else
    {
      left_->add_child(std::move(exp));
    }
    index += 1;
    ret = true;
  }
  index_ = index;
  return ret;
}

bool Parser::expect_open_paren(Token* token)
{
  return expect(token, Token::Type::open_paren, "open parenthesis");
}

bool Parser::expect_close_paren(Token* token)
{
  return expect(token, Token::Type::close_paren, "close parenthesis");
}

bool Parser::expect_open_brace(Token* token)
{
  return expect(token, Token::Type::open_brace, "open brace");
}

bool Parser::expect_close_brace(Token* token)
{
  return expect(token, Token::Type::close_brace, "close brace");
}

bool Parser::expect_semicolon(Token* token)
{
  return expect(token, Token::Type::semicolon, "semicolon");
}

bool Parser::expect_type(Token* token)
{
  return expect(token, {Token::Type::voidt, Token::Type::intt}, "a type");
}

bool Parser::expect(Token* token, std::vector<Token::Type> types, const std::string& msg)
{
  if (std::find(types.begin(), types.end(), token->type()) == types.end())
  {
    out_ << "Expected " << msg << " Found " << token->value() << std::endl;
    return false;
  }
  return true;
}

} // namespace
