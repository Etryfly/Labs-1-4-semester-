#include <stdio.h>

char in[100], C[100], D[100];
int i = 0, k = 0, Count = 1;
int B[100] = {0};
int E(int t,int _,char*a) {
    return!0<t?t<3?E(-79,-13,a+E(-87,1-_,
                                       E(-86, 0, a+1 )+a)):1,t<_?E(t+1, _, a ):3,E ( -94, -27+t, a
    )&&t == 2 ?_<13 ?E ( 2, _+1, "%s %d %d\n" ):9:16:t<0?t<-72?E(_,
                                                                       t,"@n'+,#'/*{}w+/w#cdnr/+,{}r/*de}+,/*{*+,/w{%+,/w#q#n+,/#{l,+,/n{n+,+#n+,/#;#q#n+,/+k#;*+,/'r :'d*'3,}{w+K w'K:'+}e#';dq#'l q#'+d'K#!/\
+k#;q#'r}eKK#}w'r}eKK{nl]'/#;#q#n'){)#}w'){){nl]'/+#n';d}rw' i;# ){n\
l]!/n{n#'; r{#w'r nc{nl]'/#{l,+'K {rw' iK{;[{nl]'/w#q#\
n'wk nw' iwk{KK{nl]!/w{%'l##w#' i; :{nl]'/*{q#'ld;r'}{nlwb!/*de}'c \
;;{nl'-{}rw]'/+,}##'*}#nc,',#nw]'/+kd'+e}+;\
#'rdq#w! nr'/ ') }+}{rl#'{n' ')# }'+}##(!!/")
                                                                 :t<-50?_==*a ?putchar(a[31]):E(-65,_,a+1):E((*a == '/')+t,_,a\
+1 ):0<t?E ( 2, 2 , "%s"):*a=='/'||E(0,E(-61,*a, "!ek;dc i@bK'(q)-[w]*%n+r3#l,{}:\nuwloca-O;m .vpbks,fxntdCeghiry"),a+1);
}

void F () {
    if (k == i) {
        int flag = 1, c = 0;
        for (int a = 0; a < i; a++) {
            if (D[a] > C[a]) {flag = 0; break;}
            if (D[a] < C[a]) break;
            if (D[a] == C[a]) c++;
        }
        if (c == i) flag = 0;
        if (flag) {
            printf("%d) ", Count); Count++;
            for (int a = 0; a < i; a++) printf("%c", C[a]);
            printf("\n");
            for (int a = 0; a < i; a++) D[a] = C[a];
        }
        return;
    }
    for (int j = 0; j < i; j++) {
        if (!B[j]) {
            C[k] = in[j];
            B[j] = 1;
            k++;
            F();
            k--;
            B[j] = 0;
        }
    }
    return;
}

int main() {

    int n;
    char ch;
    ch = getchar();
    while (ch != '\n') {
        in[i++] = ch;
        ch = getchar();
    }
//    E(0, 0, B);
    for (int a = 0; a < i; a++) {
        for (int b = a+1; b < i; b++) {
            if (in[a] > in[b]) {
                ch = in[a];
                in[a] = in[b];
                in[b] = ch;
            }
        }
    }
    printf("%d) ", Count); Count++;
    for (int a = 0; a < i; a++) {D[a] = in[a]; printf("%c", in[a]);}
    printf("\n");
    F();
    E(-1, 10, in);
}
