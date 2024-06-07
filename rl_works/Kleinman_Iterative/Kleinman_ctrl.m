clc;
clear;

% 定义期望目标，初始状态以及初始输入
x_t = [5; 0; 0; 0];
x_c = [0; 0; 0; 0];
u_c = [0];
% 仿真步长以及控制周期
n_step = 1000;
Ts = 0.001;
% 定义权重矩阵
Q = eye(4);
Q(1, 1) = 1000;
Q(2, 2) = 1;
Q(3, 3) = 1;
Q(4, 4) = 1;
R = eye(1);
R(1, 1) = 1;

X_K(:, 1) = x_c;

% 设置状态空间矩阵
A = [
        -0.0665,11.5,0,0;...
        0,-2.5,2.5,0;...
        -9.5,0,-13.736,-13.736;...
        0.6,0,0,0
    ];
B = [0;0;13.736;0];
C = eye(4);
D = zeros(4,1);
[K, P] = Kleinman_Iterative(A, B, Q, R);
disp(K);
K1 = lqr(A, B, Q, R);
disp(K1);
% 系统离散化用于进行仿真预测
sys_c = ss(A, B, C, D);
sys_d = c2d(sys_c, Ts);

% 循环仿真
for i = 1:n_step
    u_c = K * (x_t - x_c);
    U_K(:, i) = u_c;
    x_c = state_predict(sys_d.A, sys_d.B, x_c, u_c);
    X_K(:, i + 1) = x_c;
end

% 绘制状态变量和输入的变化
subplot (2, 1, 1);
hold;
for i = 1:size (X_K, 1)
    plot (X_K(i, :));
end
legend("x1", "x2", "x3", "x4");
hold off;
subplot (2, 1, 2);
hold;
for i = 1:size (U_K, 1)
    plot (U_K(i, :));
end
legend("u1");
hold off;
