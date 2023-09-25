#include <stdio.h>
#include <unistd.h>

int main(){
  if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
    printf("fail\n");
  }else{
    printf("success\n");
  }
}
