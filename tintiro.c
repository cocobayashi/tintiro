#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int saikoro[3];                 //サイコロ
    int i;                          //ループカウンタ
    int j;
    int k;
    int temp;                       //作業領域
    int flag;                       //flag = 0 初期状態  flag = 1 振り直し flag = 1以外 ループ終了
    int judge[4];                   //サイコロの出目の強さの判定
    int perika;                     //ペリカ
    int kake[4] = {1,1,1,1};        //かけ額
    int total = 0;                  //トータルのペリカ収支
    flag = 0;

    printf("チンチロ  プログラム\n");
    printf("あなたが親です。\n");
    printf("子の賭け額は500ペリカ固定とします。\n");
    printf("続けるには数字を押してください\n");
    scanf("%d", &i);

    //プレイヤーのサイコロの出目
    for (k = 0; k < 3; k++) {
        for(i = 0; i < 3; i++) {
            saikoro[i] = 0 + rand() % 6 +1;
        }
        for (i = 0; i < 3 - 1; i++){
            for (j = i + 1; j < 3; j++) {               //配列の並べ替え(降順)
                if (saikoro[i] < saikoro[j]) {
                    temp = saikoro[i];
                    saikoro[i] = saikoro[j];
                    saikoro[j] = temp;
                }
            }
        }
        printf("あなたの出目は %d %d %dです。\n", saikoro[0], saikoro[1], saikoro[2]);
        if (k < 2) {                                                                        //2回までは振り直し可能
            printf("サイコロを振り直しますか？\n");
            printf("振り直す場合には 1 を、振り直さない場合には 1 以外を入力してください。\n");
            printf("==> ");
            scanf("%d", &flag);
        }
        if (flag != 1) {                                                                    //振り直さない場合ループ終了
            k = 3;
        }
    }

    printf("\n");

    for (k = 0; k < 4; k++) {                   //k = 0がプレイヤー  k = 1,2,3が対戦相手
        if (k != 0){                            //対戦相手のループ時のみサイコロの出目を決める
            for(i = 0; i < 3; i++) {
                saikoro[i] = 0 + rand() % 6 +1;
            }

            for (i = 0; i < 3 - 1; i++){
                for (j = i + 1; j < 3; j++) {
                    if (saikoro[i] < saikoro[j]) {
                        temp = saikoro[i];
                        saikoro[i] = saikoro[j];
                        saikoro[j] = temp;
                    }
                }
            
            }
            printf("対戦相手 %d のサイコロの出目は %d %d %d です。\n", k, saikoro[0], saikoro[1], saikoro[2]);
        } else {

        }
        //サイコロの出目の判定(出目の強い順で判定しています) 最後のみヒフミを判定してそれ以外が出目なしで判定しています。
        if (saikoro[0] == saikoro[1] == saikoro[2]) {
            switch (saikoro[0]) {
                case 1:                                         //出目1,1,1の時(ピンゾロ)
                    judge[k] = 13;
                    kake[k] = 5;
                    break;
                case 6:                                         //出目6,6,6の時
                    judge[k] = 12;
                case 5:                                         //出目5,5,5の時
                    judge[k] = 11;
                case 4:                                         //出目4,4,4の時
                    judge[k] = 10;
                case 3:                                         //出目3,3,3の時
                    judge[k] = 9;
                case 2:                                         //出目2,2,2の時
                    judge[k] = 8;
                kake[k] = 3;
                break;
            }
        } else if (saikoro[0] == 6 && saikoro[1] == 5 && saikoro[2] ==4) {
            judge[k] = 7;                                         //出目6,5,4の時(シゴロ)
            kake[k] = 2;
        } else if (saikoro[1] == 2 && saikoro[2] ==2) {
            switch (saikoro[0]) {
                case 6:                                         //出目6,2,2の時
                    judge[k] = 6;
                case 5:                                         //出目5,2,2の時
                    judge[k] = 5;
                case 4:                                         //出目4,2,2の時
                    judge[k] = 4;
                case 3:                                         //出目3,2,2の時
                    judge[k] = 3;
                case 2:                                         //出目2,2,2の時
                    judge[k] = 2;
            }
        } else if (saikoro[0] == 2 && saikoro[1] == 2 && saikoro[2] == 1) {
            judge[k] = 1;                                        //出目2,2,1の時
        } else if (saikoro[0] == 3 && saikoro[1] == 2 && saikoro[2] == 3) {
            judge[k] = -1;                                      //出目3,2,1の時(ヒフミ)
            kake[k] = 2;
        } else {
            judge[k] = 0;                                        //出目無しの時
        }
    }
    printf("\n");
//結果発表
    for (i = 1; i <= 3; i++) {
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