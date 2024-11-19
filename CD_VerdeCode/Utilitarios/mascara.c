#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "mascara.h"

void mascara_senha(char *senha, int max_len) {
    int i = 0;
    char ch;
    while ((ch = _getch()) != '\r' && i < max_len - 1) {  // '\r' é Enter
        if (ch == '\b') {  // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Remove o último caractere digitado
            }
        } else {
            senha[i++] = ch;
            printf("*");  // Mostra o caractere como '*'
        }
    }
    senha[i] = '\0';  // Termina a string
    printf("\n");
}

void mascara_cep(char *cep) {
    int i = 0;
    char ch;
    
    while (i < 9) {  // Formato: 99999-999
        ch = _getch();

        if (ch >= '0' && ch <= '9') {  // Apenas números
            if (i == 5) {
                printf("-");  // Adiciona o traço automaticamente
                cep[i++] = '-';
            }
            cep[i++] = ch;
            printf("%c", ch);  // Exibe o caractere
        } else if (ch == '\b' && i > 0) {  // Backspace
            i--;
            printf("\b \b");
        }

        // Verifica se o CEP está completo antes de sair
        if (i == 9) {
            printf("\n");
            break;
        }
    }


    cep[i] = '\0';  
    printf("\n");
}

void aplicar_mascara_cpf(char* cpf, char* cpf_com_mascara) {
    int j = 0;

    for (int i = 0; i < 11; i++) {
        if (i == 3 || i == 6) {
            cpf_com_mascara[j++] = '.';  // Adiciona ponto
        } else if (i == 9) {
            cpf_com_mascara[j++] = '-';  // Adiciona hífen
        }
        cpf_com_mascara[j++] = cpf[i];  // Adiciona o número do CPF
    }

    cpf_com_mascara[14] = '\0';  // Finaliza a string com '\0'
}

void imprimir_cpf_com_mascara(char* cpf) {
    // Formato esperado: xxx.xxx.xxx-xx
    if (strlen(cpf) == 11) {
        printf("%c%c%c.%c%c%c.%c%c%c-%c%c\n", 
               cpf[0], cpf[1], cpf[2], 
               cpf[3], cpf[4], cpf[5], 
               cpf[6], cpf[7], cpf[8], 
               cpf[9], cpf[10]);
    } else {
        printf("CPF inválido!\n");
    }
}

void ler_cpf_com_mascara(char* cpf) {
    int i = 0;
    char ch;
    int mascara_pos = 0; // Para controlar a posição da máscara

    // Loop para capturar o CPF, permitindo apenas números
    while (i < 11) {  // Limita a 11 caracteres para o CPF
        ch = _getch();  // Lê o caractere sem exibir no console

        if (ch == 13) {  // Se pressionar Enter, termina
            break;
        } else if (ch == 8) {  // Se pressionar Backspace, apaga o caractere anterior
            if (i > 0) {
                i--;
                printf("\b \b");  // Apaga o último caractere na tela
            }
        } else if ((ch >= '0' && ch <= '9') && i < 11) {
            cpf[i] = ch;      // Armazena o número digitado
            cpf[i + 1] = '\0';// Finaliza a string corretamente
            printf("%c", ch);  // Mostra o caractere digitado

            // Aplicando a máscara enquanto o usuário digita
            if (i == 2 || i == 5) {
                printf(".");  // Coloca o ponto no formato
            } else if (i == 8) {
                printf("-");  // Coloca o hífen no formato
            }

            i++;  // Avança para o próximo caractere
        }
    }

    cpf[i] = '\0';  // Garante que a string seja terminada corretamente
}



void mascara_dat(char *dat) {
    int i = 0;
    char ch;
    while (1) {  // Formato: dd/mm/aaaa
        ch = _getch();
         if (ch == '\r') {  // Verifica se a tecla pressionada foi Enter (código '\r')
            break;  // Sai do laço
        }

        if (ch >= '0' && ch <= '9') {  // Apenas números
            if (i == 2 || i == 5) {
                printf("/");  // Adiciona a barra automaticamente
                dat[i++] = '/';
            }
            dat[i++] = ch;
            printf("%c", ch);  // Exibe o caractere
        } else if (ch == '\b' && i > 0) {  // Backspace
            i--;
            printf("\b \b");
        }
    }
    dat[i] = '\0';
    printf("\n");
}
