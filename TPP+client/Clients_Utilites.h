#include <cstddef>
#include <sys/socket.h>
#include <iostream>
#include<arpa/inet.h>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <cstdlib>

void ErrorChecker(int Rval,std::string Msg){
  if(Rval==-1){
    std::cout<<"Error while "<<Msg<<"  Error number "<<errno<<std::endl;
    std::exit(Rval);
  }
  return;
}

void CheckForExit(char *Msg);
void ServerRulesAndHelp();

void SendToServer(int Sockfd){
  char Buffer[1020];

  while(true){
  std::cout<<"\nMe  ::  ";
  std::cin.getline(Buffer,1020);
  CheckForExit(Buffer);
  size_t Bytes_Send=send(Sockfd,Buffer,sizeof(Buffer),0);
  }
}

void ReceveFromServer(int sockfd){
  char BUFFER[1020];
  
  while(true){

    size_t AmmountReceved=recv(sockfd,BUFFER,sizeof(BUFFER),0);
    ErrorChecker(AmmountReceved, "REceving from server ");
    if(AmmountReceved==0){
      break;
    }
    
    std::cout<<"\nUser  ::  "<<BUFFER<<std::endl;
    std::memset(BUFFER,'\0',1020);
  }
  close(sockfd);
}
void ReceveFromServerOnNewThread(int sockfd){

  std::thread t(ReceveFromServer,sockfd);
  t.detach();
}

void CheckForExit(char *Msg){
 int ChkRval= std::strcmp(Msg,"-Ex11");
   if( 0 == ChkRval){
     std::cout<<"Exiting Server [ OK ]"<<std::endl;
    std::exit(0);
   }
   return;
}

void ServerRulesAndHelp(){
  std::cout<<"  TO Exit from server use -Ex11"<<std::endl;
  std::cout<<" Please be civil to all the members of Server "<<std::endl;
  std::cout<<" Enjoy your time on Server "<<std::endl;
  std::cout<<"\n(:-D)"<<std::endl;
}
