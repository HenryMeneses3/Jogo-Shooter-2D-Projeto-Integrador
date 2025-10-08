#include "objetos.h"

Expressao expressoes[] =
{
    {"2 + 2 = 4", true},
    {"log(10) = 2", false},
    {"5 + 7 = 12", true},
    {"250 / 2 = 225", false},
    {"180 x 3 = 540", true},
    {"6 x 6 = 24", false},
    {"cos(60) = 0,5", true},
    {"cossec(x) = 1/cos(x)", false},
    {"tan(45) = 1", true},
    {"sen(60) = 0,5", false},
    {"sec(x) = 1/cos(x)", true},
    {"9 x 9 = 72", false},
    {"6 x 4 = 24", true},
    {"sen(x) + cos(x) = 1", false},
    {"2 + 2 = 5", false},
    {"tan = sen/cos", true}
};

int total_de_expressoes = sizeof(expressoes) / sizeof(Expressao);