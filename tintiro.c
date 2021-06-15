#include <stdio.h>
#include <stdlib.h>

void sort(int *psaikoro1);
void hantei(int *pjudge, int *pkake, int *psaikoro);

int main(void)
{
    int saikoro[10][3];                     //サイコロ 11人分
    int *psaikoro1;
    int i,j,k;                              //ループカウンタ
    int temp;                               //作業領域
    int flag;                               //flag = 0 初期状態  flag = 1 振り直し flag = 1以外 ループ終了
    int judge[11];                          //サイコロの出目の強さの判定
    int perika;                             //ペリカ
    int kake[11];                           //かけ額
    int total = 0;                          //トータルのペリカ収支
    flag = 0;

    printf("チンチロ  プログラム\n");
    printf("あなたが親です。\n");
    printf("子の賭け額は500ペリカ固定とします。\n");
    printf("続けるには数字を押してください\n");
    scanf("%d", &i);
    
    printf("\n");

    for (k = 0; k < 11; k++) {                   //k = 0がプレイヤー  それ以降が対戦相手10人　計11回
        if (k == 0){                            
            for (i = 0; i < 3; i++) {                                                           //プレイヤーは2回までは振り直し可能
                for(j = 0; j < 3; j++) {
                    saikoro[k][j] = 0 + rand() % 6 +1;
                }
            
                sort(&saikoro[k][0]);                                                           //ソート
                printf("あなたの出目は %d %d %dです。\n", saikoro[k][0], saikoro[k][1], saikoro[k][2]);

                if (i < 2) {                                                                        //2回振り直ししている場合は終了
                    printf("サイコロを振り直しますか？\n");
                    printf("振り直す場合には 1 を、振り直さない場合には 1 以外を入力してください。\n");
                    printf("==> ");
                    scanf("%d", &flag);
                } else {
                    i = 3;
                }

                if (flag != 1) {                                                                    //振り直さない場合ループ終了
                    i = 3;
                }
            } 
        } else {
            for(i = 0; i < 3; i++) {                                                    //対戦相手のサイコロ判定
                saikoro[k][i] = 0 + rand() % 6 +1;
            }
            sort(&saikoro[k][0]);                                                       //ソート
            
            printf("対戦相手 %d のサイコロの出目は %d %d %d です。\n", k, saikoro[k][0], saikoro[k][1], saikoro[k][2]);
        }

        hantei(&judge[0] + k, &kake[0] + k, &saikoro[k][0]);                                //関数にて役の判定
        
    }

    printf("\n");

//結果発表
//出目の強さを数値にて判定 ペリカの増減も判定
    for (i = 1; i <= 20; i++) {
        if (judge[0] == judge[i]) {
            printf("対戦相手 %d と出目の強さが等しいので金銭のやり取りはなし。\n", i);
        } else if (judge[0] > judge[i]){
            perika = 500 * kake[i];
            total = total + perika;
            printf("対戦相手 %d よりあなたの出目が強いので勝ち！\n", i);
            printf("獲得金額は %d ペリカです。\n",perika);
        } else if (judge[0] < judge[i]) {
            perika = 500 * kake[i];
            total = total - perika;
            printf("対戦相手 %d よりあなたの出目が弱いので負け！\n", i);
            printf("支払金額は %d ペリカです。\n", perika);
        }
    printf("\n");
    }
    printf("結果 ペリカの収支は %d でした。", total);

    return 0;
} 


//ただのソートの関数
void sort(int *psaikoro1)
{
    int *ptemp1;
    int *ptemp2;
    int work;
    for (ptemp1 = psaikoro1; ptemp1 < psaikoro1 + 3 - 1; ptemp1++) {
            for (ptemp2 = ptemp1 + 1; ptemp2 < psaikoro1 + 3; ptemp2++) {               //配列の並べ替え(降順)
                if (*ptemp1 < *ptemp2) {
                    work = *ptemp1;
                    *ptemp1 = *ptemp2;
                    *ptemp2 = work;
                }
            } 
    }
}

//サイコロの役判定関数
//サイコロの出目の判定(出目の強さを数値にして比べています。)
//一番強い出目であるピンゾロを強さ13(MAX)　出目なしが強さ0  一番弱い出目であるヒフミの強さを -1 (MIN)としています
//さらに役によって支払ったペリカが増える(乗算)のでその掛け額も判定しています　==> kake
void hantei(int *pjudge, int *pkake, int *psaikoro)
{
    *pkake = 1;
    if (*psaikoro == *(psaikoro + 1) && *(psaikoro + 1) == *(psaikoro + 2)) {
        switch (*psaikoro) {
            case 1:                                         //出目1,1,1の時(ピンゾロ)
                *pjudge = 13;
                *pkake = 5;
                break;
            case 6:                                         //出目6,6,6の時
                *pjudge = 12;
            case 5:                                         //出目5,5,5の時
                *pjudge = 11;
            case 4:                                         //出目4,4,4の時
                *pjudge = 10;
            case 3:                                         //出目3,3,3の時
                *pjudge = 9;
            case 2:                                         //出目2,2,2の時
                *pjudge = 8;
                *pkake = 3;
            break;
            }
    } else if (*psaikoro == 6 && *(psaikoro + 1) == 5 && *(psaikoro + 2) == 4) {
        *pjudge = 7;                                         //出目6,5,4の時(シゴロ)
        *pkake = 2;
    } else if (*(psaikoro + 1) == 2 && *(psaikoro + 2) ==2) {
        switch (*psaikoro) {
            case 6:                                         //出目6,2,2の時
                *pjudge = 6;
            case 5:                                         //出目5,2,2の時
                *pjudge = 5;
            case 4:                                         //出目4,2,2の時
                *pjudge = 4;
            case 3:                                         //出目3,2,2の時
                *pjudge = 3;
            case 2:                                         //出目2,2,2の時
                *pjudge = 2;
        }
    } else if (*psaikoro == 2 && *(psaikoro + 1) == 2 && *(psaikoro + 2) == 1) {
        *pjudge = 1;                                        //出目2,2,1の時
    } else if (*psaikoro == 3 && *(psaikoro + 1) == 2 && *(psaikoro + 2) == 3) {
        *pjudge = -1;                                      //出目3,2,1の時(ヒフミ)
        *pkake = 2;
    } else {
        *pjudge = 0;                                        //出目無しの時
    }
}