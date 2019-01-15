#include<stdio.h>
#define MAS 8
#define WIN 5

int hantei(int ban[MAS][MAS],int row,int col){

    int row_count=0,col_count=0,diag_count=0;

    // 1 縦
    for(int i=col+1;ban[row][i]==1 && i<MAS;i++){
        col_count++;
    }
    for(int i=col;ban[row][i]==1 && i>=0;i--){
        col_count++;
    }

    if(col_count>=WIN)
            return 1;

    // 2 横
    for(int i=row+1;ban[i][col]==1 && i<MAS;i++){
        row_count++;
    }
    for(int i=row;ban[i][col]==1 && i>=0;i--){
        row_count++;
    }

    if(row_count>=WIN)
            return 1;

    // 3 右斜
    for(int x=row+1,y=col+1;ban[x][y]==1 && x<MAS && y<MAS;x++,y++){
        diag_count++;
    }
    for(int x=row,y=col;ban[x][y]==1 && x>=0 && y>=0;x--,y--){
        diag_count++;
    }

    if(diag_count>=WIN)
            return 1;
    diag_count=0;

    // 4 左斜
    for(int x=row+1,y=col-1;ban[x][y]==1 && x<MAS && y>=0;x++,y--){
        diag_count++;
    }
    for(int x=row,y=col;ban[x][y]==1 && x>=0 && y<MAS;x--,y++){
        diag_count++;
    }

    if(diag_count>=WIN)
            return 1;
    
    return 0;
}

void showban(int ban1[MAS][MAS],int ban2[MAS][MAS]){
    for(int mem=0;mem<MAS+1;mem++){
        printf("%d",mem);
    }
    printf("\n");
    for(int y=0;y<MAS;y++){
        printf("%d",y+1);
        for(int x=0;x<MAS;x++){
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
    static int banmen_1[MAS][MAS];
    static int banmen_2[MAS][MAS];
    int input_x,input_y,winlose,playcount=0;

    while(1){
        printf("Enter x and y\n");
        while(1){
            scanf("%d%d",&input_x,&input_y);
            input_x-=1;
            input_y-=1;
            if(banmen_1[input_x][input_y]==0 && banmen_2[input_x][input_y]==0 && input_x<MAS && input_x>-1 && input_y<MAS && input_y>-1)
            break;
            printf("Retry\n");
        }

        if(playcount%2==0){
            banmen_1[input_x][input_y]=1;
            winlose=hantei(banmen_1,input_x,input_y);
        }
        else{
            banmen_2[input_x][input_y]=1;
            winlose=hantei(banmen_2,input_x,input_y);
        }
        showban(banmen_1,banmen_2);

        if(winlose==1){
            printf("Player%d was WIN!",playcount%2+1);
            break;
        }

        playcount++;
    }
}