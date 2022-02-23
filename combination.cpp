
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
