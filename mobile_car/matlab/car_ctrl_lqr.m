clc;
clear;
% 使用单步lqr进行仿真

% 定义期望目标，初始状态以及初始输入
% 注意初始输入不能为0，否则lqr无解
x_t = [10; 10; 2];
x_c = [0; 0; 0];
u_c = [0.0001; 0.0001];
% 仿真步长以及控制周期
n_step = 1000;
Ts = 0.002;
% 定义权重矩阵
Q = eye(3);
Q(1, 1) = 1000;
Q(2, 2) = 1000;
Q(3, 3) = 100;
R = eye(2);
R(1, 1) = 1;
R(2, 2) = 10;

X_K(:, 1) = x_c;

for i = 1:n_step
    u_c = car_lqr(x_t, x_c, u_c, Q, R, Ts);
    U_K(:, i) = u_c;
    x_c = car_model(x_c, u_c, Ts);
    X_K(:, i + 1) = x_c;
end

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
