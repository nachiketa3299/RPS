#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> MAT;

MAT matMul(const MAT &A, const MAT &B) {
    MAT C(A.size(), std::vector<int>(B[0].size()));
    for (std::size_t i = 0; i < A.size(); ++i) {
        for (std::size_t j = 0; j < B[0].size(); ++j) {
            int r = 0;
            for (std::size_t k = 0; k < A[0].size(); ++k)
                r += A[i][k] * B[k][j];
            C[i][j] = r;
        }
    }
    return C;
}
 
int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::size_t N, M; std::cin >> N >> M;
    MAT A(N, std::vector<int>(M));
    for (std::size_t i = 0; i < N; ++i)
        for (std::size_t j = 0; j < M; ++j)
            std::cin >> A[i][j];

    std::size_t K; std::cin >> M >> K;
    MAT B(M, std::vector<int>(K));
    for (std::size_t i = 0; i < M; ++i)
        for (std::size_t j = 0; j < K; ++j)
            std::cin >> B[i][j];

    MAT C = matMul(A, B);
    for (std::size_t i = 0; i < C.size(); ++i) {
        for (std::size_t j = 0; j < C[i].size(); ++j)
            std::cout << C[i][j] << " ";
        std::cout << '\n';
    }

    return 0;
}
