#include "expressionevaluator.h"
#include "muParser.h"

ExpressionEvaluator::ExpressionEvaluator(const std::string& expression) : expression_(expression) {}

double ExpressionEvaluator::operator()(double x) const {
    mu::Parser parser;
    parser.SetExpr(expression_);
    parser.DefineVar("x", &x);

    return parser.Eval();
}
