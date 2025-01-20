%矩阵 LU 分解
%假定输入的 A 可进行 LU 分解
A = input('输入矩阵 A:\n');
b = input('输入向量 b:\n');
n = length(A);
E = eye(n); %消去矩阵
for t=1:n-1 %进行 LU 分解
%依次求消去矩阵并相乘
temp = eye(n);
temp(t+1:n,t) = - A(t+1:n,t)./A(t,t);
E = temp * E;
%初等行变换
A(t+1:n,:) = A(t+1:n,:) + A(t,:) .* temp(t+1:n,t);
end
U = A
L = inv(E)
%解方程，既可以直接求逆后得出 x，也可用迭代法求出 x
% y = Eb;
% Ux = y
% y = E * b
% x = inv(U) * y
y = zeros(n,1);
for t = 1:ny(t) == b(t) - sum( L(t,1:t-1) * y(1:t-1) );
end
x = zeros(n,1);
for t = n:-1:1
x(t) = ( y(t) - sum( U(t,t:n) * x(t:n)) ) / U(t,t) ;
end
x