#include "objetos.h"

Expressao expressoes[] =
{
    // Certo/Errado - Paronimos Comuns de EM
    {"ratificar", true},    // Certo (confirmar)
    {"retificar", true},    // Certo (corrigir)
    {"ratificacao", false}, // Errado (grafia com 'ao' e 'c')
    {"imigrar", true},      // Certo (entrar num pais)
    {"emigrar", true},      // Certo (sair de um pais)


    // Certo/Errado - S/Z/C/SS
    {"coincidencia", true},        // Certo (costurar)
    {"conhecidencia", true},        // Certo (cozinhar)
    {"escencia", false},       // Repeticao para forcar a diferenciacao
    {"essencia", true},       // Repeticao para forcar a diferenciacao
    {"ecessao", false},     // Errado (nao existe, confusao com excecao/sessao)
    {"excecao", true},
    {"discricao", true},    // Certo (prudencia, reserva)
    {"descricao", true},    // Certo (ato de descrever)
    {"discrecao", false},   // Errado (erro de grafia)


    // Certo/Errado - Homofonos / S/X/C
    {"espectador", true},   // Certo (o que assiste)
    {"expectador", false},  // Errado (erro comum na troca do 's' pelo 'x')
    {"conssiliar", false},   // Errado 
    {"conciliar", true},
    {"acerca", true},       // Certo (a respeito de)
    {"a cerca", true},      // Certo (a distancia de)
    {"trouxe", true},    // Certo
    {"trousse", false},



    // Certo/Errado - Outros erros sutis sem acento
    {"previlegio", false},  // Errado (correto: privilegio)
    {"privilegio", true},   // Certo
    {"empecilho", true},    // Certo
    {"empessilho", true},
    {"impecilho", false},   // Errado (erro comum na vogal 'e'/'i')
    {"extinguiu", true},    // Certo
    {"estinguiu", false},     // Errado
    {"asterisco", true}, 
	{"asteristico", false},
    {"superfluo", true},
    {"superfulo", false},
    {"consciente", true},
    {"consiente", false},

    // Certo/Errado - Homofonos e Paronimos (sem acento)
    {"absolver", true },   // Certo (perdoar)
    {"abisolver", false}, // Errado (erro de grafia)
    {"infligir", true},   // Certo (aplicar pena)
    {"inflingir", false},  
    {"infringir", true},  // Certo (violar, transgredir)
    {"infragir", false},  // Errado (erro de grafia)
    {"despensa", true},   // Certo (comodo para guardar alimentos)
    {"dispensa", true},   // Certo (ato de dispensar/isenção)
    {"dispesa", false},   // Errado (erro de grafia)
};


int total_de_expressoes = sizeof(expressoes) / sizeof(Expressao);