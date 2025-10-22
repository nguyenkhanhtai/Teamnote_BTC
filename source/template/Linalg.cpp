const int SquareMOD = MOD * MOD;

struct Matrix{
    int r, c;
    vector<vector<mint>> mat;
    Matrix(int _r = 0, int _c = 0){
        r = _r;
        c = _c;
        mat.resize(r, vector<mint>(c, 0));
    }
    friend istream& operator >> (istream &in, Matrix &mat) {
        FOR(i, 0, mat.r - 1){
            FOR(j, 0, mat.c - 1){
                in >> mat.mat[i][j];
            }
        }
        return in;
    }
    friend ostream& operator << (ostream &out, Matrix &mat){
        FOR(i, 0, mat.r - 1){
            FOR(j, 0, mat.c - 1){
                out << mat.mat[i][j] << ' ';
            }
            out << endl;
        }
        return out;
    }
    Matrix operator * (const Matrix &other) const{
        Matrix res(r, other.c);
        FOR(i, 0, r - 1){
            FOR(j, 0, other.c - 1){
                mint sum = 0;
                FOR(k, 0, c - 1){
                    sum = sum + mat[i][k] * other.mat[k][j]; //Check MODINT
                }
                res.mat[i][j] = sum;
            }
        }
        return res;
    }
    
    Matrix tranpose(){
        Matrix T(c, r);
        FOR(i, 0, c - 1){
            FOR(j, 0, r - 1){
                T.mat[i][j] = mat[j][i];
            }
        }
        return T;
    }
    int determinant(){
        assert(r == c);
        int swapped = 0;
        FOR(iter, 0, c - 1){
            int minRow = -1;
            FOR(row, iter, r - 1){
                if (mat[row][iter] > 0 and (minRow == -1 or mat[row][iter] < mat[minRow][iter])){
                    minRow = row;
                }
            }
            if (minRow == -1) return 0;
            if (iter != minRow) {
                swap(mat[iter], mat[minRow]);
                swapped++;
            }
            mint div = mint(1) / mat[iter][iter];
            FOR(row, 0, r - 1){
                if (row == iter) continue;
                mint coef = mat[row][iter] * div;
                FOR(col, 0, c - 1){
                    mat[row][col] -= mat[iter][col] * coef;       
                }
            }
        }
        mint res = 1;
        FOR(i, 0, r - 1){
            res = res * mat[i][i];
        }
        if (swapped&1) res = res * mint(MOD - 1);
        return res.value();
    }
    mint rank(){
        if (r == 0 or c == 0) return 0;
        Matrix A = (*this);        
        int res = 0; //rank of the matrix
        FOR(i, 0, min(A.r, A.c) - 1){
            if (A.mat[i][i] == 0){
                FOR(j, 0, c - 1){
                    if (A.mat[i][j] != 0){
                        FOR(k, 0, r - 1){
                            swap(A.mat[k][i], A.mat[k][j]);
                        }
                        break;
                    }
                }
            }
            int pivotRow = -1;
            FOR(j, i, A.r - 1){
                if (A.mat[j][i] != 0){
                    pivotRow = j;
                    break;
                }
            }
            if (pivotRow != -1) res++;
            else continue;            
            if (i != pivotRow) swap(A.mat[i], A.mat[pivotRow]);
            FOR(j, 0, A.r - 1){
                if (j == i) continue;
                mint coef = A.mat[j][i] / A.mat[i][i];
                FOR(k, 0, A.c - 1){
                    A.mat[j][k] -= A.mat[i][k] * coef;
                }
            }
        }
        return res;
    }
    void identity(){
        assert(r == c);
        FOR(i, 0, r - 1){
            FOR(j, 0, c - 1){
                mat[i][j] = (i == j);
            }
        }
    }
};

Matrix binpow(matrix a, ll k){
    matrix res = a;
    k--;
    while(k){
        if(k&1) res = res * a;
        k >>= 1;
        a = a * a;
    }
    return res;
}

void solveEquation(Matrix &equation){
    int n = equation.r;
    int m = equation.c - 1;
    vector<int> varOrder(m, 0);
    iota(varOrder.begin(), varOrder.end(), 0);
    FOR(i, 0, min(equation.r, equation.c) - 1){
        if (equation.mat[i][i] == 0){
            FOR(j, 0, equation.c - 1){
                if (equation.mat[i][j] != 0){
                    FOR(k, 0, equation.r - 1){
                        swap(equation.mat[k][i], equation.mat[k][j]);
                    }
                    swap(varOrder[i], varOrder[j]);
                    break;   
                }
            }
        }
        int pivotRow = -1;
        FOR(j, i, equation.r - 1){
            if (equation.mat[j][i] != 0) {
                pivotRow = j;
                if (j != i) swap(equation.mat[j], equation.mat[i]);
                break;
            }
        }
        if (pivotRow == -1) continue;
        FOR(j, 0, equation.r - 1){
            if (j == i) continue;
            mint coef = equation.mat[j][i] / equation.mat[i][i];
            FOR(k, 0, equation.c - 1){
                equation.mat[j][k] -= equation.mat[i][k] * coef;
            }
        }
    }
    vector<vector<mint>> basis;
    vector<int> free(m, 0);
    FOR(i, 0, m - 1){
        if (i >= n or equation.mat[i][i] == 0){
            free[i] = 1;
        }
    }
    FOR(i, 0, m - 1){
        if (free[i]){
            vector<mint> v(m, 0);
            v[varOrder[i]] = 1;
            FOR(j, 0, n - 1){
                if (!free[j]){
                    v[varOrder[j]] = mint(0) - (equation.mat[j][i] / equation.mat[j][j]);
                }
            }
            basis.pb(v);
        }
    }

    Matrix solution(m, 1);
    FOR(i, 0, min(equation.r, m) - 1){
        solution.mat[varOrder[i]][0] = equation.mat[i][m] / equation.mat[i][i]; 
    }

    FOR(i, 0, m - 1){
        cout << solution.mat[i][0] << ' ';
    }
    cout << endl;

    FOR(i, 0, sz(basis) - 1){
        FOR(j, 0, m - 1){
            cout << basis[i][j] << ' ';
        }
        cout << endl;
    }
    
}
