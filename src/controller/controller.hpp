#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "../model/model.hpp"

namespace s21 {

class Controller {
 public:
  double CalculateExpression(std::string input) {
    Model model;
    model.ParcingInput(input);
    return model.GetValues().top();
  }

  bool ValidateExpression(std::string input) {
    Model model;
    return model.Validation(input);
  }
};

}  // namespace s21

#endif  //  SRC_CONTROLLER_H_
