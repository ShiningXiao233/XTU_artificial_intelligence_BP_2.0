#include "BP.h"
#include <io.h>
// #include<unistd.h>

double V[N + 10][L + 10], deltV[N + 10][L + 10];
double W[L + 10][M + 10], deltW[L + 10][M + 10];
double theta[M + 10], delt_th[M + 10], phi[L + 10], delt_ph[M + 10];

double Indata[N + 10];
double out_h[L + 10], out_y[M + 10];
double Desire[M + 10];
double delta_y[M + 10], delta_h[L + 10];
const char *logfile = "log.txt";

mt19937 gen(time(0));
double Gen(double l, double r) {
    return gen() % 1000000 / 999999.0 * (r - l) + l;
}

double F(double x) {
    return 1 / (1 + exp(-x));
}

const double LLL = 0, RRR = 0.001;

void rand_arg() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < L; ++j) {
            V[i][j] = Gen(LLL, RRR);
        }
    }

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < M; ++j) {
            W[i][j] = Gen(LLL, RRR);
        }
    }

    for (int i = 0; i < M; ++i) {
        theta[i] = Gen(LLL, RRR);
    }

    for (int i = 0; i < L; ++i) {
        phi[i] = Gen(LLL, RRR);
    }
}

void input_arg() {
    freopen(logfile, "r", stdin);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < L; ++j) {
                cin >> V[i][j];
            }
        }

        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> W[i][j];
            }
        }

        for (int i = 0; i < M; ++i) {
            cin >> theta[i];
        }

        for (int i = 0; i < L; ++i) {
            cin >> phi[i];
        }
        fclose(stdin);

}

void init_arg() {
    
    if (access(logfile, F_OK)!=0) {
        printf("random_get_data!\n");
        rand_arg();
    } else {
        printf("inputing....\n");
        input_arg();
        printf("inputok!\n");
    }
    
}


void calc_h() {
    for (int j = 0; j < L; ++j) {
        out_h[j] = 0;
        for (int i = 0; i < N; ++i) {
            out_h[j] += V[i][j] * Indata[i];
        }
        out_h[j] = F(out_h[j] + phi[j]);
    }
}

void calc_y() {
    for (int k = 0; k < M; ++k) {
        out_y[k] = 0;
        for (int j = 0; j < L; ++j) {
            out_y[k] += W[j][k] * out_h[j];
        }
        out_y[k] = F(out_y[k] + theta[k]);
    }
}

void calc_delta_y() {
    for (int k = 0; k < M; ++k) {
        delta_y[k] = (Desire[k] - out_y[k]) * out_y[k] * (1 - out_y[k]);
    }
}

void calc_delta_h() {
    for (int j = 0; j < L; ++j) {
        delta_h[j] = 0;
        for (int k = 0; k < M; ++k) {
            delta_h[j] += (W[j][k] * delta_y[k]);
        }
        delta_h[j] *= out_h[j] * (1 - out_h[j]);
    }
}

void calc_delta_arg() {
    for (int j = 0; j < L; ++j) {
        for (int k = 0; k < M; ++k) {
            deltW[j][k] = (Subalgha) * (deltW[j][k] + 1) * delta_y[k] * out_h[j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < L; ++j) {
            deltV[i][j] = (Subalgha) * (deltV[i][j] + 1) * delta_h[j] * Indata[i];
        }
    }

    for (int k = 0; k < M; ++k) {
        delt_th[k] = (Subalgha) * (delt_th[k] + 1) * delta_y[k];
    }

    for (int j = 0; j < L; ++j) {
        delt_ph[j] = (Subalgha) * (delt_ph[j] + 1) * delta_h[j];
    }
}


void adjust_arg() {
    // cout << " --- " << V[1][1] << ' ' << deltV[1][1] << '\n';
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < L; ++j) {
            V[i][j] += deltV[i][j];
        }
    }

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < M; ++j) {
            W[i][j] += deltW[i][j];
        }
    }

    for (int i = 0; i < M; ++i) {
        theta[i] += delt_th[i];
    }

    for (int i = 0; i < L; ++i) {
        phi[i] += delt_ph[i];
    }
}

double calc_E() {
    double E = 0;

    for (int i = 0; i < M; ++i) {
        E += (out_y[i] - Desire[i]) * (out_y[i] - Desire[i]);
    }

    return E / 2;
}

void print_to_log() {
    freopen(logfile, "w", stdout);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < L; ++j) {
            printf("%.9f ", V[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    for (int j = 0; j < L; ++j) {
        for (int k = 0; k < M; ++k) {
            printf("%.9f ", W[j][k]);
        }
        printf("\n");
    }
    printf("\n\n");

    for (int j = 0; j < L; ++j) {
        printf("%.9f ", phi[j]);
    }
    printf("\n\n\n");


    for (int k = 0; k < M; ++k) {
        printf("%.9f ", theta[k]);
    }
    printf("\n\n\n");
    
    fclose(stdout);
    // exit(0);
}

void set_data(double *in, double *d) {
    for (int i = 0; i < N; ++i) {
        Indata[i] = in[i] / 255;
    }
    for (int k = 0; k < M; ++k) {
        Desire[k] = d[k];
    }
}

double run_train() {
    calc_h();
    calc_y();
    double E = calc_E();
    if (E <= epsilon){ 
        return E;
    }
    calc_delta_y();
    calc_delta_h();
    calc_delta_arg();
    adjust_arg();
    return E;
}

double cmp(double *in, double *d) {
    set_data(in, d);
    calc_h();
    calc_y();
    double E = calc_E();
    return E;
}
