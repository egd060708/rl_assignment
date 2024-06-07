function [X_out_all, Y_out_all, X_k] = Generate_XY(A_d, B_d, Q, R, X, K_last, Ts, N)
    X_k = X;
    X_last = X;
    X_out_all = [];
    Y_out_all = [];
    
    for i = 1:N
        X_last = X_k;
        Y_out = 0;
        
        Y_out = (transpose(X_k) * (Q + transpose(K_last) * R * K_last) * X_k) * Ts;
        X_k = A_d * X_k - B_d * K_last * X_k;
        
        X_out_matrix = Exchange_X2Matrix(X_k);
        X_out_matrix_diff = Exchange_X2Matrix(X_last) - X_out_matrix;
        X_out_all = [X_out_all; X_out_matrix_diff];
        Y_out_all = [Y_out_all; Y_out];
    end
end