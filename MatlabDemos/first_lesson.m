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
s = solve(eq); %��һԪ���η���

%matrix operation

%res=dot(a1,a2); %�������� ���
%cross = cross(a1,a2); % ��� ������
A=[-10,4,-6,8;4,-1,6,-2;5,7,9,-6;0,9,6,-2];
rresu = rank(A); %��������
l1 = [1 -1 2 4]';
l2 = [0 3 1 2]';
l3 = [-3 3 7 14]';
l4 = [4 -1 9 18]';
rank([l1,l2,l3,l4]); 
[uip] = rref([l1,l2,l3,l4]); %�󼫴��޹���,������Ϊ���ݾ���
de=[1,2,4;3,4,5;6,7,8];
det(de); %������ʽ
inv(de); %������
pinv(de);

nox = norm(l1); %������ģ��Ҳ������

an1 = [1,1];
an2 = [1,0];
angle = acos((an1*an2')/(norm(an1)*norm(an2))); %�����н�
[V,D] = eig([l1,l2,l3,l4]); %��������






