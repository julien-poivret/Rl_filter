#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	long double R;
	long double L;
	long double Fc;
        int init;
}RL_filter_data;

/* 
     RL filter. fc = R/2piL
     two values must be provided at minimum,
     the third must be initialized with a zero...
     the data base memory is then writed with the correct matching values.
*/

int RL_Filter(long double R, long double L, long double Fc,RL_filter_data* data){
	if(R==0.0 && L && Fc){
                data->R = Fc/(2*M_PI*L);
                data->L = L;
                data->Fc = Fc;
                return 1;
	}	
        if(L==0.0 && R && Fc){
		data->L = R/(Fc*2*M_PI);
                data->R = R;
                data->Fc = Fc;
                return 1;
	}
	if(Fc==0.0 && L && R){
		data->Fc = R/(2*M_PI*L);
                data->R = R;
                data->L = L;
                return 1;
	}
		fprintf(stderr,"\33[1;1H\33[2J\33[31mError, at least 2 non null values  must be provided at minimum !\33[0m\n");
		exit(3);
	return 0;

}
	
// Data preprocessing for arguments handling.
void format_argv(char* argv[],RL_filter_data* data){
	data->R = atof(argv[1]);
	data->L = atof(argv[2]);
	data->Fc = atof(argv[3]);
	data->init = 1;
}

int main(int argc,char* argv[]){
	// Arguments handling condition.

	char help[500]="\33[34mRL low Pass filter: \33[33m(let only the low frequency (like audio vs Radio frequence) when R is in parallel and L in series with in the power supply .\n"
                       "\33[34mRL hight Pass filter: \33[33m(let only the High frequency passing) when R is in series and C in parallel.\n"
                       "\33[34mHelp:\33[33m\n"
                       "               fast, ( 3 cli arguments forever ):  1 Resistance, 2 Inductance, 3 Cut Off Frequency\n"
                       "             --- at least 2 arguments non Null must be provided the last third unknow is feed at 0. ---\33[0m\n"; 
	if(argc==1){
		printf("%s\n",help);
		return EXIT_SUCCESS;
	}else if(argc!=4){
		printf("3 arguments must be provided.\n");				
		return EXIT_FAILURE;
	}
        RL_filter_data RLData = {.init=1};
        format_argv(argv,&RLData);
	RL_Filter(RLData.R,RLData.L,RLData.Fc,&RLData);
	printf("\33[3J\33[34mRL filters:\33[0m\n     \33[3J \33[34mFrequency \33[0mabove or lower \33[33m%6.3Le Hz\33[0m are filtred with \33[34mR:\33[33m%6.3Le Ohm(s) \33[34mL:\33[33m%6.3Le Henry(s) \33[0m\n",RLData.Fc,RLData.R,RLData.L); 
return EXIT_SUCCESS;
}
