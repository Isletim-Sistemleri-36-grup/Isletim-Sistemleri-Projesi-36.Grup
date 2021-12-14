//***************************************************************************
//@Grup Numarası
	// 36
//@Grup Üyeleri
	//G191210017 Raif AKYOL
	//G191210101 Muhammet Enes VARDAR
	//G191210029 Yavuz ÇELİK
	//G191210071 Yusuf AYDOĞMUŞ
	//G191210011 Emir Can OLĞAÇ
	
//@Teslim tarihi
	//14.12.2021


//**************************************************************

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOKEN_DELIM " \t\r\n"
// SİL #define RESET "\e[0m"
#define BUFF_SIZE 80    //Komut satırına girilen satırın 80 karakter sınırını taşıması adına tanımlandı
#define TK_BUFF_SIZE 64
#define processnumber 30

//Renk Kodları
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"

#include "shell.h"

char *read_line() {  //shell'den girilen satırın okuma işlemini gerçekleştiriyor.
  int buffsize = BUFF_SIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * buffsize); //satırı dinamik bir bellek bölgesi ayırdık
  int c;
 
  if (!buffer) { //yer ayrılmadıysa hata döndür
    fprintf(stderr, "%sAllocation error%s\n", RED, reset);
    exit(EXIT_FAILURE);
  }

  while (1) { //her bir satırı oku ve belirli karakterlere geldiğinde \0 ekle ve bu satırı döndür
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
	lineLength++;   
  }
}
