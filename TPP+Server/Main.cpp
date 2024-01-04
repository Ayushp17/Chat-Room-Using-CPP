#include "HelperFunc.h"
#include <netinet/in.h>
#include <sys/socket.h>


int main (int argc, char *argv[]) {
  
  if(argc<2){
    ErrorChecker(-1,"Too port number is not given ");
  }

  int Socketfd=socket(AF_INET,SOCK_STREAM,0);
  std::cout<<" || Socket creation   [OK]  "<<std::endl;
  // Server Address 
  struct sockaddr_in ServerAddr,CliAddr;
  ServerAddr.sin_addr.s_addr=INADDR_ANY;
  ServerAddr.sin_port=htons(std::atoi(argv[1]));
  ServerAddr.sin_family=AF_INET;

  socklen_t ClisockSize= sizeof(CliAddr);
  
  //binding
  ErrorChecker(bind(Socketfd, (struct sockaddr *)& ServerAddr, sizeof(ServerAddr)), " Binding ");
  std::cout<<" || Binding  [OK]  "<<std::endl;
  //Listening
  ErrorChecker(listen(Socketfd, MAX_CONNECTIONS), "Listening ");

   std::cout<<" || Listening  [OK]  "<<std::endl;
  
  while (true) {
    
    int ClentFd=accept(Socketfd, (struct sockaddr*)&CliAddr, &ClisockSize);
    ErrorChecker(ClentFd, "Accepting client");
    std::cout<<" || Accepting  [OK]  "<<std::endl;
    Clients.push_back(ClentFd);
    ReceveAndSendMsgOnNewThread(ClentFd); 
  }

  return 0;
}
