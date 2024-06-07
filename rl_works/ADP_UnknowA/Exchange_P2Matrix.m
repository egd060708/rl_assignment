function P_out_array = Exchange_P2Matrix(P_in)
    P_out1 = [P_in(1), P_in(2), P_in(4), P_in(7)];
    P_out2 = [P_in(2), P_in(3), P_in(5), P_in(8)];
    P_out3 = [P_in(4), P_in(5), P_in(6), P_in(9)];
    P_out4 = [P_in(7), P_in(8), P_in(9), P_in(10)];
    P_out_array = [P_out1; P_out2; P_out3; P_out4];
end
