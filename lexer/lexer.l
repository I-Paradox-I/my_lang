%{
#include <cctype>
#include <cstdio>
#include <string>
#define YYEOF 0
int yylex();
int main() {
  do {
  } while (yylex() != YYEOF);
}
std::string yyloc = "<stdin>";
int yyrow = 1, yycolumn = 1, yycolpre = 1, yynewline = 1, yyspace = 0;
#define YY_USER_ACTION                                                         \
  do {                                                                         \
    yycolumn += yyleng;                                                        \
  } while (0);
%}
%option noyywrap
%%
#.* {
  std::string s(yytext);
  auto l = s.find("\""), r = s.rfind("\"");
  yyloc = s.substr(l + 1, r - l - 1);
  for (int i = 0; i < s.size(); ++i)
    if (std::isdigit(s[i])) {
      for (yyrow = 0; i < s.size() && std::isdigit(s[i]); ++i)
        yyrow = yyrow * 10 + s[i] - '0';
      --yyrow;
      break;
    }
}
\n {
  ++yyrow;
  yycolpre = yycolumn;
  yycolumn = 1;
  yynewline = 1;
}
[ ]+ {
  yyspace = 1;
}
[\f\r\t\v] {}
void {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "void '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
const {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "const '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
char {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "char '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
long {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "long '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
int {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "int '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
float {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "float '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
double {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "double '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
if {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "if '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
else {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "else '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
do {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "do '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
while {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "while '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
break {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "break '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
continue {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "continue '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
return {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "return '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\( {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "l_paren '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\) {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "r_paren '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\{ {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "l_brace '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\} {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "r_brace '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\[ {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "l_square '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\] {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "r_square '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
, {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "comma '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
; {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "semi '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
= {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "equal '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
! {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "exclaim '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"+" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "plus '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
- {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "minus '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"*" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "star '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"/" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "slash '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
% {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "percent '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"<" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "less '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
">" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "greater '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"<=" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "lessequal '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
">=" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "greaterequal '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
== {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "equalequal '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
!= {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "exclaimequal '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"&&" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "ampamp '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"||" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "pipepipe '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
"..." {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "ellipsis '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
[0-9]+ {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "numeric_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
0[bB][01]+ {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "numeric_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
0[xX][0-9a-fA-F]+ {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "numeric_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
([0-9]*\.[0-9]+|[0-9]+(\.[0-9]*)?)([eE][-+]?[0-9]+)? {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "numeric_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
0[xX]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+(\.[0-9a-fA-F]*)?)([pP][-+]?[0-9]+)? {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "numeric_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
[a-zA-Z_][a-zA-Z_0-9]* {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "identifier '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\"[^"\\]*((\\[onrtvabf'"\\?])*[^"\\]*)*\" {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "string_literal '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
\'([^'\\]|(\\[onrtvabf'"\\?]))\' {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "char_constant '%s'\t%sLoc=<%s:%d:%d>\n", yytext,
               s.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
<<EOF>> {
  std::fprintf(yyout, "eof ''\t\tLoc=<%s:%d:%d>\n", yyloc.c_str(), yyrow - 1,
               yycolpre - yyleng);
  return YYEOF;
}
. {
  std::string s = "";
  if(yynewline) s.append("[StartOfLine] ");
  if(yyspace) s.append("[LeadingSpace] ");
  std::fprintf(yyout, "unknown '%s'\t%sLoc=<%s:%d:%d>\n", yytext, s.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  yynewline = 0;
  yyspace = 0;
  return ~YYEOF;
}
%%
