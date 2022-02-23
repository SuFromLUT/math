#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;


/* 从 m 个元素 0,1,...,m-1 中取 k 个值，
 * 得到 多个 组合(Combination) */
/* display 为 true 时，打印所有组合 */
vector<vector<int>> combination(int m, int k, bool display = false) {
    vector<vector<int>> sq_vector;
    if (m==k) {
        vector<int> sq;
        for(int i=0;i<m;i++) {
            sq.push_back(i);
        }
        sq_vector.push_back(sq);
        return sq_vector;
    }

    vector<bool> v(m);
    fill(v.end() - k, v.end(), true);

    do {
        vector<int> sq;
        for (int i=0 ; i < m ; ++i) {
            if(v[i]) {
                sq.push_back(i);
            }
        }
        sq_vector.push_back(sq);
    } while (next_permutation(v.begin(),v.end()));

    if (display) {
        for(int i=0;i<sq_vector.size();i++){
            for(int j=0;j<sq_vector[i].size();j++){
                cout<<sq_vector[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"size="<<sq_vector.size()<<endl;

    }

    return sq_vector;

}


/* 公式连乘 */
class Multiply {
public:
    /* 初始化(不带x) */
    Multiply(int m) : m(m) {

        /* 初始化 数组theta */
        theta = new double [m+1];

        /* 初始化 数组x */
        x = new double [m];

        /* 最高次项系数总为 1 */
        theta[0] = 1;
    }

    /* 初始化(带x) */
    Multiply(int m,double *x) : m(m),x(x){
        /* 初始化 数组theta */
        theta = new double [m+1];

        /* 最高次项系数总为 1 */
        theta[0] = 1;
    }

    /* 输入X_j */
    void input() {
        for(int j=0;j<m;j++)
            cin>>x[j];
    }

    /* 开始处理 */
    void process() {
        /* 求 x^(m-k) (k<=m) 项的系数 */
        for(int k=1;k<=m;k++) {

            /* 从 m 个元素 0,1,...,m-1 中取 k 个值，
             * 得到 多个 组合(Combination) */
            vector<vector<int>> sq_vec =
                    combination(m,k, false);

            /* 子累加项 x1*x2*... + x2*x1*... + ... */
            double sub_acc = 0;

            /* 得到 x^(m-k) 前的系数 */
            for (int r = 0; r < sq_vec.size(); r++) {

                /* 子累乘项 x1*x2*... */
                double sub_mul = 1;
                for (int s = 0;s<sq_vec[r].size();s++) {
                    sub_mul *= x[sq_vec[r][s]];
                }

                sub_acc += sub_mul;
            }

            /* 将得到的数存入 theta 数组中 */
            theta[k] = sub_acc;
        }
    }

    /* 打印得到的系数向量 */
    void display_theta() {
        for (int i=0;i<=m;i++) {
            cout<<theta[i]<<" ";
        }
        cout<<endl;
    }

    /* 打印展开的式子 */
    void display_formula() {
        for (int i=0;i<m;i++) {
            cout<<theta[i]<<" * x^"<<m-i<<" + ";
        }
        cout<<theta[m];
    }

private:
    /* x_j */
    double *x;

    /* theta[k]表示x^(m-k)项前的系数 */
    double *theta;

    /* 记录x_j的数量 */
    int m;
};


/* main */
/* 主程序测试 */
int main() {

    int m;
    cin>>m;

    Multiply *pm = new Multiply(m);

    pm->input();
    pm->process();

    pm->display_formula();

    return 0;

}
