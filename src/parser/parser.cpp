#include "parser/parser.h"
#include "ast/ast_program.h"
#include "ast/ast_function.h"
#include "ast/ast_identifier.h"
#include "ast/ast_return.h"
#include "ast/ast_expression.h"
#include "lexer/token.h"

namespace mar2a
{

Parser::Parser(std::unique_ptr<Lexer> lexer, std::ostream& out) :
  lexer_{std::move(lexer)}, ast_{std::make_unique<ASTProgram>()}, out_{out}, index_{0}
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
  if (!expect(token, Token::Type::keyword, "a keyword"))
  {
    return false;
  }
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
  if (!expect(token, Token::Type::keyword, "a type"))
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
  token = lexer_->at(index);
  if (!expect(token, {Token::Type::string, Token::Type::number}, "An expression"))
  {
    return false;
  }
  out_ << token->value() << std::endl;
  nodes_.back()->add_child(std::make_unique<ASTExpression>(token->value()));

  index += 1;
  token = lexer_->at(index);
  if (!expect_semicolon(token))
  {
    return false;
  }
  nodes_.pop_back();
  index_ = index;
  return true;
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
