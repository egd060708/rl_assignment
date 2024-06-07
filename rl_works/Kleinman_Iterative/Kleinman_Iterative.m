function [K, P_c] = Kleinman_Iterative(A, B, Q, R)
    % 根据系统矩阵初始化参数
    K = zeros(size(transpose(B)));
    P_l = zeros(size(A));
    P_c = zeros(size(A));
    A_k = zeros(size(A));
    % 先迭代一次
    A_k = A - B * K;
    P_c = sylvester(transpose(A_k), A_k, - Q - transpose(K) * R * K);
    K = inv(R) * transpose(B) * P_c;
    % 循环迭代直到收敛
    while stop_judge(P_l, P_c, 0.000001) == 0
        P_l = P_c;
        A_k = A - B * K;
        P_c = sylvester(transpose(A_k), A_k, -Q - transpose(K) * R * K);
        K = inv(R) * transpose(B) * P_c;
    end

end
