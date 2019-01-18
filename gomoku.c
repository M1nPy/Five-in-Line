#include<stdio.h>
#define MASU 8
#define WIN 5

int hantei(int ban[MASU][MASU],int row,int col,int npc,int npc_date[8][2]){

    int row_co1=0,col_co1=0,diagR_co1=0,diagL_co1=0,row_co2=0,col_co2=0,diagR_co2=0,diagL_co2=0;
    int diagL_sum,diagR_sum,row_sum,col_sum;

    // 1 縦
    for(int i=col+1;ban[row][i]==1 && i<MASU;i++){
        col_co1++;
    }

    for(int i=col-1;ban[row][i]==1 && i>=0;i--){
        col_co2++;
    }

    // 2 横
    for(int i=row+1;ban[i][col]==1 && i<MASU;i++){
        row_co1++;
    }

    for(int i=row-1;ban[i][col]==1 && i>=0;i--){
        row_co2++;
    }

    // 3 右斜
    for(int x=row+1,y=col+1;ban[x][y]==1 && x<MASU && y<MASU;x++,y++){
        diagR_co1++;
    }

    for(int x=row-1,y=col-1;ban[x][y]==1 && x>=0 && y>=0;x--,y--){
        diagR_co2++;
    }
    
    // 4 左斜
    for(int x=row+1,y=col-1;ban[x][y]==1 && x<MASU && y>=0;x++,y--){
        diagL_co1++;
    }

    for(int x=row-1,y=col+1;ban[x][y]==1 && x>=0 && y<MASU;x--,y++){
        diagL_co2++;
    }

    diagL_sum=diagL_co1+diagL_co2;
    diagR_sum=diagR_co1+diagR_co2;
    row_sum=row_co1+row_co2;
    col_sum=col_co1+col_co2;

    if(row_sum>=WIN-1 || col_sum>=WIN-1 || diagR_sum>=WIN-1 || diagL_sum>=WIN-1)
        return 1;

    //01 col 23 row 45 diagR 67 diagL

    if(npc==0){
        
        if(col_sum>=WIN-4){
        npc_date[0][0]=row;
        npc_date[0][1]=col+col_co1+1;
        npc_date[1][0]=row;
        npc_date[1][1]=col-col_co2-1;
        return 10;
        }

        else if(row_sum>=WIN-4){
        npc_date[2][0]=row+row_co1+1;
        npc_date[2][1]=col;
        npc_date[3][0]=row-row_co2-1;
        npc_date[3][1]=col;
        return 20;
        }

        else if(diagR_sum>=WIN-4){
        npc_date[4][0]=row+diagR_co1+1;
        npc_date[4][1]=col+diagR_co1+1;
        npc_date[5][0]=row-diagR_co2-1;
        npc_date[5][1]=col-diagR_co2-1;
        return 30;
        }

        else if(diagL_sum>=WIN-4){
        npc_date[6][0]=row+diagL_co1+1;
        npc_date[6][1]=col-diagL_co1-1;
        npc_date[7][0]=row-diagL_co2-1;
        npc_date[7][1]=col+diagL_co2+1;
        return 40;
        }
    }
    return 0;
}


void showban(int ban1[MASU][MASU],int ban2[MASU][MASU]){
    
    for(int mem=0;mem<MASU+1;mem++){
        printf("%d",mem);
    }

    printf("\n");

    for(int y=0;y<MASU;y++){
        printf("%d",y+1);

        for(int x=0;x<MASU;x++){

            if(ban1[x][y]==1)
                printf("○");

            else if(ban2[x][y]==1)
                printf("●");

            else
                printf("+");
        }

        printf("\n");
    }
}


int main(void){

    static int banmen_you[MASU][MASU];
    static int banmen_npc[MASU][MASU];
    static int npc_date[8][2],flag[2],npcsaves[2],input_npc[2][2];
    int input_x,input_y,temp_x,temp_y,winlose=100,playcount=0,flag_x,flag_y,b=1;

    while(1){
        if(playcount%2==0){
            while(1){
                printf("YOUR turn Enter x and y\n");
                scanf("%d%d",&input_x,&input_y);
                input_x-=1;
                input_y-=1;
                if(banmen_you[input_x][input_y]==0 && banmen_npc[input_x][input_y]==0 && input_x<MASU && input_x>-1 && input_y<MASU && input_y>-1)
                break;

                printf("Retry\n");
            }
        }

            else{
                for(int c=0;c<8;c++){
                    
                    for(int d=0;d<2;d++){
                        printf("%d",npc_date[c][d]);
                    }
                    printf("\n");
                }
                
                switch(winlose){
                    case 10://col
                        for(int arraynum=0;arraynum<2;arraynum++){

                            for(int i=0;i<MASU;i++){
                            temp_x=npc_date[arraynum][0];//
                            temp_y=npc_date[arraynum][1];
                                if(temp_x<0 || temp_x>=MASU || temp_y<0 || temp_y>=MASU){//
                                    flag[arraynum]=2;
                                    break;
                                }

                                if(arraynum==0)
                                    flag_y=temp_y+i;
                                else
                                    flag_y=temp_y-i;
                                    
                                if(banmen_you[temp_x][flag_y]==0){
                                    temp_y=flag_y;
                                    if(banmen_you[temp_x][temp_y]==0 && banmen_npc[temp_x][temp_y]==0){
                                        flag[arraynum]=3;
                                        if(arraynum==0)
                                            flag_y=temp_y+1;
                                        else
                                            flag_y=temp_y-1;

                                        if(banmen_you[temp_x][flag_y]==1){
                                            flag[arraynum]=1;
                                            break;//
                                        }
                                        break;//
                                    
                                    }
                                    else
                                        flag[arraynum]=2;
                                    break;
                                }
                            }

                            input_npc[arraynum][0]=temp_x;
                            input_npc[arraynum][1]=temp_y;
                        }
                        break;
                

                    case 20://row
                        for(int arraynum=0;arraynum<2;arraynum++){

                            for(int i=0;i<MASU;i++){
                                temp_x=npc_date[arraynum+2][0];
                                temp_y=npc_date[arraynum+2][1];

                                if(temp_x<0 || temp_x>=MASU || temp_y<0 || temp_y>=MASU){
                                    flag[arraynum]=2;
                                    break;
                                }

                                if(arraynum==0)
                                    flag_x=temp_x+i;
                                else
                                    flag_x=temp_x-i;

                                if(banmen_you[flag_x][temp_y]==0){
                                    temp_x=flag_x;
                                    if(banmen_you[temp_x][temp_y]==0 && banmen_npc[temp_x][temp_y]==0){
                                        flag[arraynum]=3;
                                        if(arraynum==0)
                                            flag_x=temp_x+1;
                                        else
                                            flag_x=temp_x-1;

                                        if(banmen_you[flag_x][temp_y]==1){
                                            flag[arraynum]=1;
                                            break;
                                        }
                                        break;
                                    }
                                    else
                                        flag[arraynum]=2;
                                    break;
                                }
                            }

                                printf("%d,%d,flag:%d,%d\n",temp_x,temp_y,flag[0],flag[1]);
                            input_npc[arraynum+2][0]=temp_x;
                            input_npc[arraynum+2][1]=temp_y;
                        }
                        break;
                
                    case 30://diagr
                        for(int arraynum=0;arraynum<2;arraynum++){

                            for(int i=0;i<MASU;i++){
                            temp_x=npc_date[arraynum+4][0];
                            temp_y=npc_date[arraynum+4][1];

                                if(temp_x<0 || temp_x>=MASU || temp_y<0 || temp_y>=MASU){
                                    flag[arraynum]=2;
                                    break;
                                }

                                if(arraynum==0){
                                    flag_x=temp_x+i;
                                    flag_y=temp_y+i;
                                }
                                else{
                                    flag_x=temp_x-i;
                                    flag_y=temp_y-i;
                                }
                                if(banmen_you[flag_x][flag_y]==0){
                                    temp_x=flag_x;
                                    temp_y=flag_y;
                                    if(banmen_you[temp_x][temp_y]==0 && banmen_npc[temp_x][temp_y]==0){
                                    flag[arraynum]=3;
                                        if(arraynum==0){
                                            flag_x=temp_x+1;
                                            flag_y=temp_y+1;
                                        }
                                        else{
                                            flag_x=temp_x-1;
                                            flag_y=temp_y-1;
                                        }
                                        if(banmen_you[flag_x][flag_y]==1){
                                            flag[arraynum]=1;
                                            break;
                                        }
                                        break;
                                    }
                                    else
                                        flag[arraynum]=2;
                                    break;
                                }
                            }

                            input_npc[arraynum+4][0]=temp_x;
                            input_npc[arraynum+4][1]=temp_y;
                        }
                        break;
                
                    case 40://diagl
                        for(int arraynum=0;arraynum<2;arraynum++){

                            for(int i=0;i<MASU;i++){
                            temp_x=npc_date[arraynum+6][0];
                            temp_y=npc_date[arraynum+6][1];

                                if(temp_x<0 || temp_x>=MASU || temp_y<0 || temp_y>=MASU){
                                    flag[arraynum]=2;
                                    break;
                                }

                                if(arraynum==0){
                                    flag_x=temp_x-i;
                                    flag_y=temp_y+i;
                                }
                                else{
                                    flag_x=temp_x-i;
                                    flag_y=temp_y+i;
                                }
                                if(banmen_you[flag_x][flag_y]==0){
                                    temp_x=flag_x;
                                    temp_y=flag_y;
                                    if(banmen_you[temp_x][temp_y]==0 && banmen_npc[temp_x][temp_y]==0){
                                    flag[arraynum]=3;
                                        if(arraynum==0){
                                            flag_x=temp_x-1;
                                            flag_y=temp_y+1;
                                        }
                                        else{
                                            flag_x=temp_x+1;
                                            flag_y=temp_y-1;
                                        }
                                        if(banmen_you[flag_x][flag_y]==1){
                                            flag[arraynum]=1;
                                            break;
                                        }
                                    break;
                                    }
                                    else
                                        flag[arraynum]=2;
                                    break;
                                }
                            }

                            input_npc[arraynum+6][0]=temp_x;
                            input_npc[arraynum+6][1]=temp_y;
                        }
                        break;
                


                    case 100:
                        input_x=input_x+1;
                        input_y=input_y+1;

                        if(banmen_you[input_x][input_y]==0 && banmen_npc[input_x][input_y]==0 && input_x<MASU && input_x>-1 && input_y<MASU && input_y>-1)
                            break;

                            input_x=input_x-2;
                            input_y=input_y-2;
                            break;

                    default:
                        input_x=npcsaves[0]+1;
                        input_y=npcsaves[1];
                        int a=6;
                        for(int i=1;i==1 || !(banmen_you[input_x][input_y]==0 && banmen_npc[input_x][input_y]==0 && input_x<MASU && input_x>-1 && input_y<MASU && input_y>-1); i++){
                            if(i>a){
                                a+=7;
                                b=a/2;
                                continue;
                            }
                            switch(i%7){
                                case 0:
                                    input_x=npcsaves[0];
                                    input_y=npcsaves[1]+b;
                                    break;
                                case 1:
                                    input_x=npcsaves[0]+b;
                                    input_y=npcsaves[1]+b;
                                    break;
                                case 2:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1];
                                    break;
                                case 3:
                                    input_x=npcsaves[0];
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 4:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 5:
                                    input_x=npcsaves[0]+b;
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 6:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1]+b;
                                    break;
                            }
                        }
                }
                    int sel=winlose;
                    if(sel==10)
                        sel=0;
                    else if(sel==20)
                        sel=2;
                    else if(sel==30)
                        sel=4;
                    else if(sel==40)
                        sel=6;

                    if(flag[0]==1 && flag[1]==1){
                        input_x=input_npc[1+sel][0];
                        input_y=input_npc[1+sel][1];
                    }
                    else if(flag[0]==3 && flag[1]==3){
                        input_x=input_npc[1+sel][0];
                        input_y=input_npc[1+sel][1];
                    }
                    //ランダム
                    else if(flag[0]==2 && flag[1]==2){
                        
                        input_x=npcsaves[0]+1;
                        input_y=npcsaves[1];
                        int a=6;
                        for(int i=1;i==1 || !(banmen_you[input_x][input_y]==0 && banmen_npc[input_x][input_y]==0 && input_x<MASU && input_x>-1 && input_y<MASU && input_y>-1); i++){
                            if(i>a){
                                a+=7;
                                b=a/2;
                                continue;
                            }
                            switch(i%7){
                                case 0:
                                    input_x=npcsaves[0];
                                    input_y=npcsaves[1]+b;
                                    break;
                                case 1:
                                    input_x=npcsaves[0]+b;
                                    input_y=npcsaves[1]+b;
                                    break;
                                case 2:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1];
                                    break;
                                case 3:
                                    input_x=npcsaves[0];
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 4:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 5:
                                    input_x=npcsaves[0]+b;
                                    input_y=npcsaves[1]-b;
                                    break;
                                case 6:
                                    input_x=npcsaves[0]-b;
                                    input_y=npcsaves[1]+b;
                                    break;
                            }
                        }
                    }
//
                    else if(flag[0]==1 && (flag[1]==2 || flag[1]==3)){
                        input_x=input_npc[0+sel][0];
                        input_y=input_npc[0+sel][1];
                    }
                    else if(flag[0]==3 && flag[1]==2){
                        input_x=input_npc[0+sel][0];
                        input_y=input_npc[0+sel][1];
                    }
//
                    else if(flag[1]==1 && (flag[0]==2 || flag[0]==3)){
                        input_x=input_npc[1+sel][0];
                        input_y=input_npc[1+sel][1];
                    }
                    else if(flag[1]==3 && flag[0]==2){
                        input_x=input_npc[1+sel][0];
                        input_y=input_npc[1+sel][1];
                    }

//npc ここまで
            }

//10 row 20 col 30 R 40 L
        printf("final:%d,%d\n%d\n",input_x,input_y,winlose);
        
        if(playcount%2==0){
            banmen_you[input_x][input_y]=1;
            winlose=hantei(banmen_you,input_x,input_y,playcount%2,npc_date);
        }
        
        else{
            banmen_npc[input_x][input_y]=1;
            winlose=hantei(banmen_npc,input_x,input_y,playcount%2,npc_date);
        }

        showban(banmen_you,banmen_npc);
        if(winlose==1){
            printf("Player%d was WIN!",playcount%2+1);
            break;
        }
        playcount++;
//引き分け
        if(playcount>=MASU*MASU){
            printf("引き分け");
            return 0;
        }
    }

    return 0;
}