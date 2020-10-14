#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char ** argv){
  char **tabla = NULL;
  char chr;
  int i, j;
  int count_lines = 0;

  if(argc!=2){
    return -1;
  }

  char *entrada = NULL;
  printf("%ld", strlen(argv[1]));
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

  char *buffer = NULL;
  buffer = (char *)calloc(sizeof(char),count_lines);
  if(buffer == NULL){
    printf("Error al reservar memoria a buffer");
    return -1;
  }

  tabla = (char**)malloc(sizeof(char*)*count_lines);
  for(i=0; i<count_lines; i++){
    tabla[i] = (char*)malloc(sizeof(char)*count_lines);
  }

  i=0;
  while(fgets(buffer, (count_lines*2), (FILE *)automata)){
    strcpy(tabla[i], buffer);
    i++;
  }

  //Comprobamos que la entrada esté determinada por  el autómata
  int estado = 0, nuevo_estado = 0;
  for(i=0; i<strlen(argv[1]); i++){
    printf("Leo %c \n", entrada[i]);
    for(j=0; j<count_lines; j++){
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
  }
  printf("Palabra NO aceptada\n");
  return -1;
}
