%first lesson,test some basic grammars

x = 3;
y = sqrt(4);
initial_velocity = 0;
acceleration = 9.8;
time = 20;
final_velocity = initial_velocity ... % line break
    + acceleration * time;
a = [1 2 3 4;0 2 0 0];
b = [5 6 7 8];
c = find(a);
% length = length(a);
% linspace = linspace(5,5);
a1 = [1 2 3];a2 = [1 0 2];
eq = 'x^2 - 7*x + 12=0';
s = solve(eq); %解一元二次方程

%matrix operation

%res=dot(a1,a2); %求数量积 点积
%cross = cross(a1,a2); % 叉积 向量积
A=[-10,4,-6,8;4,-1,6,-2;5,7,9,-6;0,9,6,-2];
rresu = rank(A); %求矩阵的秩
l1 = [1 -1 2 4]';
l2 = [0 3 1 2]';
l3 = [-3 3 7 14]';
l4 = [4 -1 9 18]';
rank([l1,l2,l3,l4]); 
[uip] = rref([l1,l2,l3,l4]); %求极大无关组,并化简为阶梯矩阵
de=[1,2,4;3,4,5;6,7,8];
det(de); %求行列式
inv(de); %求逆阵
pinv(de);

nox = norm(l1); %求向量模，也即长度

an1 = [1,1];
an2 = [1,0];
angle = acos((an1*an2')/(norm(an1)*norm(an2))); %向量夹角
[V,D] = eig([l1,l2,l3,l4]); %求特征量






