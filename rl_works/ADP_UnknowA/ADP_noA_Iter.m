function K = ADP_noA_Iter(A, B, Q, R, A_n, A_d, B_d, Ts, N)
    % 根据系统矩阵初始化参数
    [K, P_c] = Kleinman_Iterative(A, B, Q, R);
    X = [0; 0.1; 0; 0];
    P_l = P_c;

    [X_i_all, Y_i_all, X_i] = Generate_XY(A_d, B_d, Q, R, X, K, Ts, N);
    P_c = LSE(X_i_all, Y_i_all);
    count = 0;
    while stop_judge(P_l, P_c, 0.001) == 0
        P_l = P_c;
        [X_i_all, Y_i_all, X_i] = Generate_XY(A_d, B_d, Q, R, X_i, K, Ts, N);
        P_c = LSE(X_i_all, Y_i_all);
        disp(P_c-P_l);
        K = inv(R) * transpose(B) * P_c;
        count = count + 1;
    end
    disp(count);
end
