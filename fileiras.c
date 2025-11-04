#include "objetos.h"
#include "stdlib.h"
#include"config.h"
#include "cenas.h"


int indice_ordem_atual;
int ordem_fileiras[MAX_FILEIRAS];

Fileira infofileiras[] =
{
    { "Reptilia", "Classe", 1},
    { "Aves", "Classe", 5},
    { "Amphibia", "Familia", 6},
    { "Felidae", "Familia", 2},
    { "Equidae", "Familia", 3},
    { "Herpestidae", "Familia", 0},
    { "Squamata", "Ordem", 4},
    { "Artiodactyla", "Ordem", 9}
};

int total_de_fileiras = sizeof(infofileiras) / sizeof(Fileira);

void embaralhar_fileiras(void)
{
    for (i = 0; i < total_de_fileiras; i++)
    {
        ordem_fileiras[i] = i;
    }

    for (i = total_de_fileiras - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        int temp = ordem_fileiras[i];
        ordem_fileiras[i] = ordem_fileiras[j];
        ordem_fileiras[j] = temp;
    }

    indice_ordem_atual = 0; // começa do primeiro da ordem
}

void sortear_fileira(void)
{
    if (indice_ordem_atual < total_de_fileiras)
    {
        fileira_ativa = ordem_fileiras[indice_ordem_atual];
        indice_ordem_atual++;
    }
    else
    {
		mudar_de_cena(CENA_CONCLUSAO);
    }
}