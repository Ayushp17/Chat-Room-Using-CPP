#include "Clients_Utilites.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <sys/socket.h>

int main (int argc, char *argv[]) {
  
  if(argc>3){
    std::cout<<"Port number or IP address not given ";
    std::exit(1);
  }

  
  int Socketfd=socket(AF_INET, SOCK_STREAM, 0);
  ErrorChecker(Socketfd ,"Socket Created");
  std::cout<<" Socket [ OK ] " <<std::endl;

  struct sockaddr_in Cliaddr;
  Cliaddr.sin_port=htons(atoi(argv[1]));
  Cliaddr.sin_addr.s_addr=inet_addr(argv[2]);
  Cliaddr.sin_family=AF_INET;

  ErrorChecker(connect(Socketfd,(struct sockaddr *)&Cliaddr , sizeof(Cliaddr)), "conected to server ");
  
  std::cout<<" Connected To Server  [ OK ] " <<std::endl;
  system("clear");
  ServerRulesAndHelp();
  
  while(true){
    ReceveFromServerOnNewThread(Socketfd);
    SendToServer(Socketfd);
  }
  return 0;
}
