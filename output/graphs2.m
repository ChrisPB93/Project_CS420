close all
clear all
CG = importdata('out_CG_parallel3.txt',' ',1);
LU = importdata('out_CG_parallel2.txt',' ',1);
timeseq = 0.16294694;

%%
figure;
hold on
plot([CG.data(1:15,1)'],[CG.data(1:15,2)'],'x-');
plot([LU.data(1:15,1)'],[LU.data(1:15,2)'],'x-');
%plot([0 cgParallel.data(22:28,2)'],[timeseq cgParallel.data(22:28,3)'],'x-');
xlabel('Number of threads');
ylabel('Running time');
title('Runningtime for nodes running with varying number of threads');
legend('CG','LU');
set(gca,'yscale','log')
grid on
hold off


%%
figure;
hold on
plot([0 CG.data(1:15,1)'],timeseq./[timeseq CG.data(1:15,2)'],'x-');
plot([0 LU.data(1:15,1)'],timeseq./[timeseq LU.data(1:15,2)'],'x-');
%plot([0 cgParallel.data(22:28,2)'],timeseq./[timeseq cgParallel.data(22:28,3)'],'x-');
xlabel('Number of threads');
ylabel('Speedup');
%set(gca,'xscale','log') 
legend('CG','LU');
title('Speedup for nodes running with varying number of threads');
grid on
hold off
