function x_k1 = state_predict(A, B, x_k, u_k)
    x_k1 = A * x_k + B * u_k;
end
