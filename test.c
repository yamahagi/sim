#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include "include/common.h"
#include "include/oc_sim.h"
static char *log_file = (char*) "ika.log";
static char *sfile;
FILE *err_fp;
static void configure(int argc, char **argv);
static void print_usage(char*);
static void register_segv_handler(void);
static void prom_set(int argc, char **argv);
static void open_log_file(void);
uint32_t prom[ROMNUM];
#define LINE_LENGTH_MAX 256 // １行の長さの上限

int main(int argc, char **argv, char **envp){
/*
int b = 0b00000000011001000000000000000001;
int a = get_opcode(b);
int c = get_rsi(b);
int d = get_rti(b);

printf("%d",a);
printf("%d",c);
printf("%d",d);
*/
configure(argc,argv);
register_segv_handler();
        open_log_file();
        prom_set(argc, argv);
int opcode0 = get_opcode(prom[0]);
int rsi0 = get_rsi(prom[0]);
int rti0 = get_rti(prom[0]);
int rdi0 = get_rdi(prom[0]);
int imm0 = get_imm(prom[0]);
printf("opcode %d",opcode0);
printf("rsi %d",rsi0);
printf("rti %d",rti0);
printf("rdi %d",rdi0);
printf("imm %d\n",imm0);

int opcode1 = get_opcode(prom[1]);
int rsi1 = get_rsi(prom[1]);
int rti1 = get_rti(prom[1]);
int rdi1 = get_rdi(prom[1]);
int imm1 = get_imm(prom[1]);
printf("opcode %d",opcode1);
printf("rsi %d",rsi1);
printf("rti %d",rti1);
printf("rdi %d",rdi1);
printf("imm %d\n",imm1);

}


static void open_log_file(void) {
#ifdef LOG_FLAG
        log_fp = fopen(log_file, "w");
        if (log_fp==NULL) {
                perror("fopen log_file");
                exit(1);
        }
        fprintf(log_fp, "running %s\n", sfile);
        fprintf(log_fp, "cnt(hex).[pc(hex)]\n");
#endif
}

void segv_handler(int a){
};
static void register_segv_handler(void) {
        struct sigaction sa;
        sa.sa_handler = segv_handler;
        if (sigaction(SIGSEGV, &sa, NULL) != 0) {
                perror("sigaction");
                exit(1);
        }

}
/*
static void prom_set(int argc, char **argv) {
        int  ret;
	int fp;
	FILE *fd;
	int n = 0;
	char line[LINE_LENGTH_MAX];
        if (argc < 2) {
                print_usage(argv[0]);
                exit(1);
        }
	printf("5");
        sfile = argv[1];
        fd = fopen(sfile, O_RDONLY);
        if (fd<0) {
                perror("open @ prom_set");
                exit(1);
        }
	while(fgets(line, LINE_LENGTH_MAX, fd)){
		prom[n] = strtol(line, NULL, 2);
		n++;
		printf("%d",n);
	}
        
	ret = read(fd, prom, ROMNUM*4);
        if (ret<0) {
                perror("read");
                exit(1);
        }
	prom[ret] = '\0';
        printf("read:%d - %d\n", ret,prom);
        fclose(fd);
}
*/


static void prom_set(int argc,char **argv) {

FILE *fp;
    char *filename = argv[1];
    char readline[32] = {'\0'};
	int n = 0;

    /* ファイルのオープン */
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
        exit(EXIT_FAILURE);
    }

    /* ファイルの終端まで文字を読み取り表示する */
    while ( fgets(readline, 100, fp) != NULL ) {
	printf("%s\n",readline);
        prom[n] = strtol(readline,NULL,2);
	printf("prom[%d]\n",n);
	n++;
    }

    /* ファイルのクローズ */
    fclose(fp);


}

/*
static void prom_set(int argc, char **argv) {
        int fd, ret;
        if (argc < 2) {
                print_usage(argv[0]);
                exit(1);
        }
        sfile = argv[1];
        fd = open(sfile, O_RDONLY);
        if (fd<0) {
                perror("open @ prom_set");
                exit(1);
        }
        ret = read(fd, prom, ROMNUM*4);
        if (ret<0) {
                perror("read");
                exit(1);
        }
        close(fd);
}
*/
static void configure(int argc, char **argv) {
        int opt;
        err_fp = stderr;
        if (argc < 2) {
                print_usage(argv[0]);
                exit(1);
        }
        sfile = argv[1];
        if (sfile==NULL) {
                warning("Not Found: source file\n");
                exit(1);
        }

        while ((opt = getopt(argc, argv, "l:")) != -1) {
                switch (opt) {
                        case 'l' :
                                log_file = optarg;
                                break;

                        default :
                                print_usage(argv[0]);
                                exit(1);
                                break;
                }
        }
}

#define print_option(fmt, ...) \
        warning("\t"fmt"\n", ##__VA_ARGS__)
static void print_usage(char*name) {
        warning("\n");
        warning("USAGE\t: %s $file [$option]\n", name);
        warning("OPTIONS\t:\n");
        print_option("-l [$log_file]\t: output log if LOG_FLAG macro is defined");
        warning("\n");
}
#undef print_option
