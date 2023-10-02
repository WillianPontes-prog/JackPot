#include "queue.h"
#include <time.h>

//pode ser modificado para qualquer numeor maior ou igual a 3
#define LINHAS 5
//qualquer valor para velocidade da rotação
#define SPEED 100
//numero maximo de rotações
#define MAX_ROTATION 50
//numero minimo de rotações
#define MIN_ROTATION 10

/**DEFINE AS CORES*/
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_GRAY      "\e[0;37m"

/**PREDEFINE AS LINHAS COM SUAS CORES*/
#define PRINT_LINHA         COLOR_GRAY"|"COLOR_RED"%d"COLOR_GRAY"|"
#define PRINT_LINHA_MEIO    COLOR_MAGENTA"|"COLOR_GREEN"%d"COLOR_MAGENTA"|"     COLOR_GRAY
#define PRINT_LINHA_LEFT    COLOR_MAGENTA">"COLOR_GREEN"%d"COLOR_MAGENTA"|"     COLOR_GRAY
#define PRINT_LINHA_RIGHT   COLOR_MAGENTA"|"COLOR_GREEN"%d"COLOR_MAGENTA"<"     COLOR_GRAY


void jackpot (int n, int r) {

    /**=iniciando====================================================================**/

    //inicializção de variaveis
    int i, j, k, l, rotacoes = 4, guardaValor;

    //Cria um vetor com posições para cada um dos carreteis
    Queue** carreteis;
    carreteis = (Queue**) malloc(n*sizeof(Queue*));


    //preenche cada um dos carreteis com numeros de 0-9
    for(i = 0; i < n; i++){
        carreteis[i] = create(r+1);

        for(j = 0; j < r; j++){
            enqueue(carreteis[i], r-1-j);
        }
    }
    /**============================================================================**/

    /**===Funcionamento============================================================**/
    printf("Ola, bem vindo e boa sorte!!\n\n");
    system("pause");

    //passa por cada posição do vetor para acessar todos os carreteis
    for(i = 0; i < n; i++){

        //define um numero aleatorio de rotações usando numero minimo e maximo de rotações
        rotacoes = ((rand())%(MAX_ROTATION+1-MIN_ROTATION)+MIN_ROTATION);

        //rotaciona a quantidade
        for(j = 0; j < rotacoes; j++){
        //======================================================================//
            //Limpa tudo para dar impressão de rotação
            system("cls");
            //======================================================================//
            //guarda o valor anterior e adiciona novamente no fim fila
            guardaValor = dequeue(carreteis[i]);
            enqueue(carreteis[i], guardaValor);
            //======================================================================//

            //passa por todas as linhas menos as ultimas três
            for(k = 0; k < LINHAS-3; k++){
                //passa por todos os carreteis
                for(l = 0; l < n; l++){
                    //desenha
                    printf(PRINT_LINHA,(front(carreteis[l])+k)%r);
                }
                //pula linha
                printf("\n");
            }



            //desenha a linha com o valor que realmente ira ser contada
            //separado para poder desenhas as "setinhas" (seta esquerda)
            printf(PRINT_LINHA_LEFT,(front(carreteis[0])+LINHAS-3)%r);

            //desenha os numeros entre as "setinhas"
            for(l = 1; l < n-1; l++){
                printf(PRINT_LINHA_MEIO,(front(carreteis[l])+k)%r);
            }

            //separado para poder desenhas as "setinhas" (seta direita)
            printf(PRINT_LINHA_RIGHT,(front(carreteis[n-1])+LINHAS-3)%r);

            //pula linha
            printf("\n");

            //passa pelas ultimas duas linhas
            for(k = LINHAS-2; k < LINHAS; k++){
                //passa pelos carreteis
                for(l = 0; l < n; l++){
                    //desenha
                    printf(PRINT_LINHA,(front(carreteis[l])+k)%r);
                }
                //pula linha
                printf("\n");
            }

            //velocidade de "rotação" (pode ser alterado no define)
            Sleep(SPEED);
        }

        //se não for a ultima rotação ele diz para ir para a proxima
        if(i != n-1){
            printf("\n\nVamos para o proximo numero.\n\n");
            system("pause");
        }
    }
    /**============================================================================**/

    /**=Resultados=================================================================**/

    //faz uma contagem de comparações entre o vetor e em caso de uma diferença ja aponta o erro
    for(i = 1; i < n && front(carreteis[i]) == front(carreteis[i-1]); i++);

    //compara para ver se as comparações corretas são suficientes
    if(i >= n){
        //aponta que conseguiu :)
        printf(COLOR_GREEN"\nPARABENS VOCE GANHOU!!!\n");

        //verifica se foram apenas 7
        if((front(carreteis[n-1])+LINHAS-3)%r == 7){
            printf(COLOR_GREEN"\nVOCE CONSEGUIU "COLOR_RED"%d"COLOR_GREEN" NUMEROS "COLOR_RED"7"COLOR_GREEN "\nVOCE TEM MUITA SORTE\n", n);
        }
    //ponta um erro :(
    }else{
        printf(COLOR_RED"\nNao foi dessa vez :(\n");
    }

    //volta a cor ao normal
    printf(COLOR_GRAY);

    //desaloca todos os carreteis
    for(i = 0; i < n; i++){
        destroy(carreteis[i]);
    }

    //desaloca o vetor dos carreteis
    free(carreteis);

    /**============================================================================**/
}

int main () {
    srand(time(NULL));
    int n = 8;  /*número de carretéis (NO MINIMO 2)*/
    int r = 10; /*sequência de números em cada carretel (ACONCELHAVEL NO MAXIMO 10 PARA NÃo ESTRAGAR A INTERFACE, MAS FUNCIONA COM QUALQUER NUMERO ACIMA DE 0)*/
    jackpot (n, r);
}
