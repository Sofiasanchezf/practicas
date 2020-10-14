#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encuentra_lambdas_recursiva(char ***tabla, int *estado_destino, int num_estados, int j){
  int aa;
  for(aa=0; aa<num_estados;aa++){
      // printf("ha entrado en el for, iteracion %d\n", aa);
      // printf("la tabla contiene %c\n", tabla[j][aa][2]);
      // printf("tabla[%d][%d][%d]%c " ,estado, j, k, tabla[estado][j][k]);
      if(tabla[j][aa][2]=='-'){
        printf("estado siguiente posible por lambda %d\n", aa);
        // flag = 0;
        estado_destino[aa]=0;
        encuentra_lambdas_recursiva(tabla, estado_destino, num_estados, aa);
      } /*else if(tabla[estado][j][k]=='-'){
        printf("estado siguiente posible por lambdas%d\n", j);
        // flag = 0;
        estado_destino[j]=0;
      }*/
  }
}

int main(int argc, char ** argv){
  char ***tabla = NULL;
  char **aux = NULL;
  char chr, aux_char[1];
  int i, j, k, aa, bb;
  int count_lines = 0;
  int num_simbolos;
  int max_linea;
  int num_estados;
  int ini, fin;
  char* alfabeto = NULL;
  int estado_actual, estado_final;

  if(argc!=2){
    return -1;
  }

  char *entrada = NULL;
  //printf("%ld", strlen(argv[1]));
  entrada = (char *)malloc(strlen(argv[1])*sizeof(char));
  strcpy(entrada, argv[1]);

  FILE *automata = fopen("automata_descr.txt", "r");
  if(automata == NULL){
    printf("Autómata NO descrito\n");
    return -1;
  }

  //Cargar la tabla del Autómata
  chr = getc(automata);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        //take next character from file.
        chr = getc(automata);
    }
  fclose(automata);
  automata = fopen("automata_descr.txt", "r");

  fgets(aux_char, 10, (FILE *)automata);
  num_simbolos = atoi(aux_char) + 1;
  max_linea=num_simbolos+4;// - para estados lambda
  printf("num_simbolos %d\n", num_simbolos);

  fgets(aux_char, 10, (FILE *)automata);
  num_estados = atoi(aux_char);
  printf("num_estados %d\n", num_estados);

  fgets(aux_char, 10, (FILE *)automata);
  ini = atoi(aux_char);
  printf("ini %d\n", ini);

  fgets(aux_char, 10, (FILE *)automata);
  fin = atoi(aux_char);
  printf("fin %d\n", fin);

  char *buffer = NULL;
  buffer = (char *)calloc(sizeof(char),max_linea);
  if(buffer == NULL){
    printf("Error al reservar memoria a buffer");
    return -1;
  }

  alfabeto = (char *)calloc(sizeof(char),num_simbolos);
  if(alfabeto == NULL){
    printf("Error al reservar memoria al alfabeto");
    return -1;
  }

  fgets(buffer, max_linea, (FILE *)automata);
  strcpy(alfabeto, buffer);

  printf("alfabeto: %s\n", alfabeto);

  tabla = (char***)malloc(sizeof(char**)*num_estados);
  for(i=0; i<num_estados; i++){
    tabla[i] = (char**)malloc(sizeof(char*)*num_estados);
    for(j=0; j<num_estados; j++){
      tabla[i][j] = (char*)malloc(sizeof(char)*(num_simbolos));
    }
  }

  for(i=0; i<num_estados; i++){
    for(j=0; j<num_estados; j++){
      for(k=0; k<num_simbolos; k++){
        tabla[i][j][k] = '*';
      }
    }
  }

  char buf;
  i=0;
  while(fgets(buffer, max_linea, automata)){
    printf("buffer lee %s\n", buffer);
    buf = buffer[0];
    estado_actual = atoi(&buf);
    printf("estado actual %d\n", estado_actual);
    buf = buffer[1];
    estado_final = atoi(&buf);
    printf("estado final %d\n", estado_final);
    i=2;
    j=0;
    //empezamos a coger las letras
    for(i=2; i<num_simbolos+2; i++){
      tabla[estado_actual][estado_final][i-2]=buffer[i];
      //printf("- %c - lo que guarda %c\n", buffer[i], tabla[estado_actual][estado_final][i-2]);
    }
  }

  // for(i=0; i<4; i++){
  //   for(j=0; j<4; j++){
  //     printf("%c \n", tabla[i][j][0]);
  //   }
  // }
  //
  // for(i=0; i<4; i++){
  //   for(j=0; j<4; j++){
  //     printf("%c \n", tabla[i][j][1]);
  //   }
  // }

  //Comprobamos que la entrada esté determinada por  el autómata

  int estado = ini, *nuevo_estado = NULL, *estado_destino = NULL;
  int l, p;
  int flag = 1;
  nuevo_estado = (int*)malloc(sizeof(int)*num_estados);
  estado_destino = (int*)malloc(sizeof(int)*num_estados);
  for(i=0; i<num_estados; i++){
    nuevo_estado[i]=1;
  }
  for(i=0; i<num_estados; i++){
    estado_destino[i]=1;
  }
  nuevo_estado[ini]=0;
  for(i=0; i<strlen(argv[1]);i++){//leemos la entrada
    printf("----- Leo %c \n", entrada[i]);
    for(l=0; l<num_estados;l++){
      if(nuevo_estado[l] == 0){
        estado = l;
        // nuevo_estado[l]=1;
        //estado_destino[l]=1;
        for(j=0; j<num_estados;j++){
          for(k=0; k<num_simbolos;k++){//posibles transiciones
            printf("estado actual%d\n", estado);
            // printf("tabla[%d][%d][%d]%c " ,estado, j, k, tabla[estado][j][k]);
            if(tabla[estado][j][k]==entrada[i]){
              printf("estado siguiente posible%d\n", j);
              // flag = 0;
              estado_destino[j]=0;

              encuentra_lambdas_recursiva(tabla, estado_destino, num_estados, j);

              // for(aa=0; aa<num_estados;aa++){
              //     // printf("ha entrado en el for, iteracion %d\n", aa);
              //     // printf("la tabla contiene %c\n", tabla[j][aa][2]);
              //     // printf("tabla[%d][%d][%d]%c " ,estado, j, k, tabla[estado][j][k]);
              //     if(tabla[j][aa][2]=='-'){
              //       printf("estado siguiente posible por lambda %d\n", aa);
              //       // flag = 0;
              //       estado_destino[aa]=0;
              //     } /*else if(tabla[estado][j][k]=='-'){
              //       printf("estado siguiente posible por lambdas%d\n", j);
              //       // flag = 0;
              //       estado_destino[j]=0;
              //     }*/
              // }

            }
          }
        }
        // if(flag == 0){
        //   flag = 1;
        //   break;
        // }
      }
      if(l == num_estados-1){
        for(p=0; p<num_estados; p++){
          nuevo_estado[p]=estado_destino[p];
          estado_destino[p]=1;

        }
      }
    }
      if(entrada[i+1] == '\0'){
        if(nuevo_estado[fin]==0){
          printf("Palabra aceptada\n");
          return 0;
        }
      }
    }


/*
  int estado = 0, nuevo_estado = 0;
  for(i=0; i<strlen(argv[1]); i++){
    printf("Leo %c \n", entrada[i]);
    for(j=0; j<num_estados; j++){
      for(k=0; k<)
      if(tabla[estado][j]==entrada[i]){
        nuevo_estado = j;
        break;
      }
    }
    estado = nuevo_estado;
    if(entrada[i+1] == '\0'){
      break;
    }
  }

  if(estado == 2){
    printf("Palabra aceptada\n");
    return 0;
  */
  printf("Palabra NO aceptada\n");
  return -1;
}
