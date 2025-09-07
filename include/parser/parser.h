#ifndef MAR2A_PARSER_H__
#define MAR2A_PARSER_H__

#include <ostream>
#include <vector>
#include "ast/ast_node.h"
#include "lexer/lexer.h"

namespace mar2a
{

class Parser
{
public:
  Parser(std::unique_ptr<Lexer> lexer, std::ostream& out);
  bool parse();
  void pretty_print();
private:
  bool expect(Token* token, Token::Type type, const std::string& msg);
  bool expect(Token* token, std::vector<Token::Type> types, const std::string& msg);
  bool parse_program(size_t index);
  bool parse_function(size_t index);
  bool parse_statement(size_t index);
  bool parse_return(size_t index);
  std::unique_ptr<Lexer> lexer_;
  std::unique_ptr<ASTNode> ast_;
  std::ostream& out_;
  std::vector<ASTNode*> nodes_;
  size_t index_;

  bool expect_open_paren(Token* token);
  bool expect_close_paren(Token* token);
  bool expect_open_brace(Token* token);
  bool expect_close_brace(Token* token);
  bool expect_semicolon(Token* token);
};

} // namespace

#endif // MAR2A_PARSER_H__
