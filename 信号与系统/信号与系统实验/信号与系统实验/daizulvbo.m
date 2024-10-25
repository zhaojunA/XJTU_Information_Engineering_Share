clc;
close all;
[y,Fs]=audioread('16.wav');
siglength=length(y);
T=1/Fs;
t=(1:siglength)*T;
subplot(2,2,1);
plot(t,y);
title('原始信号时域图');
xlabel('时间');
ylabel('声音信号');
Y=fft(y,20000);
K=length(20*log10(abs(Y)));
f=-pi:2*pi/(K-1):pi;
subplot(2,2,2);
plot(f,20*log10(abs(Y)));
title('原始信号频域图');
xlabel('信号频率');
ylabel('信号幅度');
[y1,Fs]=audioread('16noise.wav');
t1=(1:length(y1))*T;
subplot(2,2,3);
plot(t1,y1);
title('含噪声信号时域图');
xlabel('时间');
ylabel('声音信号');
Y2=abs(fft(y1));
P=length(20*log10(abs(Y2)));
f1=-pi:2*pi/(P-1):pi;
subplot(2,2,4);
plot(f1,20*log10(abs(Y2)));
title('含噪声信号频域图');
xlabel('信号频率');
ylabel('信号幅度');
h=[1 -2*cos(2.76132) 1];
z=conv(y1,h);
N=length(z);
Z=fftshift(fft(z,N));
w=linspace(-pi,pi,N);
figure(3)
plot(w,20*log10(abs(Z)));
sound(z,Fs);