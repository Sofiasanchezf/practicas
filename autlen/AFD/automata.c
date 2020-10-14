#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){
  char tabla[4][4];
  tabla[0][1]='a';
  tabla[1][2]='b',
  tabla[2][1]='a';
  tabla[2][3]='b';
  tabla[3][1]='a';

  if(argc!=2){
    return -1;
  }

  char entrada[500];
  strcpy(entrada, argv[1]);

  int i, j;
  int estado = 0, nuevo_estado = 0;
  for(i=0; i<500; i++){
    printf("Leo %c \n", entrada[i]);
    for(j=0; j<4; j++){
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
