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

#ifndef SHELL_H
#define SHELL_H

static char* currentPath;//Mevcut çalışma dizinini tutuyor
static int lineLength=0;
static int ProcessCount=0;

char *read_line(); //Girilen satırı okuyan ve döndüren fonksiyon
char **split_line(char *);//kendisine gönderilen satırı ayırıcı karakterlere göre ayırıp bunları döndüren,argümanları tutan fonksiyon
int execute(char **);//kendisine gönderilen argümanlar doğrultusunda yapması gereken işleri tamamlayan fonksiyon
int builtin_exit( );//Shell'den çıkmayı sağlayan fonksiyon
int *process;
int showpid();
int builtin_cd(char **args);
int builtin_help();
int args_length(char **args);
void Prompt();


#endif
