function u_k = Prediction(y_k, x_k, E, L, H, N, p)

    U_k = zeros(N * p, 1); % NP x 1

    G = E * x_k - L * y_k;

    eigenvalues = eig(H);

    if all(eigenvalues > 0)
        disp('矩阵是正定的');
    else
        disp('矩阵不是正定的');
    end

    U_k = quadprog(H, G);

    u_k = U_k(1:p, 1); % 取第一个结果

end
