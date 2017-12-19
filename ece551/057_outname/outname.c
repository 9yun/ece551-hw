#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char *outputfile=strdup(inputName);
  outputfile=realloc(outputfile,(strlen(inputName)+8)*sizeof(*outputfile));
  outputfile=strcat(outputfile,".counts");
  return outputfile;
}
