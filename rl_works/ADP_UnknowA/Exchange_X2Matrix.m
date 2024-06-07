function [X10D] = Exchange_X2Matrix(X4D)
% 将X:4D转化成10D
X10D = [];
for row = 1:4
    for column = 1:row
        X10D = [X10D,X4D(row)*X4D(column)];
    end
end
end

