#include "model.hpp"

namespace s21 {

bool Model::Validation(std::string input) {  // OK – 1, FAIL – 0
  bool flag = 1;
  int open_br = 0, close_br = 0, mult = 0;
  int dot = 0, num = 0;
  std::string::iterator format = input.begin();

  while (*format != '\0' && flag) {
    if (strchr("(", *format)) open_br++;
    if (strchr(")", *format)) close_br++;
    if (close_br > open_br || strchr("I", *format)) {
      flag = 0;
      break;
    }
    if (!strchr(")(=", *format) && strchr(ops, *format)) {
      if (mult) {
        flag = 0;
        break;
      }
      mult = 1;
    } else {
      mult = 0;
    }
    if (strchr(nums, *format)) {
      num = 1;
    } else if (strchr(".", *format)) {
      if (dot && num) {
        flag = 0;
        break;
      } else if (!dot && !num) {
        flag = 0;
        break;
      }
      dot = 1;
    } else {
      dot = 0, num = 0;
    }
    format++;
  }
  if (open_br != close_br) flag = 0;
  return flag;
}

void Model::WithoutExp(std::string *input) {
  if (input->find('e') != std::string::npos) {
    int ef = 0;
    bool sign;
    std::string str_e;
    for (auto c : *input) {
      if (c == 'e') ef = 1;

      if (ef == 0) {
        str_e += c;
      } else if (ef == 1) {
        str_e += "*10^(";
        ef = 2;
      } else if (ef == 2) {
        if (!strchr(ops, c) && !strchr(others, c)) {
          str_e += c;
        } else {
          if (!sign && (strchr("+", c) || strchr("-", c))) {
            sign = 1;
            str_e += c;
          } else {
            str_e += ')';
            str_e += c;
            sign = 0;
            ef = 0;
          }
        }
      }
    }
    *input = str_e;
  }
}

void Model::ParcingInput(std::string input) {
  WithoutExp(&input);

  if (!Validation(input)) throw std::invalid_argument("Invalid string");

  std::string::iterator format = input.begin();
  int unar_m = 0, open_br = 0;
  int start = 0;
  while (*format != '\0') {
    if (strchr(nums, *format)) {
      double tmp = *format - '0';
      int drob = 0, tmp_dr = 0;
      format++;
      if (strchr(".", *format)) {
        drob = 1;
        format++;
      }
      while (strchr(nums, *format)) {
        if (drob) tmp_dr++;
        tmp = 10.0 * tmp + (*format - '0');
        format++;
        if (strchr(".", *format)) {
          drob = 1;
          format++;
        }
      }
      if (drob) {
        while (tmp_dr) {
          tmp = tmp / 10;
          tmp_dr--;
        }
      }
      if (unar_m) tmp *= -1;
      values.push(tmp);
      open_br = 0;
      start++;
    }
    if (strchr(others, *format)) {
      PushOperator(*format);
    }
    if (strchr(ops, *format)) {
      if (*format == '-' && (!start || open_br)) {
        unar_m = 1;
      } else if (*format == '+' && (!start || open_br)) {
        unar_m = 0;
      } else {
        unar_m = 0;
        PushOperator(*format);
        if (*format == '(') open_br = 1;
      }
    }
    start++;
    format++;
  }
}

void Model::PushOperator(char format) {
  int flag = FlagPriority(format);
  double tmp = CountWithPriority(format);

  if (!tmp && !flag && format != ')') {
    operators.push(format);
  } else if (!operators.empty() && operators.top() == '=') {
    operators.pop();
  } else {
    while (flag) {
      values.push(tmp);

      if (!operators.empty()) {
        char oper = operators.top();
        if (oper == '(' && format == ')') {
          break;
        }
      }

      flag = FlagPriority(format);
      tmp = CountWithPriority(format);
      if (!tmp && !flag) break;
    }
    if (format != ')') {
      operators.push(format);
    } else if (!operators.empty()) {
      operators.pop();
    }
  }
}

double Model::CountWithPriority(char format) {
  if (PriorityComparison(format) && !operators.empty() &&
      operators.top() != '(') {
    char oper = cpop(&operators);
    double top = vpop(&values);
    switch (oper) {
      case '*':
        return vpop(&values) * top;
      case '/':
        return vpop(&values) / top;
      case 'm':
        return fmod(vpop(&values), top);
      case '+':
        return vpop(&values) + top;
      case '-':
        return vpop(&values) - top;
      case '^':
        return pow(vpop(&values), top);
      case 'c':
        return cos(top);
      case 's':
        return sin(top);
      case 't':
        return tan(top);
      case 'k':
        return acos(top);
      case 'z':
        return asin(top);
      case 'd':
        return atan(top);
      case 'q':
        return sqrt(top);
      case 'n':
        return log(top);
      case 'g':
        return log10(top);
    }
  }
  return 0.0;
}

bool Model::FlagPriority(char format) {
  if (PriorityComparison(format) && !operators.empty()) {
    switch (operators.top()) {
      case '^':
      case '*':
      case '/':
      case 'm':
      case '+':
      case '-':
      case ')':
      case '=':
      case 'c':
      case 's':
      case 't':
      case 'k':
      case 'z':
      case 'd':
      case 'q':
      case 'n':
      case 'g':
        return 1;
      default:
        return 0;
    }
  } else {
    return 0;
  }
}

bool Model::PriorityComparison(char format) {
  bool flag = 0;
  if (!operators.empty()) {
    double oper = operators.top();
    if (oper == '(' && format == ')') {
      flag = 1;
    } else if (HowPriority(oper) >= HowPriority(format)) {
      flag = 1;
    }
  }
  return flag;
}

int Model::HowPriority(char format) {
  switch (format) {
    case '^':
      return 3;
    case '*':
    case '/':
    case 'm':
      return 2;
    case '+':
    case '-':
    case ')':
    case '=':
      return 1;
    case 'c':
    case 's':
    case 't':
    case 'k':
    case 'z':
    case 'd':
    case 'q':
    case 'n':
    case 'g':
      return 4;
    case '(':
      return 10;
  }

  return 0;
}

}  // namespace s21
