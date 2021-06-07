#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
int dataIndex;
int n=0;
char buffer[1024];
int i;

dataIndex = 0;
printf("How many members ?\n");
scanf("%d", &n);
char *Data[n];

for(dataIndex = 0; dataIndex < n; dataIndex++) {
    printf("Member %d name\n",dataIndex+1);
    scanf( "%s" , buffer );
    if ( strcmp( "end" , buffer ) == 0 ) break;
    Data[dataIndex] = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(Data[dataIndex] ,buffer);
}

printf( "----\n" );

for ( i = 0 ; i < dataIndex ; i++ ) {
    printf( "%s\n" , Data[i] );
    free(Data[i]);
}
}