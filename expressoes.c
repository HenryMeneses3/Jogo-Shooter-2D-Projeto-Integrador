#include "objetos.h"

Expressao expressoes[] =
{
    //Trigonometria
    {"sen(30)=1/2", true},
    {"sen(45)=0", false},
    {"cos(60)=1/2", true},
    {"sen(45)=1/2", false},
    {"tan(45)=1", true},
    {"cos(30)=1/2", false},
    {"cos(0)=1", true},
    {"tan(60)=1", false},
    {"sen²+cos²=1", true},
    {"sen(60)=1/2", false},
    {"tan=sen/cos", true},
    {"cos(45)=1", false},
    {"cos(45)=√2/2", true},
    {"sen²−cos²=1", false},
    {"tan(60)=√3", true},
    {"tan=cos/sen", false},
    {"sen(45)=√3/2", false},

	//Física
    {"F=mxa", true},
    {"F=axm", false},
    {"v=Δs/Δt", true},
    {"v=Δt/Δs", false},
    {"E=mxc²", true},
    {"E=mxc", false},
    {"Q=mxcxΔT", true},
    {"Q=m+cxΔT", false},

    {"log(100)=2", true},
    {"Δ=b²-4ac", true},
    {"log(100)=1", false},
    {"Δ=a²-bc", false}
};


int total_de_expressoes = sizeof(expressoes) / sizeof(Expressao);