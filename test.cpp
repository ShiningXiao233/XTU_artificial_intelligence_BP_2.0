#include "BP.h"
#include "Util_img.h"

const string DIR = "./YALE/";
const string img_pre[] = {
    "subject01", "subject02", "subject03", "subject04", "subject05",
    "subject06", "subject07", "subject08", "subject09", "subject10",
    "subject11", "subject12", "subject13", "subject14", "subject15",
};
U1 img[ImgSive + 100];
double imgp[800][ImgSive + 100], imgd[800][50];
int cnt = 0;
int TrainCnt = 30000;
void set_P(string p, double *f) {
    input_img8(p.c_str(), img);
    compress(img, f);
}

void work(double *in, double *d) {
    set_data(in, d);
    double E = run_train();
    // printf("learn %d-th: E = %.6f\n", ++cnt, E); // 打印训练信息
}

void set_D(int x, double *f) {
    for (int i = 0; i < M; ++i) {
        if (i == x) f[i] = 1;
        else f[i] = 0;
    }
}

void train() {
    int CNT = TrainCnt;
    int fcnt = 0;
    for (int i = 0; i < 15; ++i) {
        string name;
        for (int j = 1; j <= 5; ++j) {
            name = DIR + img_pre[i] + "_";
            if (j < 10)
                name += (char)(j + '0');
            else {
                name += (char)(j / 10 + '0');
                name += (char)(j % 10 + '0');
                
            }
            name += ".bmp";
            set_P(name, imgp[fcnt]);
            set_D(i, imgd[fcnt]);
            fcnt ++;
        }
    } 
    double st_time = clock();
    int i = 0;
    while (CNT --) {
        work(imgp[i], imgd[i]);
        i ++;
        i %= fcnt;
    }
    double ed_time = clock();
    printf("Train picture: %d\n", TrainCnt);
    printf("Train time: %.5f\n", (ed_time - st_time) / CLOCKS_PER_SEC);
    print_to_log();
}
double cmpin[ImgSive + 10], cmpout[ImgSive + 10];

int get_cmp(string x) {
    double f = 1e18;
    int id = -1;
    set_P(x, cmpin);
    for (int i = 0; i < 15; ++i) {
        set_D(i, cmpout);
        double tmp = cmp(cmpin, cmpout);
        if (tmp < f) {
            f = tmp;
            id = i;
        }
    }
    printf("%s belong %d == E : %.5f ", x.c_str(), id + 1, f);
    return id;
}

void test() {
    int CNT = 0, YCNT = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 1; j <= 11; ++j) {
            string name = DIR + img_pre[i] + "_";
            if (j < 10) name += (char)(j + '0');
            else { 
                name += (char)(j / 10 + '0');
                name += (char)(j % 10 + '0');
            }
            name += ".bmp";
            int p = get_cmp(name);
            CNT ++;
            if (p == i) {
                YCNT ++;
                printf (" Yes!\n");
            } else {
                printf (" No! \n");
            }
        }
    }
    printf("yes: %d  ==== no: %d  ===  %.5f\n", YCNT, CNT - YCNT, 1.0 * YCNT / CNT);
}


int main(int argc,char *argv[]) {
    init_arg(); // 初始，没有log.txt 就随机参数，否则输入log.txt
    if (argc >= 2 && strcmp(argv[1], "train") == 0) {
        printf("train!\n");
        if (argc >= 3) {
            int n = strlen(argv[2]);
            int res = 0;
            for (int i = 0; i < n; ++i) {
                res = res * 10 + argv[2][i] - '0';
            }
            TrainCnt = res;
        }
        train(); // 训练
    }
    else if (argc == 1 || strcmp(argv[1], "test") == 0) {
        printf("test!");
        test();
    }
    
    
    return 0;
}