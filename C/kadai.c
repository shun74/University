#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>｜
// 1 2 17 227 503 1009
#define n 503

struct cell *p_hashtable[n];
struct cell *a_hashtable[n];

struct cell{
    char *p_code;
    char *address;
    struct cell *p_next;
    struct cell *a_next;
};

int hash(char *key){
    int hashval = 0;
    while(*key!='\0'){
        hashval += *key;
        key++;
    }
    return abs(hashval) % n;
}

void add(char *post_code, char *address){
    int p_hash, a_hash;
    p_hash = hash(post_code);
    a_hash = hash(address);
    struct cell *ptr;
    ptr = malloc(sizeof(struct cell));
    ptr->p_code = malloc(sizeof(char)*(strlen(post_code)+1));
    ptr->address = malloc(sizeof(char)*(strlen(address)+1));
    strcpy(ptr->p_code, post_code);
    strcpy(ptr->address, address);
    ptr->p_next = p_hashtable[p_hash];
    p_hashtable[p_hash] = ptr;
    ptr->a_next = a_hashtable[a_hash];
    a_hashtable[a_hash] = ptr;
    return;
}

struct cell *find_address(char *address){
    struct cell *p;
    int hashval;
    hashval = hash(address);
    p = a_hashtable[hashval];

    while(p!=NULL){
        if(strcmp(address,p->address)==0){
            return p;
        }
        p = p->a_next;
    }
    return NULL;
}

struct cell *find_postcode(char *post_code){
    struct cell *p;
    int hashval;

    hashval = hash(post_code);
    p = p_hashtable[hashval];

    while(p!=NULL){
        if(strcmp(post_code,p->p_code)==0){
            return p;
        }
        p = p->p_next;
    }
    return NULL;
}

void hash_info(){
    int i, length;
    int p_hashtable_count[n];
    int a_hashtable_count[n];
    int sum=0;
    struct cell *p,*a;

    for(i=0; i< n; i++){
        length = 0;
        p = p_hashtable[i];
        while(p!=NULL){
            length++;
            p = p->p_next;
        }
        // printf("p_hashtable [%d] : %d\n",i,length);
        p_hashtable_count[i] = length;
        sum += length;
    }
    for(i=0; i< n; i++){
        length = 0;
        a = a_hashtable[i];
        while(a!=NULL){
            length++;
            a = a->a_next;
        }
        // printf("a_hashtable [%d] : %d\n",i,length);
        a_hashtable_count[i] = length;
    }
    float average = (float)sum/(float)n;
    float p_variance,a_variance;
    for(i=0; i<n; i++){
        p_variance += (average-p_hashtable_count[i])*(average-p_hashtable_count[i]);
        a_variance += (average-a_hashtable_count[i])*(average-a_hashtable_count[i]);
    }
    p_variance = sqrtf(p_variance);
    a_variance = sqrtf(a_variance);
    printf("Average: %f\n",average);
    p_variance = p_variance/(float)average;
    a_variance = a_variance/(float)average;
    printf("Variance: p_hash %f, a_hash %f\n",p_variance,a_variance);
}


int main(int argc, char *argv[]){
    printf("Hash mod:%d\n",n);
    struct timeval start,end;
    char post_code[256];
    char address[256];
    struct cell *ptr;
    char word[256];
    
    FILE *fp;
    fp = fopen("postal.txt","r");
    while(fscanf(fp,"%s %s",post_code,address)!=EOF){
        add(post_code, address);
    }
    fclose(fp);

    hash_info();

    if(argc>1){
        fp = fopen(argv[1],"r");
        gettimeofday(&start,NULL);
        while(fscanf(fp,"%s",word)!=EOF){
            // printf("%s\n",word);
            if(word[0]>='0'&&word[0]<='9'){
                ptr = find_postcode(word);
                if(ptr==NULL) continue;
                // printf("->%s\n",ptr->address);
            } else {
                ptr = find_address(word);
                if(ptr==NULL) continue;
                // printf("->%s\n",ptr->p_code);
            }
        }
        gettimeofday(&end,NULL);
        printf("Search time = %lf\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)*1.0E-6);
        fclose(fp);
    } else {
        while(scanf("%s", word) != EOF){
            if(word[0]>='0'&&word[0]<='9'){
                ptr = find_postcode(word);
                if(ptr==NULL) continue;
                printf("->%s\n",ptr->address);
            } else if(word[0]=='q') {
                break;
            } else {
                ptr = find_address(word);
                if(ptr==NULL) continue;
                printf("->%s\n",ptr->p_code);
            }
        }
    }
    return 0;
}