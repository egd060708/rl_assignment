function [W,u_k1] = car_mpc_step(ref, yaw, u_k)

    % 更新系统模型
    A = [0, 0, -u_k(1, 1) * sin(yaw); ...
             0, 0, u_k(1, 1) * cos(yaw); ...
             0, 0, 0];
    B = [cos(yaw), 0; ...
             sin(yaw), 0; ...
             0, 1];

    % 定义权重矩阵
    Q = eye(3);
    Q(1, 1) = 1000;
    Q(2, 2) = 1000;
    Q(3, 3) = 300;
    R = eye(2);
    R(1, 1) = 1;
    R(2, 2) = 1;
    F = Q;

    C = eye(3);
    D = zeros(3, 2);
    % 系统离散化
    Ts = 0.002;
    sys_c = ss(A, B, C, D);
    sys_d = c2d(sys_c, Ts);

    % 定义控制区间
    n_steps = 5;

    % 定义状态矩阵 A, n x n 矩阵
    n = size(sys_d.A, 1); %取其行数，即状态空间变量个数

    % 定义输入矩阵 B, n x p 矩阵
    p = size(sys_d.B, 2); %取其列数，即输入变量个数

    % 当前状态变量值， n x 1 向量
    X_K = [0; 0; yaw];

    % 获得期望目标
    y_t = [0; 0; ref];

    %定义目标向量
    Y_T = y_t;

    for i = 0:n_steps

        for j = 1:n
            Y_K((i * n + j), 1) = Y_T(j, 1);
        end

    end

    % Call MPC_Matrices 函数 求得 E,H矩阵
    [E, L, H] = MPC_Matrices(sys_d.A, sys_d.B, Q, R, F, n_steps);

    % 求解二次规划问题得输出
    u_k1 = Prediction(Y_K, X_K, E, L, H, n_steps, p);
    W = u_k1(2,1);

end
