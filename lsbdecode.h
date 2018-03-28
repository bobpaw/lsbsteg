#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef LSB_DECODE_H_
#define LSB_DECODE_H_

// Filetypes
#define LSB_DECODE_FILETYPE_BMP 1

static int lsb_error = 0;
char * lsb_decode_err (void) {
  char * output = NULL;
  switch (lsb_error) {
  case 1:
    output = "Invalid number of LSB";
    break;
  case 2:
    output = "File is not of specified type";
    break;
  case 3:
    output = "Invalid type";
    break;
  case 4:
    output = "No file specified";
    break;
  case 5:
    output = "Specified file does not exist";
    break;
  default:
    output = "Unknown Error";
    break;
  }
  return output;
}

char * lsb_decode (char * filename, const int type, int num_lsb) {
  if (filename == NULL || filename == "") {
    lsb_error = 4;
    return NULL;
  }
  if (access(filename, R_OK) == -1) {
    lsb_error = 5;
    return NULL;
  }
  if (type != LSB_DECODE_FILETYPE_BMP) {
    lsb_error = 3;
    return NULL;
  }
  if (num_lsb < 1 || num_lsb > 7) {
    lsb_error = 1;
    return NULL;
  }
  int realsize = 0;
  int begoffset = 0;
  char * bitmap = NULL;
  FILE * bmpstream = fopen(filename, "r");
  char encoding[2] = "";
  char * data = NULL;
  char letter = 0;
  int size = 0;
  fread(encoding, 1, 2, bmpstream);
  if (!(encoding[0] == 'B' && encoding[1] == 'M')) {
    lsb_error = 2;
    return NULL;
  }
  // Get size of BMP file (specified in file itself).
  fread(&size, 1, 4, bmpstream);
  // Throw away application-specific values
  fseek(bmpstream, 10, SEEK_SET);
  fread(&begoffset, 1, 4, bmpstream);
  fseek(bmpstream, begoffset, SEEK_SET);
  bitmap = malloc(size);
  memset(bitmap, 0, size);
  realsize = fread(bitmap, 1, size, bmpstream);
  fclose(bmpstream);
  data = malloc((int)realsize/(8/num_lsb)+1);
  memset(data, 0, (int)realsize/(8/num_lsb)+1);
  for (int i = 0, dloc = 0; i < realsize/num_lsb; i++) {
    if ((i+1) % 8/num_lsb == 0 && i != 0) {
      data[dloc] = letter;
      dloc++;
      letter = 0;
    } else {
      if (bitmap[i] & ((1 << num_lsb) - 1) != 0) {
        letter |= (bitmap[i] & ((1 << num_lsb) - 1)) << 7 - i%(8/num_lsb);
      }
    }
  }
  free(bitmap);
  return data;
}

#endif // LSB_DECODE_H_
