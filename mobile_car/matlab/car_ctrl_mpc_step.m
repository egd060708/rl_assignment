clc;
clear;

% 定义期望目标，初始状态以及初始输入
% 注意初始输入不能为0，否则lqr无解
x_t = [10; 10; 2];
x_c = [0; 0; 0];
u_c = [0; 0];
% 仿真步长以及控制周期
n_step = 2000;
Ts = 0.002;

X_K(:, 1) = x_c;

for i = 1:n_step
    [w,u_c] = car_mpc_step(x_t(3,1), x_c(3,1), u_c);
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
