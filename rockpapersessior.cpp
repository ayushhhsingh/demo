#include<iostream>
#include<ctime>

char getUserChoice();
char getComputerChoice();
void showChoice(char choice);
void chooseWinner(char player,char computer);
int main(){
    char player;
    char computer;
    player= getUserChoice();
    std::cout<<"your choice: ";
    showChoice(player);

    computer= getComputerChoice() ;
    std::cout<<"computer's choise: ";
    showChoice(computer);
    chooseWinner(player,computer);

    return 0;
}
char getUserChoice(){
    char player;
    do
    {
       std::cout<<"ROCK PAPER SCISSORS GAME!!!!!\n";
       std::cout<<"-----------------------------\n";
       std::cout<<"choose R for rock\n";
       std::cout<<"choose P for paper\n";
       std::cout<<"choose s for scissors\n";
       std::cin>>player;
       std::cout<<player<<'\n';
    } while (player!='r'&&  player != 'p'&& player !='s');
    
    return player;

}
char getComputerChoice(){
    srand(time(0));
    int num= rand() % 3 + 1;
    switch (num)
    {
    case 1:
           return 'r';
       
    
     case 2: return 'p';
        
        
    case 3:  return 's';
    }
    
   return 0;
}
 void showChoice(char choice){
   
  switch (choice)
    {
    case 'r':
        std::cout<<"ROCK\n";
        break;
    case 'p':
        std::cout<<"PAPER\n";
            break;
    case 's':
        std::cout<<"SCISSORS\n";
         break;
    
    }

}
void chooseWinner(char player, char computer){
    switch (player)
    {
    case 'r': if (computer=='r'){
        std::cout<<"its a tie\n";
        
    }
   else if(computer=='p'){
    std::cout<<"you lose\n";
   }
    else std::cout<<"YOU WIN!!!!!!!!!!\n";
//"YOU WIN!!!!!!!!!!
        break;
    
    case 'p':if (computer=='r'){
        std::cout<<"YOU WIN!!!!!!!!!!\n";
        
    }
   else if(computer=='p'){
    std::cout<<"its a tie\n";
   }
   else std::cout<<"you lose\n";
        break;
    case 's':if (computer=='r'){
        std::cout<<"you lose\n";
        
    }
   else if(computer=='p'){
    std::cout<<"YOU WIN!!!!!!!!!!\n";
   }
   else std::cout<<"its a tie\n";
    
    }

}