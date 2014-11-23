// c++ simple.cpp -o simple
#include <iostream>
#include <vector> 
using namespace std;

int use_a_prompt = 0;
const char *VERSION = "0.0.1b";
const char *PROGRAM = "jtSimple";
vector<string> exit_strings;

void simple_exit(int exit_code) {
  printf("\nbye bye!\n");
  exit(exit_code);
}

void welcome(void) {
  cout << "Welcome to " << PROGRAM << " " << VERSION << "\n";
  cout << "Type 'exit' or 'quit' (not including the single-quotes) to Exit";
}

string eval(string expression) {
  return expression;
}

void prompt(string &line) {
  //printf("\n%s:%d> ", VERSION, global_line_counter);
  cout << "\n" << VERSION << "> ";
  getline(cin, line);
}

void readline_from_file(string &line) {
  // for now:
  cout << "readline not implemented\n";
  prompt(line);
}

int found(vector<string> search_list, string key) {
  for (int n = 0; n < search_list.size(); ++n) {
    if (search_list[n] == key) {
      //cout << "[ " << n << " => " << search_list[n] << " ]" << endl;
      //debug("n is %d\n", n);
      return n;
    }
  }
  return -1;
}

int found_an_exit_in(string input_token) {
  if (found( exit_strings, input_token) >= 0) {
    return 1;
  } else {
    return 0;
  }
}

class SimpleToken {
  public:
    string to_s() const { return text + " " + token_class; }
    friend std::ostream& operator<< (std::ostream& o, SimpleToken const& st);
    SimpleToken(string parsed_line, string _token_class) {
      text = parsed_line;
      token_class = _token_class;
    }
    //SimpleToken(string line);

    // separate regex ?!
    string text, token_class;
};
vector<SimpleToken> keyword_tokens;
//SimpleToken *if_token = new SimpleToken("if", "Condition");
//SimpleToken *else_token = new SimpleToken("else", "Else");

SimpleToken *find(string key, vector<SimpleToken> search_tokens, SimpleToken *default_token) {
  SimpleToken *result;
  vector<string> search_text;
  for (int n = 0; n < search_tokens.size(); ++n) {
    search_text.push_back(search_tokens[n].text);
  }

  int lookup_id = found( search_text, key);
  if (lookup_id < 0) {
    result = default_token;
  } else {
    result = &search_tokens[lookup_id];
  }
  //cout << "result: " << *result << endl;
  return result;
}

//SimpleToken::SimpleToken(string line) {
SimpleToken* parse(string line) {
  SimpleToken *default_token = new SimpleToken(line, "Object"); // call the "base" constructor
  //SimpleToken(parsed_line, find(line, keyword_tokens, "Object")); // call the "base" constructor
  return find(line, keyword_tokens, default_token);
}

class SimpleExpression {
  public:
    friend std::ostream& operator<< (std::ostream& o, SimpleExpression const& st);
    string to_s() const {
      string output;
      for( int pos = 0; pos < tokens.size(); ++pos ) {
        output += tokens.at(pos).to_s();
      }
      return output;
    }
    void add_token(SimpleToken st) { tokens.push_back(st); }
    SimpleExpression(SimpleToken st) { add_token(st); }
  private:
    vector<SimpleToken> tokens;
};

std::ostream& operator<< (std::ostream& o, SimpleExpression const& se) {
  return o << se.to_s();
}

//std::ostream& operator<< (std::ostream& o, SimpleToken const& st) {
std::ostream& operator<< (std::ostream& o, SimpleToken const& st) {
  return o << st.to_s();
}

void setup_stop_tokens(void) {
  exit_strings.push_back("exit");
  exit_strings.push_back("quit");
}

void setup_keyword_tokens(void) {
  SimpleToken *if_token = new SimpleToken("if", "Condition");
  SimpleToken *else_token = new SimpleToken("else", "Else");
  keyword_tokens.push_back(*if_token);
  keyword_tokens.push_back(*else_token);
}

int main(int ac, char** av) {
  --ac, ++av; // skip program name
  if (ac > 0) {
    //yyin = fopen(av[0], "r");
    use_a_prompt = 0;
  } else {
    //yyin = stdin;
    use_a_prompt = 1;
  }

  setup_stop_tokens();
  setup_keyword_tokens();

  string line;
  int exit_value = 0;
  welcome();

  do {
    if (use_a_prompt) {
      prompt(line);
    } else {
      readline_from_file(line);
    }

    exit_value = found_an_exit_in(line);
    if ( exit_value ) {
      simple_exit(exit_value);
    } else {
      //Do we need a class to combine parsed lines into full "expressions"
      SimpleToken *parsed_line = parse(line);
      //cout << "=> " << parsed_line->to_s()  << ";" << endl;
      cout << "=> " << *parsed_line  << ";" << endl;
    }

  } while(true);

  return 0;
}
