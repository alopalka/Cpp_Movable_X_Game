#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void ClearScreen(){
    system("cls");
}

void PrefillBoard(char screen[20][40]){
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            screen[i][j]=' ';
        }
    }
}

void FillBoard(char screen[20][40],char &znak,int x){
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= x; j++){
            if (j == i || j == (x + 1 - i)){
                screen[i][j]=znak; 
            }
        }
    }
}

void PrintBoard(char screen[20][40]){
    for(int i=0;i<20;i++){
        for(int j=0;j<40;j++){
            if(i==0 || i==19){
                cout<<'#';
            }
            else if(j==0 || j==39){
                cout<<'#';
            }
            else{
                cout<<screen[i][j];
            }
        }
        cout<<endl;
    }
}

int MoveUp(char screen[20][40],char &znak,int y_pos){
    for(int y=0;y<20;y++){
        for(int x=0;x<40;x++){
            if(screen[y][x]==znak){
                if(y==1 || y==0){
                    goto end;
                }
                else{
                    screen[y-1][x]=screen[y][x];
                    screen[y][x]=' ';
                }
            }
        }
    }
    y_pos-=1;

    end:
    return y_pos;
}

int MoveDown(char screen[20][40],char &znak,int y_pos){

    for(int y=19;y>0;y--){
        for(int x=0;x<40;x++){
            if(screen[y][x]==znak){
                if(y==18 || y==19){
                    goto end;
                }
                else{
                    screen[y+1][x]=screen[y][x];
                    screen[y][x]=' ';
                }
            }
        }
    }
    y_pos+=1;

    end:
    return y_pos;
}

int MoveRight(char screen[20][40],char &znak,int x_pos){

    for(int x=39;x>0;x--){
        for(int y=0;y<20;y++){
            if(screen[y][x]==znak){
                if(x==39||x==38){
                    goto end;
                }                
                else{
                    screen[y][x+1]=screen[y][x];
                    screen[y][x]=' ';
                }
            }
        }
    }
    x_pos+=1;

    end:
    return x_pos;
}

int MoveLeft(char screen[20][40],char &znak,int x_pos){

    for(int x=0;x<40;x++){
        for(int y=0;y<20;y++){
            if(screen[y][x]==znak){
                if(x==0||x==1){
                    goto end;
                }                
                else{
                    screen[y][x-1]=screen[y][x];
                    screen[y][x]=' ';
                }
            }
        }
    }
    x_pos-=1;

    end:
    return x_pos;
}

void Resize(int x_pos,int y_pos,int n,char screen[20][40],char znak){
    if(n<3 || n>18){
        goto skip;
    }

    int x_pos_old,y_pos_old;
    PrefillBoard(screen);
    FillBoard(screen,znak,n);
    x_pos_old=x_pos;
    y_pos_old=y_pos;
    x_pos=0;
    y_pos=0;
    
    if(x_pos_old>0){
        for(int i=0;i<x_pos_old;i++){
            x_pos=MoveRight(screen,znak,x_pos);
        }
    }
    if(y_pos_old>0){
        for(int i=0;i<y_pos_old;i++){
            y_pos=MoveDown(screen,znak,y_pos);
        }
    }
    skip:
    cout<<endl;
}

int main(){
    char znak;
    int n;
    char screen[20][40];
    int x_pos=0,y_pos=0;

    ClearScreen();
    
    cout<<"Witaj w programiku \n \n";
    cout<<"Wybierz swoj znak z jakie skladac ma sie X: \n";
    cin>>znak;
    cout<<"Podaj poczatkowe rozmiary figury (minimum n=3) (n x n) \nMinimalna wielkosc - 3 Maxymalna wielkosc - 18 \nn: ";
    cin>>n;

    if(n<3 || n>18){
        n=3;
    }

    PrefillBoard(screen);
    FillBoard(screen,znak,n);

    bool k = true;   
    while(k)
    {
        int c = 0;
        ClearScreen();
        PrintBoard(screen);
        cout<<"Aby zwiekszyc lub zmniejszyc figure nacisnij (+) lub (-) . \n";
        cout<<"Aby przesunac figure uzyj do tego strzalek \n";
        cout<<"Aby wyjsc wcisnij 'e' \n";

        switch((c=getch())) {
        case KEY_UP:
            y_pos=MoveUp(screen,znak,y_pos);
            break;
        case KEY_DOWN:
            y_pos=MoveDown(screen,znak,y_pos);
            break;
        case KEY_LEFT:
            x_pos=MoveLeft(screen,znak,x_pos);
            break;
        case KEY_RIGHT:
            x_pos=MoveRight(screen,znak,x_pos);
            break;
        case '+':
            n+=1;
            Resize(x_pos,y_pos,n,screen,znak);
            break;
        case '-':
            n-=1;
            Resize(x_pos,y_pos,n,screen,znak);
            break;

        case 'e':
            k = false;
            break;
        default:
            break;
        }

    }

    return 0;
}