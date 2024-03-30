#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include <string>

class ExpressionEvaluator {
public:
    ExpressionEvaluator(const std::string& expression);
    double operator()(double x) const;

private:
    std::string expression_;
};

#endif // EXPRESSIONEVALUATOR_H
