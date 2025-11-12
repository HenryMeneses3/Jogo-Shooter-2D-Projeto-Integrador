#include "objetos.h"
#include "stdlib.h"
#include"config.h"
#include "cenas.h"


int indice_ordem_atual;
int ordem_fileiras[MAX_FILEIRAS];

Fileira infofileiras[] =
{
    { "Reptilia", "Classe", 1, "Corpo coberto por escamas de queratina"},
    { "Aves", "Classe", 5, "Corpo coberto por penas"},
    { "Amphibia", "Familia", 6, "Pele fina, umida e permeavel"},
    { "Felidae", "Familia", 2, "Possuem garras retrateis"},
    { "Equidae", "Familia", 3, "Um unico dedo em cada pata com casco"},
    { "Herpestidae", "Familia", 0, "Corpo alongado e patas curtas, resiste ao veneno"},
    { "Squamata", "Ordem", 4, "Escamas queratinizadas que se renovam periodicamente"},
    { "Artiodactyla", "Ordem", 9, "Numero par de dedos nas patas"}
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
    else if (indice_ordem_atual >= total_de_fileiras && personagem.vida > 0)
    {
		destruir_cena(CENA_LEVEL_2);
		mudar_de_cena(CENA_CONCLUSAO);
    }
}