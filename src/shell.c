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


int showpid(){ //Execute satırında her forklanmadan sonra oluşturulan (yani kabuk tarafından üretilmiş) processlerin id'lerini göstermekte
	printf("\n%s**************************************************%s\n",YEL,reset);
	printf(" %s processes created by shell %s\n", BLU,reset);
	//printf("%d",Shellpid);
	for(int i=0;i<ProcessCount;i++) 
	 printf("%d-) %d\n",i+1,process[i]);
 	printf("\n%s**************************************************%s\n",YEL,reset);
		return 1;
		 
}

int builtin_exit() { //kullanıcı shell'e exit yazdığında çıkış sağlanacak
	printf("%sFile was closed by user request with Exit command%s\n", RED, reset);
  return 0;
}

int builtin_help() //kullanıcı shell'e help yazdığında çalışacak olan fonksiyon , built-in komutları listelemekte
{
	
		fprintf(stderr,"\n*******************\n"
				"Supported Commands:\n1. showpid\n2. help\n3. cd\n4.exit"
				"\n*******************\n\n");	
	return 1;
}
int builtin_cd(char **args)//kullanıcı shell'e cd yazdığında ilgili kontroller sağlandıktan sonra mevcut konumunu değiştirmesi sağlandı.
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "%sPlease enter a path to cd%s\n", RED, reset);
	}
	else
	{
		if(chdir(args[1]) > 0)//Dizin değiştirme "chdir" fonksiyonu ile yapıldı
		{
			perror("ERROR\n");			
		}
	}
	return 1;
}

char **split_line(char * line) { //kendisine gönderilen satır parametresini parçalayan,bölen ve bu parçaları döndüren fonksiyon
	int buffsize = TK_BUFF_SIZE, position = 0; //
	char **tokens = malloc(buffsize * sizeof(char *));//parçalar için ek bir bellek alanı oluşturuldu 
	char *token;

  if (!tokens) {//eğer  parçalar için oluşturulan ek bellek alanında sıkıntı varsa hata döndürüldü ve fonksiyon başarısız olarak sonlandırıldı.
    fprintf(stderr, "%sAllocation error%s\n", RED, reset);
    exit(EXIT_FAILURE);
  }
  
  token = strtok(line, TOKEN_DELIM); //burada strtok fonksiyonu ile satırlar ilgili ayırıcı karakterlere bölümlendirildi.
									 //her ayırıcı karakter bölümünü NULL'ile sonlandırıp strtok fonksiyonunu besledik.
  while (token != NULL) {			//daha böldüğü satırları döndürecek
    tokens[position] = token;
    position++;

    if (position >= buffsize) {
      buffsize += TK_BUFF_SIZE;
      tokens = realloc(tokens, buffsize * sizeof(char * ));

      if (!tokens) {
        fprintf(stderr, "%sAllocation error%s\n", RED, reset);
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, TOKEN_DELIM);
  }
  tokens[position] = NULL;

  return tokens;
}

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

int execute(char **args) { //kendisini gönderilen parametreleri işleyen  fonksiyon
  int cpid;
  int status;
	//**Builtin kısmı
  if (strcmp(args[0], "exit") == 0||atoi(args[0])==4) {
    return builtin_exit();
  }
    else if (strcmp(args[0], "cd") == 0||atoi(args[0])==3) {
    return builtin_cd(args);
  }
    else if (strcmp(args[0], "help") == 0||atoi(args[0])==2) {
    return builtin_help();
  }
   else if (strcmp(args[0], "showpid") == 0) {
	  return showpid(); 
	}
//*****
  cpid = fork(); //Ebevyn process fork ile kendi kopyasını oluşturmuş oldu
  
  if (cpid == 0) {//Eğer oluşturulmış processin fork değeri 0'a eşitse bu yavru processtir.
    if (execvp(args[0], args) < 0)//gönderilen argümanların ilki her zaman komutu barındırdığından dizinin ilk elemanı ve argümanları olarak execvp'ye gönderildi
	{
		printf("%sCommand not found: %s", RED, reset);//eğer fonksiyon sonucu 0'dan küçük ise böyle bir komutun olmadığı ifade edildi.
		printf("%s\n", args[0]);
	}
    exit(EXIT_FAILURE); //ve execute fonksiyonu başarısız olarak sonlandırıldı.

  } else if (cpid < 0)//eğer oluşturulmuş process'in fork değeri 0'dan küçük ise fork işlenirken hata oluşmuş demektir 
    printf(RED "Error forking"
      reset "\n");
   else { //burada oluşturulmuş yavru processlerin id'leri bir process dizisinde tutuldu.Showpid kısmında listelenmesi adına
	  process[ProcessCount]=cpid;
    waitpid(cpid, & status, WUNTRACED);//zombi processlerin oluşmasını engellemek adına ebevyn'in yavrunun sonlanması anına kadar bekletilmesi işlemi gerçekleştirildi.
  }
  ProcessCount++;
  return 1;
}
