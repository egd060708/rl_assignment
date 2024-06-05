function u_c = car_lqr(x_t, x_c, u_c, Q, R, Ts)
% x_c 为三维状态向量, u_c(1) 为上一个周期求出的参考速度
A = [0,0,-u_c(1)*sin(x_c(3));...
     0,0, u_c(1)*cos(x_c(3));...
     0,0, 0];
B = [cos(x_c(3)),0;...
     sin(x_c(3)),0;...
     0,1];
C = eye(3);
D = zeros(3,2);
% 系统离散化
sys_c = ss(A, B, C, D);
sys_d = c2d(sys_c, Ts);
% 计算lqr
K = dlqr(sys_d.A,sys_d.B,Q,R);
u_c = transpose(K * transpose(x_t - x_c));

end



