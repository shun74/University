#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *Data[100];
int dataIndex;




int main() {
char buffer[1024];
int i;

dataIndex = 0;

while( 1 ) {
    scanf( "%s" , buffer );
    if ( strcmp( "end" , buffer ) == 0 ) break;
    Data[dataIndex] = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(Data[dataIndex] ,buffer);

    dataIndex = dataIndex + 1;
}

printf( "----\n" );

for ( i = 0 ; i < dataIndex ; i++ ) {
    printf( "%s\n" , Data[i] );
    free(Data[i]);
}
}