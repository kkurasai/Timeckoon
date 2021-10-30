#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {

    //variaveis do menu de dia unico
    int comecoDia, fimDia, cont1, ocupado1[2][MAX], livre1[2][MAX], duracao[MAX];

    //variaveis comuns
    int h, min, i, j, k, l, aux, menor, posicaoMenor, numRepetidos;

    //variaveis do menu de semana
    int diaInt, qtdeDias, diaCalc, cont2[7], diasEspecif[7], comecoDiaVet[7], fimDiaVet[7], ocupado2[7][2][MAX], livre2[7][2][MAX];
    char opcao, dia[20], diaAnterior[20];

    while(1) {
        //inicializando variaveis
        for(i=0; i<MAX; i++)
            duracao[i]=0;
        for(i=0; i<7; i++) {
            cont2[i]=0;
            comecoDiaVet[i]=8*60;
            fimDiaVet[i]=23*60+59;
            for(j=0; j<2; j++)
                for(k=0; k<MAX; k++)
                    ocupado2[0][0][i]=10000;
        }     
        for(i=0; i<2; i++)
            for(j=0; j<MAX; j++)
                ocupado1[i][j]=livre1[i][j]=0;
        cont1=h=min=i=j=aux=menor=posicaoMenor=0;
        fimDia=23*60+59;
        comecoDia=8*60;
        diaInt=10;
              
        //menu geral
        system("cls");
        printf("CALCULADORA DE HORARIOS LIVRES\n\n");
        printf("[0] Sair do programa\n");
        printf("[1] Calcular horarios livres em um dia qualquer\n");
        printf("[2] Calcular horarios livres em uma semana\n\n");

        //validador de opcao
        while(1) {
            printf("Opcao: ");
            scanf(" %c", &opcao);
            if(opcao=='0'||opcao=='1'||opcao=='2')
                break;                
            else
                printf("Opcao invalida! Por favor, insira novamente.\n");
        }
     
        //sair do programa
        if(opcao=='0')
            break;


        //menu de dia unico
        else if(opcao=='1') {        
            while(1) {
                system("cls");
                printf("CALCULADORA DE HORARIOS LIVRES\n\n");
                printf("[0] Sair do menu\n");
                printf("[1] Definir inicio e fim do dia\n");
                printf("[2] Inserir um periodo de tempo ocupado\n");
                printf("[3] Calcular horarios livres no dia\n\n");
                printf("Horarios em formato 24h (xx:xx)\n\n");

                //validador de opcao
                while(1) {
                    printf("Opcao: ");
                    scanf(" %c", &opcao);
                    if(opcao=='0'||opcao=='1'||opcao=='2'||opcao=='3')
                        break;                
                    else
                        printf("Opcao invalida! Por favor, insira novamente.\n");
                }

                //sair do menu
                if(opcao=='0')
                    break;

                //definir inicio e fim do dia
                else if(opcao=='1') {  
                    //validador de entrada do inicio
                    while(1) {
                        printf("Digite o horario do inicio do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h<0 || h>23 || min<0 || min>59)
                            printf("Horario invalido! Por favor, insira novamente.\n");
                        else
                            break;
                    }                        
                    comecoDia=h*60+min;

                    //validador de entrada do fim
                    while(1) {
                        printf("Digite o horario do fim do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h<0 || h>23 || min<0 || min>59)
                            printf("Horario invalido! Por favor, insira novamente.\n");
                        else
                            break;
                    }
                    fimDia=h*60+min;
                }                
                
                //inserir um periodo de tempo ocupado
                else if(opcao=='2') {
                    while(1) {
                        //validador do inicio do periodo
                        while(1) {
                            printf("Digite o horario do inicio do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }
                        ocupado1[0][cont1]=h*60+min;

                        //validador do fim do periodo
                        while(1) {
                            printf("Digite o horario do fim do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }
                        ocupado1[1][cont1]=h*60+min; //conversao para minutos

                        //validador do periodo
                        if(ocupado1[0][cont1]>=ocupado1[1][cont1])
                            printf("Periodo invalido! Por favor, insira novamente.\n");
                        else {
                            cont1++;
                            break;
                        }
                    }
                }
                
                //calcular horarios livres no dia
                else if(opcao=='3') {
                    /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                       Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                       seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                       Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                       blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */

                    if(comecoDia>fimDia) {
                        ocupado1[0][cont1]=fimDia;
                        ocupado1[1][cont1]=comecoDia;
                    }
                    else if(comecoDia<fimDia) {
                        ocupado1[0][cont1]=fimDia;
                        ocupado1[1][cont1]=23*60+59;
                        cont1++;
                        ocupado1[0][cont1]=0;
                        ocupado1[1][cont1]=comecoDia;
                    }

                    //select sort entre as entradas
                    for(i=0; i<=cont1-1; i++) {
                        menor=100000;
                        for(j=i; j<=cont1; j++) {
                            if(ocupado1[0][j]<menor) {
                                menor=ocupado1[0][j];
                                posicaoMenor=j;
                            }
                        }            
                        aux=ocupado1[0][i];
                        ocupado1[0][i]=ocupado1[0][posicaoMenor];
                        ocupado1[0][posicaoMenor]=aux;

                        aux=ocupado1[1][i];
                        ocupado1[1][i]=ocupado1[1][posicaoMenor];
                        ocupado1[1][posicaoMenor]=aux;
                    }

                    // select sort se o ocupado1[0] for igual mas ocupado[1] diferente
                    for(i=0; i<=cont1; i+=numRepetidos+1) {
                        numRepetidos=0;
                        for(j=i+1; j<=cont1; j++)
                            if(ocupado1[0][j]==ocupado1[0][i])
                                numRepetidos++;

                        for(j=i; j<=i+numRepetidos-1; j++) {
                            menor=100000;
                            for(k=i; k<=i+numRepetidos; k++) {
                                if(ocupado1[1][k]<menor) {
                                    menor=ocupado1[1][k];
                                    posicaoMenor=k;
                                }
                            }            
                            aux=ocupado1[1][j];
                            ocupado1[1][j]=ocupado1[1][posicaoMenor];
                            ocupado1[1][posicaoMenor]=aux;
                        }
                    }
                    
                    //remover periodos de tempo redundantes
                    for(i=1; i<=cont1; i++) {
                        //se um periodo estiver contido em outro, vamos exclui-lo
                        if(ocupado1[0][i]>ocupado1[0][i-1] && ocupado1[1][i]<ocupado1[1][i-1]) {
                            for(j=i; j<=cont1-1; j++) {
                                ocupado1[0][j]=ocupado1[0][j+1];
                                ocupado1[1][j]=ocupado1[1][j+1];
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }

                        //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                        else if(ocupado1[0][i]<=ocupado1[1][i-1]) {
                            ocupado1[1][i-1]=ocupado1[1][i];
                            for(j=i; j<=cont1-1; j++) {
                                ocupado1[0][j]=ocupado1[0][j+1];
                                ocupado1[1][j]=ocupado1[1][j+1];
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }
                    }


                    //calculo dos tempos livres
                    for(i=0; i<=cont1+1; i++) {
                        /* No geral, os periodos livres sao o intervalo entre o final de
                           um periodo ocupado e comeco do seguinte.
                           Para que o algoritmo seja generico, o primeiro periodo sera sempre
                           o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                           tiver duracao 0, ele sera ignorado)
                           A mesma logica se aplica ao ultimo periodo livre. */

                        if(i==0) {
                            livre1[0][i]=0;
                            livre1[1][i]=ocupado1[0][i];
                        }
                        else if(i==cont1+1) {
                            livre1[0][i]=ocupado1[1][i-1];
                            livre1[1][i]=23*60+59;
                        }
                        else {
                            livre1[0][i]=ocupado1[1][i-1];
                            livre1[1][i]=ocupado1[0][i];
                        }
                    }

                    printf("Periodos de tempo livre:\n");
                    for(i=0; i<=cont1+1; i++) {
                        duracao[i]=livre1[1][i]-livre1[0][i];

                        if(duracao[i]!=0) { //para excluir periodos nulos
                            printf("> %02d:%02.0f - %02d:%02.0f\n", livre1[0][i]/60, (livre1[0][i]/60.0-livre1[0][i]/60)*60, livre1[1][i]/60, (livre1[1][i]/60.0-livre1[1][i]/60)*60);
                            printf("  Duracao: %02d:%02.0f\n", duracao[i]/60, (duracao[i]/60.0-duracao[i]/60)*60);
                        }
                        else if(i==1)
                            printf("Nenhum\n");
                    }

                    system("pause");
                    break;
                }
            }
        }


        //menu da semana
        else if(opcao=='2') {
            while(1) {

                system("cls");
                printf("CALCULADORA DE HORARIOS LIVRES\n\n");
                printf("[0] Sair do menu\n");
                printf("[1] Definir inicio e fim do dia\n");
                printf("[2] Definir dia da semana\n");
                printf("[3] Inserir um periodo de tempo ocupado\n");
                printf("[4] Calcular horarios livres em um dia da semana\n");
                printf("[5] Calcular horarios livres na semana\n\n");
                printf("Horarios devem estar em formato 24h (xx:xx)\n");
                printf("Nao usar palavra com acento ou cedilha\n\n");

                //validador de opcao
                while(1) {
                    printf("Opcao: ");
                    scanf(" %c", &opcao);
                    if(opcao=='0'||opcao=='1'||opcao=='2'||opcao=='3'||opcao=='4'||opcao=='5')
                        break;                
                    else
                        printf("Opcao invalida! Por favor, insira novamente.\n");
                }

                //sair do menu
                if(opcao=='0')
                    break;

                //definir inicio e fim do dia
                else if(opcao=='1') {
                    while(1) {
                        //menu para definir abrangencia
                        printf("\n[0] Sair do menu\n");
                        printf("[1] Definir para todos os dias\n");
                        printf("[2] Definir para dias especificos\n\n");
                                
                        //validacao de entrada da opcao
                        while(1) {
                            printf("Opcao: ");
                            scanf(" %c", &opcao);
                            printf("\n");
                            if(opcao=='0'||opcao=='1'||opcao=='2')
                                break;                                
                            else
                                printf("Opcao invalida! Por favor, insira novamente.\n");
                        }

                        //sair do menu
                        if(opcao=='0')
                            break;
                        
                        //lendo os dias os dias, caso for definir para dias especificos
                        if(opcao=='2') {
                            //quantidade de dias
                            printf("Quantidade de dias: ");
                            scanf("%d", &qtdeDias);

                            getchar();

                            //lendo os dias
                            for(i=0; i<qtdeDias; ) {
                                printf("\nDia %d: ", i+1);
                                gets(dia);
                                if(stricmp(dia, diaAnterior)==0)
                                    printf("Dia da semana repetido! Por favor, insira novamente.\n");
                                else if(stricmp(dia, "Domingo")==0 || stricmp(dia, "domingo")==0 || stricmp(dia, "DOMINGO")==0) {
                                    diasEspecif[i]=0;
                                    i++;
                                }
                                else if(stricmp(dia, "Segunda")==0 || stricmp(dia, "segunda")==0 || stricmp(dia, "SEGUNDA")==0 || stricmp(dia, "Segunda-feira")==0 || stricmp(dia, "segunda-feira")==0 || stricmp(dia, "SEGUNDA-FEIRA")==0) {
                                    diasEspecif[i]=1;
                                    i++;
                                }
                                else if(stricmp(dia, "Terca")==0 || stricmp(dia, "terca")==0 || stricmp(dia, "TERCA")==0 || stricmp(dia, "Terca-feira")==0 || stricmp(dia, "terca-feira")==0 || stricmp(dia, "TERCA-FEIRA")==0) {
                                    diasEspecif[i]=2;
                                    i++;
                                }
                                else if(stricmp(dia, "Quarta")==0 || stricmp(dia, "quarta")==0 || stricmp(dia, "QUARTA")==0 || stricmp(dia, "Quarta-feira")==0 || stricmp(dia, "quarta-feira")==0 || stricmp(dia, "QUARTA-FEIRA")==0) {
                                    diasEspecif[i]=3;
                                    i++;
                                }
                                else if(stricmp(dia, "Quinta")==0 || stricmp(dia, "quinta")==0 || stricmp(dia, "QUINTA")==0 || stricmp(dia, "Quinta-feira")==0 || stricmp(dia, "quinta-feira")==0 || stricmp(dia, "QUINTA-FEIRA")==0) {
                                    diasEspecif[i]=4;
                                    i++;
                                }
                                else if(stricmp(dia, "Sexta")==0 || stricmp(dia, "sexta")==0 || stricmp(dia, "SEXTA")==0 || stricmp(dia, "Sexta-feira")==0 || stricmp(dia, "sexta-feira")==0 || stricmp(dia, "SEXTA-FEIRA")==0) {
                                    diasEspecif[i]=5;
                                    i++;
                                }
                                else if(stricmp(dia, "Sabado")==0 || stricmp(dia, "sabado")==0 || stricmp(dia, "SABADO")==0) {
                                    diasEspecif[i]=6;
                                    i++;
                                }
                                else
                                    printf("Dia da semana invalido! Por favor, insira novamente.\n");

                                strcpy(diaAnterior, dia);
                            }
                        }

                        //validador de entrada do horario de inicio
                        while(1) {
                            printf("Digite o horario do inicio do dia: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }

                        //se for para todos os dias
                        if(opcao=='1')
                            for(i=0; i<7; i++)
                                comecoDiaVet[i]=min+h*60;
                        //se for para dias especificos
                        else
                            for(i=0; i<qtdeDias; i++)
                                comecoDiaVet[diasEspecif[i]]=min+h*60;

                        //validacao de entrada do horario de fim
                        while(1) {
                            printf("Digite o horario do fim do dia: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }

                        //se for para todos os dias
                        if(opcao=='1')
                            for(i=0; i<7; i++)
                                fimDiaVet[i]=min+h*60;
                        //se for para dias especificos
                        else
                            for(i=0; i<qtdeDias; i++)
                                fimDiaVet[diasEspecif[i]]=min+h*60;
                    }
                }

                //definir dia da semana
                else if(opcao=='2') {
                    getchar();
                    while(1) {
                        printf("\nDigite o dia da semana: ");
                        gets(dia);
                        if(stricmp(dia, "Domingo")==0 || stricmp(dia, "domingo")==0 || stricmp(dia, "DOMINGO")==0) {
                            diaInt=0;
                            break;
                        }
                        else if(stricmp(dia, "Segunda")==0 || stricmp(dia, "segunda")==0 || stricmp(dia, "SEGUNDA")==0 || stricmp(dia, "Segunda-feira")==0 || stricmp(dia, "segunda-feira")==0 || stricmp(dia, "SEGUNDA-FEIRA")==0) {
                            diaInt=1;
                            break;
                        }
                        else if(stricmp(dia, "Terca")==0 || stricmp(dia, "terca")==0 || stricmp(dia, "TERCA")==0 || stricmp(dia, "Terca-feira")==0 || stricmp(dia, "terca-feira")==0 || stricmp(dia, "TERCA-FEIRA")==0) {
                            diaInt=2;
                            break;
                        }
                        else if(stricmp(dia, "Quarta")==0 || stricmp(dia, "quarta")==0 || stricmp(dia, "QUARTA")==0 || stricmp(dia, "Quarta-feira")==0 || stricmp(dia, "quarta-feira")==0 || stricmp(dia, "QUARTA-FEIRA")==0) {
                            diaInt=3;
                            break;
                        }
                        else if(stricmp(dia, "Quinta")==0 || stricmp(dia, "quinta")==0 || stricmp(dia, "QUINTA")==0 || stricmp(dia, "Quinta-feira")==0 || stricmp(dia, "quinta-feira")==0 || stricmp(dia, "QUINTA-FEIRA")==0) {
                            diaInt=4;
                            break;
                        }
                        else if(stricmp(dia, "Sexta")==0 || stricmp(dia, "sexta")==0 || stricmp(dia, "SEXTA")==0 || stricmp(dia, "Sexta-feira")==0 || stricmp(dia, "sexta-feira")==0 || stricmp(dia, "SEXTA-FEIRA")==0) {
                            diaInt=5;
                            break;
                        }
                        else if(stricmp(dia, "Sabado")==0 || stricmp(dia, "sabado")==0 || stricmp(dia, "SABADO")==0) {
                            diaInt=6;
                            break;
                        }
                        else
                            printf("Dia da semana invalido! Por favor, insira novamente.\n");
                    }
                }

                //inserir um periodo de tempo ocupado
                else if(opcao=='3') {
                    while(1) {
                        //caso um dia nao tiver sido escolhido previamente
                        if(diaInt==10) {
                            printf("Voce precisa escolher o um dia primeiro!\n");
                            system("pause");
                            break;
                        }

                        //validador de entrada do inicio
                        while(1) {
                            printf("Digite o horario do inicio do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }

                        ocupado2[diaInt][0][cont2[diaInt]]=h*60+min;

                        //validador de entrada do fim
                        while(1) {
                            printf("Digite o horario do fim do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h<0 || h>23 || min<0 || min>59)
                                printf("Horario invalido! Por favor, insira novamente.\n");
                            else
                                break;
                        }

                        //validador de periodo
                        if(ocupado2[diaInt][0][cont2[diaInt]]>=h*60+min)
                            printf("Periodo invalido! Por favor, insira novamente.\n");
                        else {
                            ocupado2[diaInt][1][cont2[diaInt]]=h*60+min;
                            cont2[diaInt]++;
                            break;
                        }
                    }
                }
                
                //calcular horarios livres em um dia da semana
                else if(opcao=='4') {
                    getchar();
                    //validacao de entrada da opcao
                    while(1) {
                        printf("\nDigite o dia da semana: ");
                        gets(dia);
                        if(stricmp(dia, "Domingo")==0 || stricmp(dia, "domingo")==0 || stricmp(dia, "DOMINGO")==0) {
                            diaCalc=0;
                            break;
                        }
                        else if(stricmp(dia, "Segunda")==0 || stricmp(dia, "segunda")==0 || stricmp(dia, "SEGUNDA")==0 || stricmp(dia, "Segunda-feira")==0 || stricmp(dia, "segunda-feira")==0 || stricmp(dia, "SEGUNDA-FEIRA")==0) {
                            diaCalc=1;
                            break;
                        }
                        else if(stricmp(dia, "Terca")==0 || stricmp(dia, "terca")==0 || stricmp(dia, "TERCA")==0 || stricmp(dia, "Terca-feira")==0 || stricmp(dia, "terca-feira")==0 || stricmp(dia, "TERCA-FEIRA")==0) {
                            diaCalc=2;
                            break;
                        }
                        else if(stricmp(dia, "Quarta")==0 || stricmp(dia, "quarta")==0 || stricmp(dia, "QUARTA")==0 || stricmp(dia, "Quarta-feira")==0 || stricmp(dia, "quarta-feira")==0 || stricmp(dia, "QUARTA-FEIRA")==0) {
                            diaCalc=3;
                            break;
                        }
                        else if(stricmp(dia, "Quinta")==0 || stricmp(dia, "quinta")==0 || stricmp(dia, "QUINTA")==0 || stricmp(dia, "Quinta-feira")==0 || stricmp(dia, "quinta-feira")==0 || stricmp(dia, "QUINTA-FEIRA")==0) {
                            diaCalc=4;
                            break;
                        }
                        else if(stricmp(dia, "Sexta")==0 || stricmp(dia, "sexta")==0 || stricmp(dia, "SEXTA")==0 || stricmp(dia, "Sexta-feira")==0 || stricmp(dia, "sexta-feira")==0 || stricmp(dia, "SEXTA-FEIRA")==0) {
                            diaCalc=5;
                            break;
                        }
                        else if(stricmp(dia, "Sabado")==0 || stricmp(dia, "sabado")==0 || stricmp(dia, "SABADO")==0) {
                            diaCalc=6;
                            break;
                        }
                        else
                            printf("Dia da semana invalido! Por favor, insira novamente.\n");
                    }

                    /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                       Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                       seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                       Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                       blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                    
                    if(comecoDiaVet[diaCalc]>fimDiaVet[diaCalc]) {
                        ocupado2[diaCalc][0][cont2[diaCalc]]=fimDiaVet[diaCalc];
                        ocupado2[diaCalc][1][cont2[diaCalc]]=comecoDiaVet[diaCalc];
                    }
                    else if(comecoDiaVet[diaCalc]<fimDiaVet[diaCalc]) {
                        ocupado2[diaCalc][0][cont2[diaCalc]]=fimDiaVet[diaCalc];
                        ocupado2[diaCalc][1][cont2[diaCalc]]=23*60+59;
                        cont2[diaCalc]++;
                        ocupado2[diaCalc][0][cont2[diaCalc]]=0;
                        ocupado2[diaCalc][1][cont2[diaCalc]]=comecoDiaVet[diaCalc];
                    }

                    //select sort entre as entradas
                    for(i=0; i<=cont2[diaCalc]-1; i++) {
                        menor=100000;
                        for(j=i; j<=cont2[diaCalc]; j++) {
                            if(ocupado2[diaCalc][0][j]<menor) {
                                menor=ocupado2[diaCalc][0][j];
                                posicaoMenor=j;
                            }
                        }            
                        aux=ocupado2[diaCalc][0][i];
                        ocupado2[diaCalc][0][i]=ocupado2[diaCalc][0][posicaoMenor];
                        ocupado2[diaCalc][0][posicaoMenor]=aux;

                        aux=ocupado2[diaCalc][1][i];
                        ocupado2[diaCalc][1][i]=ocupado2[diaCalc][1][posicaoMenor];
                        ocupado2[diaCalc][1][posicaoMenor]=aux;
                    }

                    // select sort se o ocupado2[0] for igual mas ocupado[1] diferente
                    for(i=0; i<=cont2[diaCalc]; i+=numRepetidos+1) {
                        numRepetidos=0;
                        for(j=i+1; j<=cont2[diaCalc]; j++)
                            if(ocupado2[diaCalc][0][j]==ocupado2[diaCalc][0][i])
                                numRepetidos++;

                        for(j=i; j<=i+numRepetidos-1; j++) {
                            menor=100000;
                            for(k=i; k<=i+numRepetidos; k++) {
                                if(ocupado2[diaCalc][1][k]<menor) {
                                    menor=ocupado2[diaCalc][1][k];
                                    posicaoMenor=k;
                                }
                            }            
                            aux=ocupado2[diaCalc][1][j];
                            ocupado2[diaCalc][1][j]=ocupado2[diaCalc][1][posicaoMenor];
                            ocupado2[diaCalc][1][posicaoMenor]=aux;
                        }
                    }
                    
                    //remover periodos de tempo redundantes
                    for(i=1; i<=cont2[diaCalc]; i++) {
                        //se um periodo estiver contido em outro, vamos exclui-lo
                        if(ocupado2[diaCalc][0][i]>ocupado2[diaCalc][0][i-1] && ocupado2[diaCalc][1][i]<ocupado2[diaCalc][1][i-1]) {
                            for(j=i; j<=cont2[diaCalc]-1; j++) {
                                ocupado2[diaCalc][0][j]=ocupado2[diaCalc][0][j+1];
                                ocupado2[diaCalc][1][j]=ocupado2[diaCalc][1][j+1];
                            }
                            cont2[diaCalc]--; //um periodo a menos no vetor
                            i--;
                        }

                        //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                        else if(ocupado2[diaCalc][0][i]<=ocupado2[diaCalc][1][i-1]) {
                            ocupado2[diaCalc][1][i-1]=ocupado2[diaCalc][1][i];
                            for(j=i; j<=cont2[diaCalc]-1; j++) {
                                ocupado2[diaCalc][0][j]=ocupado2[diaCalc][0][j+1];
                                ocupado2[diaCalc][1][j]=ocupado2[diaCalc][1][j+1];
                            }
                            cont2[diaCalc]--; //um periodo a menos no vetor
                            i--;
                        }
                    }

                    //calculo dos tempos livres
                    for(i=0; i<=cont2[diaCalc]+1; i++) {
                        /* No geral, os periodos livres sao o intervalo entre o final de
                           um periodo ocupado e comeco do seguinte.
                           Para que o algoritmo seja generico, o primeiro periodo sera sempre
                           o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                           tiver duracao 0, ele sera ignorado)
                           A mesma logica se aplica ao ultimo periodo livre. */

                        if(i==0) {
                            livre2[diaCalc][0][i]=0;
                            livre2[diaCalc][1][i]=ocupado2[diaCalc][0][i];
                        }
                        else if(i==cont2[diaCalc]+1) {
                            livre2[diaCalc][0][i]=ocupado2[diaCalc][1][i-1];
                            livre2[diaCalc][1][i]=23*60+59;
                        }
                        else {
                            livre2[diaCalc][0][i]=ocupado2[diaCalc][1][i-1];
                            livre2[diaCalc][1][i]=ocupado2[diaCalc][0][i];
                        }
                    }

                    printf("Periodos de tempo livre:\n");
                    for(i=0; i<=cont2[diaCalc]+1; i++) {
                        duracao[i]=livre2[diaCalc][1][i]-livre2[diaCalc][0][i];

                        if(duracao[i]!=0) { //para excluir periodos nulos
                            printf("> %02d:%02.0f - %02d:%02.0f\n", livre2[diaCalc][0][i]/60, (livre2[diaCalc][0][i]/60.0-livre2[diaCalc][0][i]/60)*60, livre2[diaCalc][1][i]/60, (livre2[diaCalc][1][i]/60.0-livre2[diaCalc][1][i]/60)*60);
                            printf("  Duracao: %02d:%02.0f\n", duracao[i]/60, (duracao[i]/60.0-duracao[i]/60)*60);
                        }
                        else if(i==1)
                            printf("Nenhum\n");
                    }

                    system("pause");
                }

                //calcular horarios livres na semana
                else if(opcao=='5') {
                    for(i=0; i<7; i++) {
                        /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                        Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                        seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                        Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                        blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                        
                        if(comecoDiaVet[i]>fimDiaVet[i]) {
                            ocupado2[i][0][cont2[i]]=fimDiaVet[i];
                            ocupado2[i][1][cont2[i]]=comecoDiaVet[i];
                        }
                        else if(comecoDiaVet[i]<fimDiaVet[i]) {
                            ocupado2[i][0][cont2[i]]=fimDiaVet[i];
                            ocupado2[i][1][cont2[i]]=23*60+59;
                            cont2[i]++;
                            ocupado2[i][0][cont2[i]]=0;
                            ocupado2[i][1][cont2[i]]=comecoDiaVet[i];
                        }

                        //select sort entre as entradas
                        for(j=0; j<=cont2[i]-1; j++) {
                            menor=100000;
                            for(k=j; k<=cont2[i]; k++) {
                                if(ocupado2[i][0][k]<menor) {
                                    menor=ocupado2[i][0][k];
                                    posicaoMenor=k;
                                }
                            }            
                            aux=ocupado2[i][0][j];
                            ocupado2[i][0][j]=ocupado2[i][0][posicaoMenor];
                            ocupado2[i][0][posicaoMenor]=aux;

                            aux=ocupado2[i][1][j];
                            ocupado2[i][1][j]=ocupado2[i][1][posicaoMenor];
                            ocupado2[i][1][posicaoMenor]=aux;
                        }

                        // select sort se o ocupado2[0] for igual mas ocupado[1] diferente
                        for(j=0; j<=cont2[i]; j+=numRepetidos+1) {
                            numRepetidos=0;
                            for(k=j+1; k<=cont2[i]; k++)
                                if(ocupado2[i][0][k]==ocupado2[i][0][j])
                                    numRepetidos++;

                            for(k=j; k<=j+numRepetidos-1; k++) {
                                menor=100000;
                                for(l=j; l<=j+numRepetidos; l++) {
                                    if(ocupado2[i][1][l]<menor) {
                                        menor=ocupado2[i][1][l];
                                        posicaoMenor=l;
                                    }
                                }            
                                aux=ocupado2[i][1][k];
                                ocupado2[i][1][k]=ocupado2[i][1][posicaoMenor];
                                ocupado2[i][1][posicaoMenor]=aux;
                            }
                        }
                        
                        //remover periodos de tempo redundantes
                        for(j=1; j<=cont2[i]; j++) {
                            //se um periodo estiver contido em outro, vamos exclui-lo
                            if(ocupado2[i][0][j]>ocupado2[i][0][j-1] && ocupado2[i][1][j]<ocupado2[i][1][j-1]) {
                                for(k=j; k<=cont2[i]-1; k++) {
                                    ocupado2[i][0][k]=ocupado2[i][0][k+1];
                                    ocupado2[i][1][k]=ocupado2[i][1][k+1];
                                }
                                cont2[i]--; //um periodo a menos no vetor
                                j--;
                            }

                            //se um periodo comecar antes ou quando outro acabar, vamos kunta-los
                            else if(ocupado2[i][0][j]<=ocupado2[i][1][j-1]) {
                                ocupado2[i][1][j-1]=ocupado2[i][1][j];
                                for(k=j; k<=cont2[i]-1; k++) {
                                    ocupado2[i][0][k]=ocupado2[i][0][k+1];
                                    ocupado2[i][1][k]=ocupado2[i][1][k+1];
                                }
                                cont2[i]--; //um periodo a menos no vetor
                                j--;
                            }
                        }

                        //calculo dos tempos livres
                        for(j=0; j<=cont2[i]+1; j++) {
                            /* No geral, os periodos livres sao o intervalo entre o final de
                            um periodo ocupado e comeco do seguinte.
                            Para que o algoritmo seja generico, o primeiro periodo sera sempre
                            o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                            tiver duracao 0, ele sera ignorado)
                            A mesma logica se aplica ao ultimo periodo livre. */

                            if(j==0) {
                                livre2[i][0][j]=0;
                                livre2[i][1][j]=ocupado2[i][0][j];
                            }
                            else if(j==cont2[i]+1) {
                                livre2[i][0][j]=ocupado2[i][1][j-1];
                                livre2[i][1][j]=23*60+59;
                            }
                            else {
                                livre2[i][0][j]=ocupado2[i][1][j-1];
                                livre2[i][1][j]=ocupado2[i][0][j];
                            }
                        }

                        switch(i) {
                            case 0:
                                printf("\nDomingo\n");
                                break;
                            case 1:
                                printf("\nSegunda-feira\n");
                                break;
                            case 2:
                                printf("\nTerca-feira\n");
                                break;
                            case 3:
                                printf("\nQuarta-feira\n");
                                break;
                            case 4:
                                printf("\nQuinta-feira\n");
                                break;
                            case 5:
                                printf("\nSexta-feira\n");
                                break;
                            case 6:
                                printf("\nSabado\n");
                        }

                        printf("Periodos de tempo livre:\n");
                        for(j=0; j<=cont2[i]+1; j++) {
                            duracao[j]=livre2[i][1][j]-livre2[i][0][j];

                            if(duracao[j]!=0) { //para excluir periodos nulos
                                printf("> %02d:%02.0f - %02d:%02.0f\n", livre2[i][0][j]/60, (livre2[i][0][j]/60.0-livre2[i][0][j]/60)*60, livre2[i][1][j]/60, (livre2[i][1][j]/60.0-livre2[i][1][j]/60)*60);
                                printf("  Duracao: %02d:%02.0f\n", duracao[j]/60, (duracao[j]/60.0-duracao[j]/60)*60);
                            }
                            else if(j==1)
                                printf("Nenhum\n");
                        }
                    }
                    printf("\n");
                    system("pause");
                    break;
                }         
            }
        }
    }

    return 0;
}