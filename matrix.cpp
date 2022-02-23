#include "iostream"
#include "algorithm"
using namespace std;


/* 矩阵 */
class matrix {
public:

    /*初始化矩阵*/
    matrix(int n,int m)
    :n(n),m(m)
    {
        a = new double*[n];
        for(int i=0;i<n;i++)
            a[i] = new double[m];
    }

    /*从键盘键入矩阵所有元素*/
    void input(){
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                cin>>a[i][j];

    }

    /* 初等行(列)变换
     * 当col为默认值false时，初等行变换
     * 当col值为true时，初等列变换 */
    void transform(int u,int v,bool col = false) {
        if(col) {
            for(int i=0;i<n;i++){
                swap(this->a[i][u],this->a[i][v]);
            }
            return;
        }
        swap(a[u],a[v]);
    }



    /*打印矩阵的所有元素到cmd*/
    void disp(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
               cout<<a[i][j]<<"\t";
            cout<<endl;
        }
    }

    /* 求矩阵的逆 */
    matrix operator~() const {
        /* 创建this->m*this->n的副本矩阵，作为返回的结果 */
        matrix pr(m,n);

        for(int j=0;j<m;j++)
            for(int i=0;i<n;i++)
                pr.a[j][i] = this->a[i][j];

        return pr;
    }

    /*矩阵叉乘*/
    matrix operator*(const matrix &toMul) const {
        int _m = toMul.m;
        int _n = toMul.n;
        if(this->m!=_n){
            cout<<"两矩阵不符合要求(A*B，矩阵A的列数必须和矩阵B的行数相同)，无法相乘"<<endl;
            return toMul;
        }

        /* 两矩阵相乘组以后得到行为n，列为_m的矩阵 */
        matrix *pr = new matrix(n, _m);

        /* 两矩阵开始叉乘 */
        for(int i=0;i<pr->n;i++){
            for(int j=0;j<pr->m;j++){
                double sum = 0;
                /* this矩阵第i行行向量的和toMul矩阵第j列列向量相乘
                 * 或者说：
                 * this矩阵第i行行向量的转置和toMul矩阵第j列列向量的点乘 */
                for(int k=0;k<n;k++){
                    sum += this->a[i][k]*toMul.a[k][j];
                }
                /* 将得到的值带入矩阵结果二维数组中 */
                pr->a[i][j] = sum;
            }
        }
        return *pr;
    }


    /* 矩阵点乘 */
    matrix operator&(const matrix &toMul) const {
        int _n = toMul.n;
        int _m = toMul.m;

        if (_n != n || _m != m) {
            cout << "矩阵点乘不符点乘合要求（两矩阵行数和列数必须相同）" << endl;
            return toMul;
        }

        /* 声明两矩阵点乘得到的函数 */
        matrix *pr = new matrix(n, m);

        /* 开始点乘 */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                pr->a[i][j] = this->a[i][j] * toMul.a[i][j];

        /* 返回结果 */
        return *pr;

    }

    int get_n() const {
        return n;
    }

    int get_m() const {
        return m;
    }

    double **get_a() const {
        return a;
    }

    double get_v(int i,int j) const {
        return a[i][j];
    }

protected:
    /*定义矩阵的行数和列数*/
    int n,m;

    /*定义矩阵内的实数元素*/
    double **a;


};


class square_matrix : public matrix
{
public:
    /* 初始化方阵 */
    square_matrix(int n):
    matrix(n,n){
    }

    /* 求方阵的值 */
    double value() const;

    /* 将矩阵转换为方阵 */
    friend square_matrix to_square(const matrix &matrix);

};

/* 求方阵的值 */
double square_matrix::value() const {
    double v = 0;
    int *ps = new int[n];
    for(int i=0;i<n;i++)
        ps[i] = i;
    do {
        int cnt = 0;
        for (int i = n - 1; i > 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (ps[j] > ps[i])
                    cnt++;
            }
        }
        double pro = 1;
        for (int i = 0; i < n; i++)
            pro *= a[i][ps[i]];
        if (cnt % 2 == 1)
            pro = -pro;
        v += pro;

    } while(next_permutation(ps,ps+n));
    return v;
}

/* 将矩阵转换为方阵 */
square_matrix to_square(const matrix &matrix) {
    int _n = matrix.get_n();
    square_matrix *pr = new square_matrix(_n);
    if(_n!=matrix.get_m()) return *pr;
    for(int i=0;i<_n;i++) {
        for(int j=0;j<_n;j++)
            pr->a[i][j] = matrix.get_v(i,j);
    }
    return *pr;
}

/*main*/
int main(){

    /* 声明一个3*3的方阵 */
    matrix A(2,2);


    cout<<"请输入2*2的方阵的所有元素："<<endl;

    /* 输入方阵A的元素 */
    A.input();

    /* 将行列数相同的矩阵转化为方阵 */
    square_matrix A_S = to_square(A);

    /* 展示方阵A_S的所有元素 */
    A_S.disp();

    /* 求方阵A_S的值 */
    cout<<A_S.value()<<endl;

    return 0;

}
