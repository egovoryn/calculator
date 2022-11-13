#include "model.hpp"

#include "gtest/gtest.h"

TEST(Mod, Test_1) {
  char format[100] = "(103-3)m(5+4)=";
  double standart = 1.000000;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Sin, Test_2) {
  char format[100] = "42+4-11*s(3-1)=";
  double standart = 35.997728304917501;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(ModLn, Test_3) {
  char format[100] = "5m3*21-n(10)=";
  double standart = 39.697414907005957;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(SqrtSin, Test_4) {
  char format[100] = "q(121)*s(9-5)=";
  double standart = -8.324827448387211;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Tan, Test_5) {
  char format[100] = "12*(t(3))/13+13=";
  double standart = 12.868418575623744;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(SqrtCosLog, Test_6) {
  char format[100] = "q(256)+c(7)*g(4)=";
  double standart = 16.453894384712061;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Brackets, Test_7) {
  char format[100] = "13/(-2)/(-1)*(-2+12)/3=";
  double standart = 21.666666666666668;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Arc, Test_8) {
  char format[100] = "z(0.5)+k(0.5)+d(0.5)+2^2=";
  double standart = 6.034443935795703;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Error, Test_9) {
  char format[100] = ")asin(0.5)+acos(0.5)+(atan(0.5)+2^2=";
  s21::Model res;
  EXPECT_THROW(res.ParcingInput(format), std::exception);
}

TEST(Error, test_10) {
  char format[100] = "5+3.5*sin(10)++sin(3)=";
  s21::Model res;
  EXPECT_THROW(res.ParcingInput(format), std::exception);
}

TEST(Error, Test_11) {
  char format[100] = "5+3...5*sin(10)+sin(3)=";
  s21::Model res;
  EXPECT_THROW(res.ParcingInput(format), std::exception);
}

TEST(Hard, Test_12) {
  char format[100] =
      "(s(-2)*(3+(((4*(5+6))/2)*5))*7)-(1582*200)+(6523532*2.5)=";
  double standart = 15991710.745735380798578;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Mod, Test_13) {
  char format[100] = "-5*(+5)m15.412321=";
  double standart = -9.587678999999998;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

TEST(Error, Test_14) {
  char format[100] = "+*-5*(+5)m15.412321=";
  s21::Model res;
  EXPECT_THROW(res.ParcingInput(format), std::exception);
}

TEST(Error, Test_15) {
  char format[100] = "I5*(+5)mod15.412321=";
  s21::Model res;
  EXPECT_THROW(res.ParcingInput(format), std::exception);
}

TEST(Exp, Test_16) {
  char format[100] = "2.3e+5*5.8e+12-15e-10=";
  double standart = 1333999999999999744.0;
  s21::Model res;
  res.ParcingInput(format);
  EXPECT_EQ(res.GetValues().top(), standart);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
