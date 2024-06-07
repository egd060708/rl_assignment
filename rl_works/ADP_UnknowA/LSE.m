function P_out = LSE(X, Y)
    P = inv(transpose(X) * X) * transpose(X) * Y;
    P_out = Exchange_P2Matrix(P);
end
