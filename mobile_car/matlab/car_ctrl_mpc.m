clc;
clear;

% 定义step数量k
k_steps = 1000; %预测区间
n_steps = 5; %控制区间

%%
% 定义权重矩阵
Q = eye(3);
Q(1, 1) = 1000;
Q(2, 2) = 1000;
Q(3, 3) = 100;
R = eye(2);
R(1, 1) = 1;
R(2, 2) = 1;

F = Q;

% 目标向量及初始状态
y_t = [10; 10; 2];
x_init = [0; 0; 0];

% 计算
[Y_K, X_K, U_K] = car_mpc(Q, R, F, k_steps, n_steps, y_t, x_init);

% 绘制状态变量和输入的变化

subplot (2, 1, 1);

hold;

for i = 1:size (X_K, 1)

    plot (X_K(i, :));

end

legend("x", "y", "theta");

hold off;

subplot (2, 1, 2);

hold;

for i = 1:size (U_K, 1)

    plot (U_K(i, :));

end

legend("u1", "u2");

hold off;
