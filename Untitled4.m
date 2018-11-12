%**************************************************%
%目的：实现孔洞填充及连通分量的提取
%日期：2018.5.24
%**************************************************%

%***************** 孔洞填充 ***********************%
A = imread('C:/Users/KimTaehee/Desktop/111.jpg');
A = im2bw(A); %二值化
figure(1);
subplot(1, 2, 1);
imshow(A);
title('二值化后的图');
A_ct = ~A; %A的补集
[m, n] = size(A);
X = zeros(m, n);
[k, z] = find(A == 1); %找到A中灰度值为1的点的位置
X(k(1), z(1)) = 1; %选取第一个灰度值为1的点为初始点
se = [0, 1, 0;1, 1, 1;0, 1, 0]; %结构元
over = 0;  %判断是否迭代结束
i = 0;    %迭代次数
while (~over)
i = i + 1;
Xp = X;
X = imdilate(X, se) & A_ct;  %膨胀后与补集求交集
if X == Xp % 二者相等，迭代结束
over = 1;
end
end
A = ~X | A; %求并集
subplot(1, 2, 2);
imshow(A);
title('填充结果');

%**************** 连通分量的提取 ************************%
%直接对以上填充得到的图像进行连通分量提取
A0 = A; %原始图像
X1 = zeros(m, n);  %迭代阵列
B = zeros(m, n); %用来存储已经提取的连通分量
count = 1;   %记录提取的连通分量的个数
figure(2);
i = 1;
j = 1;
while (length(find(A == 1)))
[k, z] = find(A == 1); %找到A中灰度值为1的点的位置
X1(k(1), z(1)) = 1; %选取第一个灰度值为1的点为初始点
se = ones(3); %结构元
%提取连通分量
while (1)
Xp1 = X1;
X1 = imdilate(X1, se) & A;  %膨胀后求交集
if X1 == Xp1 % 二者相等，迭代结束
break;
end
end
B = B + X1;
num(count) = length(find(X1 == 1));
count = count + 1;
A = A - B; %减去已经提取的连通分量，接下来通过迭代继续对剩下的连通分量进行提取
imshow(B); %动态显示每次迭代过程中提取到的各个连通区域
title('各连通分量的提取过程');
hold on;
end
hold off;
%显示提取到的连通分量的数目及各连通分量中的像素数
fprintf('连通分量     连通分量中的像素数\n');
for i = 1:count
fprintf('%2d               %d\n', i, num(i));
end
figure(3);
subplot(1, 2, 1);
imshow(A0);
title('原始图像');
subplot(1, 2, 2);
imshow(B);
title('提取得到的所有连通分量');
