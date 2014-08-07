/* definitions */

%{
  #include <stdio.h>
  #include <stdlib.h>

  #define PROGRAM "jtRuby"
  #define VERSION "v.0.0.1a"
  int num_lines = 1, num_chars = 1; // hopefully this will help with error messages!
  int use_a_prompt = 0;
  void prompt(void);
  void ruby_exit(int);
%}

%option noyywrap

DIGIT [0-9]
FLOAT [0-9]+"."[0-9]+
/* QUIT exit|quit */

%% /* rules */

exit|quit {
  printf("\nbye bye!\n");
  ruby_exit(0);
}

{FLOAT}+  {
  printf("=> %f\n", atof(yytext));
  if (use_a_prompt) {
    prompt();
  }
}

{DIGIT}+  {
  printf("=> %d\n", atoi(yytext));
  if (use_a_prompt) {
    prompt();
  }
}

username  {
  printf("=> user: %s\n", getlogin());
  if (use_a_prompt) {
    prompt();
  }
}

\n num_chars++, num_lines++;

. {
  num_chars++;
  printf("[line: %d; char: %d]: unrecognized input: %s\n", num_lines, num_chars, yytext);
  if (use_a_prompt) {
    prompt();
  }
}

%% /* user code */

void welcome(void) {
  printf("Welcome to %s %s\n", PROGRAM, VERSION);
}

void prompt(void) {
  printf("\n%s:%d> ", VERSION, num_lines);
}

void ruby_exit(int exit_code) {
  printf("%d characters across %d lines\n", num_chars, num_lines);
  exit(exit_code);
}

int main(int ac, char** av) {
  --ac, ++av; // skip program name

  if (ac > 0) {
    yyin = fopen(av[0], "r");
  } else {
    use_a_prompt = 1;
    yyin = stdin;
  }

  welcome();
  if (use_a_prompt) {
    prompt();
  }
  yylex();
  ruby_exit(0);
}
