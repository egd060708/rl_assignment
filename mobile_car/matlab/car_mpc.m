function [Y_K,X_K,U_K] = car_mpc(Q,R,F,k_steps,n_steps,y_t,x_init)
%% 定义状态矩阵 A, n x n 矩阵
n= 3;%取其行数，即状态空间变量个数

%% 定义输入矩阵 B, n x p 矩阵
p = 2;%取其列数，即输入变量个数

%% 定义矩阵 X_K， n x k 矩 阵

X_K = zeros(n,k_steps);

%% 初始状态变量值， n x 1 向量
X_K(:,1) = x_init;

%% 定义输入矩阵 U_K， p x k 矩阵
U_K=zeros(p,k_steps);


for k = 1 : k_steps
    % X_K 为三维状态向量, U_K 为上一个周期求出的参考出
    if k == 1
        A = [0,0,0;...
            0,0, 0;...
            0,0, 0];
        B = [1,0;...
             0,0;...
             0,1];
    else
        A = [0,0,-U_K(1,k-1)*sin(X_K(3,k));...
            0,0, U_K(1,k-1)*cos(X_K(3,k));...
            0,0, 0];
        B = [cos(X_K(3,k)),0;...
            sin(X_K(3,k)),0;...
            0,1];
    end
    C = eye(3);
    D = zeros(3,2);
    % 系统离散化
    Ts = 0.002;
    sys_c = ss(A, B, C, D);
    sys_d = c2d(sys_c, Ts);

    %% Call MPC_Matrices 函数 求得 E,H矩阵 

    [E,L,H]=MPC_Matrices(sys_d.A,sys_d.B,Q,R,F,n_steps);

    %% 计算每一步的状态变量的值
    %定义目标向量
    Y_T = y_t;
    for i=0:n_steps
        for j=1:n
            Y_K((i*n+j),1) = Y_T(j,1);
        end
    end

    %% 求得U_K(:,k)

    U_K(:,k) = Prediction(Y_K,X_K(:,k),E,L,H,n_steps,p);

    %% 计算第k+1步时状态变量的值

    X_K(:,k+1)=(sys_d.A*X_K(:,k)+sys_d.B*U_K(:,k));

end



end