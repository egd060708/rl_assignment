function [A_d, B_d] = get_car_model(x_k, u_k, Ts)
    % x_c 为三维状态向量, u_c(1) 为上一个周期求出的参考速度
    A = [0, 0, -u_k(1, 1) * sin(x_k(3, 1)); ...
             0, 0, u_k(1, 1) * cos(x_k(3, 1)); ...
             0, 0, 0];
    B = [cos(x_k(3, 1)), 0; ...
             sin(x_k(3, 1)), 0; ...
             0, 1];
    C = eye(3);
    D = zeros(3, 2);
    if nargin < 3
        A_d = A;
        B_d = B;
    else
        % 系统离散化
        sys_c = ss(A, B, C, D);
        sys_d = c2d(sys_c, Ts);
        A_d = sys_d.A;
        B_d = sys_d.B;
    end
end
