#pragma once
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory_resource>
#include <ostream>
#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <mutex>
#include <thread>


const int MAX_CONNECTIONS=5;
std::vector<int> Clients;
std::mutex Mux;

void ErrorChecker(int Rval,std::string Msg){
  if(Rval==-1){
    std::cout<<"Error while "<<Msg<<"  Error number "<<errno<<std::endl;
    std::exit(Rval);
  }
  return;
}

void ReceveAndSendMsgOnNewThread(int Socketfd);
void ReceveAndSendMsg(int Socketfd);
void RemoveClient(int sockfd);
void LogsMaintain(int Socketfd,std::string Messg);

void BroadcastMsg(int SenderSocketAddr,char* Msg){
  std::lock_guard<std::mutex>lock(Mux);
  for(const auto& cl:Clients){
    if(cl==SenderSocketAddr){
      continue;
    }
  ErrorChecker(send(cl,Msg,sizeof(Msg),0),"Sending messags to Clients ");
  
  }

}

void ReceveAndSendMsg(int Socketfd){

  char BUFFER[1020];
  while(true){
    
    size_t Bytesrecv=recv(Socketfd,BUFFER,sizeof(BUFFER),0);
    ErrorChecker(Bytesrecv, "Receving the message ");
    BUFFER[Bytesrecv]='\0';
    
    if(!std::strcmp(BUFFER,"-Ex11")){
      RemoveClient(Socketfd);
    }
    if(Bytesrecv==0 ){
      RemoveClient(Socketfd);
    }
    BroadcastMsg(Socketfd,BUFFER);
  }
}

void RemoveClient(int sockfd){

  for(auto it=Clients.begin();it!=Clients.end();it++){
    if(*it==sockfd){
      Clients.erase(it);
      break; 
    }
  }
}

void ReceveAndSendMsgOnNewThread(int Socketfd ){
  std::thread t(ReceveAndSendMsg,Socketfd);
  t.detach();
}
